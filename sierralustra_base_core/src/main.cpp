#include "sierralustra/knowledge_graph.hpp"
#include <iostream>

int main() {
    // 1. Establish the original scientific primitive
    auto root = sl::KnowledgeNode::create("node_0", "\\section{Introduction}\nInitial thesis.");

    // 2. Fork parallel working branches concurrently
    auto researcher_alex = root->fork("node_alex");
    auto researcher_blake = root->fork("node_blake");

    // 3. Simulating independent state modifications
    researcher_alex->update_content("\\section{Introduction}\nInitial thesis.\n\\delta_A = 1");
    researcher_blake->update_content("\\section{Introduction}\nInitial thesis.\n\\delta_B = 2");

    // 4. Implement a custom structural merge rule
    sl::MergeStrategy latex_fallback_resolver = [](const sl::MergeContext& ctx) -> std::string {
        // Here you would hook up your native LaTeX tokenizers.
        // For demonstration, we handle conflicts by structural stack sequencing:
        return ctx.branch_a_content + "\n% --- Concatenated Merge Variant ---\n" + ctx.branch_b_content;
    };

    // 5. Execute a synchronized merge operation
    auto merged_node = sl::KnowledgeNode::merge("node_consolidated", researcher_alex, researcher_blake, latex_fallback_resolver);

    std::cout << "Consolidated Content:\n" << merged_node->get_content() << std::endl;
    return 0;
}
