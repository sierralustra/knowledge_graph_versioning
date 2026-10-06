#include "sierralustra/knowledge_graph.hpp"
#include <unordered_map>
#include <mutex>

namespace sl {

KnowledgeNode::KnowledgeNode(std::string id, std::string content, std::vector<Ptr> ancestors)
    : id_(std::move(id)), content_(std::move(content)), ancestors_(std::move(ancestors)) 
{
    version_hash_ = compute_intrinsic_hash(content_);
}

KnowledgeNode::Ptr KnowledgeNode::create(const std::string& id, const std::string& initial_content) {
    return Ptr(new KnowledgeNode(id, initial_content, {}));
}

KnowledgeNode::Ptr KnowledgeNode::fork(const std::string& new_id) {
    std::shared_lock<std::shared_mutex> read_lock(mutex_);
    return Ptr(new KnowledgeNode(new_id, content_, { shared_from_this() }));
}

void KnowledgeNode::update_content(std::string new_content) {
    std::unique_lock<std::shared_mutex> write_lock(mutex_);
    content_ = std::move(new_content);
    version_hash_ = compute_intrinsic_hash(content_);
}

std::string KnowledgeNode::get_content() const {
    std::shared_lock<std::shared_mutex> read_lock(mutex_);
    return content_;
}

size_t KnowledgeNode::get_version_hash() const {
    std::shared_lock<std::shared_mutex> read_lock(mutex_);
    return version_hash_;
}

std::vector<KnowledgeNode::Ptr> KnowledgeNode::get_ancestors() const {
    std::shared_lock<std::shared_mutex> read_lock(mutex_);
    return ancestors_;
}

size_t KnowledgeNode::compute_intrinsic_hash(const std::string& text) {
    return std::hash<std::string>{}(text);
}

KnowledgeNode::Ptr KnowledgeNode::merge(const std::string& target_id, 
                                        const Ptr& branch_a, 
                                        const Ptr& branch_b, 
                                        const MergeStrategy& resolver) 
{
    auto common_ancestor = find_lca(branch_a, branch_b);
    
    std::shared_lock<std::shared_mutex> lock_a(branch_a->mutex_, std::defer_lock);
    std::shared_lock<std::shared_mutex> lock_b(branch_b->mutex_, std::defer_lock);
    std::lock(lock_a, lock_b); // Concurrency safety: Deadlock prevention step

    std::string ancestor_text = common_ancestor ? common_ancestor->get_content() : "";
    std::string text_a = branch_a->content_;
    std::string text_b = branch_b->content_;

    std::string final_content;
    if (text_a == text_b)             final_content = text_a;
    else if (text_a == ancestor_text) final_content = text_b;
    else if (text_b == ancestor_text) final_content = text_a;
    else {
        final_content = resolver(MergeContext{ancestor_text, text_a, text_b});
    }

    return Ptr(new KnowledgeNode(target_id, final_content, { branch_a, branch_b }));
}

KnowledgeNode::Ptr KnowledgeNode::find_lca(const Ptr& a, const Ptr& b) {
    if (!a || !b) return nullptr;
    
    std::unordered_map<size_t, Ptr> visited;
    std::vector<Ptr> queue = { a };
    
    while (!queue.empty()) {
        auto current = queue.back();
        queue.pop_back();
        if (current) {
            visited[current->get_version_hash()] = current;
            for (const auto& parent : current->get_ancestors()) queue.push_back(parent);
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
            for (const auto& parent : current->get_ancestors()) queue.push_back(parent);
        }
    }
    return nullptr;
}

} // namespace sl
