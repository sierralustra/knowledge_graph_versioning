#pragma once

#include <string>
#include <vector>
#include <memory>
#include <shared_mutex>
#include <unordered_map>
#include <functional>
#include <optional>
#include <mutex>

namespace sl {

struct MergeContext {
    std::string ancestor_content;
    std::string branch_a_content;
    std::string branch_b_content;
};

// Stratified conflict resolution strategy type
using MergeStrategy = std::function<std::string(const MergeContext&)>;

class KnowledgeNode : public std::enable_shared_from_this<KnowledgeNode> {
public:
    using Ptr = std::shared_ptr<KnowledgeNode>;
    using WeakPtr = std::weak_ptr<KnowledgeNode>;

    // Factory method for generating a root primitive
    static Ptr create(const std::string& id, const std::string& initial_content) {
        return Ptr(new KnowledgeNode(id, initial_content, {}));
    }

    // Thread-safe branching (Forking a new leaf in the DAG)
    Ptr fork(const std::string& new_id) {
        std::shared_lock<std::shared_mutex> read_lock(mutex_);
        
        // The new node carries this node as its sole immediate ancestor
        return Ptr(new KnowledgeNode(new_id, content_, { shared_from_this() }));
    }

    // High-performance state updates (Exclusive write lock)
    void update_content(std::string new_content) {
        std::unique_lock<std::shared_mutex> write_lock(mutex_);
        content_ = std::move(new_content);
        version_hash_ = compute_intrinsic_hash(content_);
    }

    // Read access to content and metadata
    std::string get_content() const {
        std::shared_lock<std::shared_mutex> read_lock(mutex_);
        return content_;
    }

    size_t get_version_hash() const {
        std::shared_lock<std::shared_mutex> read_lock(mutex_);
        return version_hash_;
    }

    std::vector<Ptr> get_ancestors() const {
        std::shared_lock<std::shared_mutex> read_lock(mutex_);
        return ancestors_;
    }

    // Thread-safe three-way semantic merge primitive
    static Ptr merge(const std::string& target_id, 
                     const Ptr& branch_a, 
                     const Ptr& branch_b, 
                     const MergeStrategy& resolver) 
    {
        auto common_ancestor = find_lca(branch_a, branch_b);
        
        std::shared_lock<std::shared_mutex> lock_a(branch_a->mutex_, std::defer_lock);
        std::shared_lock<std::shared_mutex> lock_b(branch_b->mutex_, std::defer_lock);
        std::lock(lock_a, lock_b); // Avoid deadlock scenarios via structured lock ordering

        std::string ancestor_text = common_ancestor ? common_ancestor->get_content() : "";
        std::string text_a = branch_a->content_;
        std::string text_b = branch_b->content_;

        std::string final_content;
        if (text_a == text_b) {
            final_content = text_a; // Fast-path: Clean, identical resolution
        } else if (text_a == ancestor_text) {
            final_content = text_b; // Fast-path: Only branch B mutated
        } else if (text_b == ancestor_text) {
            final_content = text_a; // Fast-path: Only branch A mutated
        } else {
            // High-contention fallback: Defer to structural/semantic layout rule
            final_content = resolver(MergeContext{ancestor_text, text_a, text_b});
        }

        return Ptr(new KnowledgeNode(target_id, final_content, { branch_a, branch_b }));
    }

private:
    KnowledgeNode(std::string id, std::string content, std::vector<Ptr> ancestors)
        : id_(std::move(id)), content_(std::move(content)), ancestors_(std::move(ancestors)) 
    {
        version_hash_ = compute_intrinsic_hash(content_);
    }

    static size_t compute_intrinsic_hash(const std::string& text) {
        return std::hash<std::string>{}(text);
    }

    // Helper: Find Lowest Common Ancestor (LCA) in the graph topology
    static Ptr find_lca(const Ptr& a, const Ptr& b) {
        if (!a || !b) return nullptr;
        
        std::unordered_map<size_t, Ptr> visited;
        std::vector<Ptr> queue = { a };
        
        while (!queue.empty()) {
            auto current = queue.back();
            queue.pop_back();
            if (current) {
                visited[current->get_version_hash()] = current;
                for (const auto& parent : current->get_ancestors()) {
                    queue.push_back(parent);
                }
            }
        }

        queue = { b };
        while (!queue.empty()) {
            auto current = queue.back();
            queue.pop_back();
            if (current && visited.contains(current->get_version_hash())) {
                return visited[current->get_version_hash()];
            }
            if (current) {
                for (const auto& parent : current->get_ancestors()) {
                    queue.push_back(parent);
                }
            }
        }
        return nullptr;
    }

    std::string id_;
    std::string content_;
    size_t version_hash_;
    std::vector<Ptr> ancestors_;
    
    mutable std::shared_mutex mutex_; // Core synchronization engine primitive
};

} // namespace sl
