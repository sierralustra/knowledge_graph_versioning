#include "sierralustra/knowledge_graph.hpp"
#include <cassert>
#include <iostream>

void test_clean_fork_and_mutation() {
    auto root = sl::KnowledgeNode::create("root", "Base Scientific State");
    auto child = root->fork("branch_1");
    child->update_content("Mutated State");

    assert(root->get_content() == "Base Scientific State");
    assert(child->get_content() == "Mutated State");
    std::cout << "[Test Passed]: DAG Isolation Integrity Preserved." << std::endl;
}

int main() {
    test_clean_fork_and_mutation();
    return 0;
}
