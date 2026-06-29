#include "sierralustra/knowledge_graph.hpp"
#include <iostream>

int main() {
    auto server_root = sl::KnowledgeNode::create("origin", "\\title{Sierralustra Global Graph}");
    std::cout << "[Runtime Initialization Complete] Instance hash: " << server_root->get_version_hash() << std::endl;
    return 0;
}
