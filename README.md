

---


# Sierralustra: The Non-Linear Knowledge Engine

[![License: AGPL-3.0](https://img.shields.io/badge/License-AGPL%203.0-blue.svg)](https://opensource.org/licenses/AGPL-3.0)
[![Language: C++20](https://img.shields.io/badge/Language-C%2B%2B20-00599C.svg)](https://isocpp.org/)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)]()

Sierralustra is a high-performance, concurrent version-control and collaboration engine designed specifically for structured intellectual and scientific knowledge. 

While Git revolutionized line-by-line source code tracking, it falls short when dealing with nested document structures, mathematical schemas, and multi-party research logic. Sierralustra introduces **Knowledge Trees**: a thread-safe, graph-based data primitive designed to branch, mutate, and semantically merge complex concepts without flat-text merge conflicts.

---

## 🏗️ Architectural Foundations

Unlike typical web platforms built on top of flat document models, Sierralustra handles intellectual capital as a Directed Acyclic Graph (DAG). 



Every node in the graph represents a logical brick of knowledge (e.g., text blocks, LaTeX expressions, or metadata) maintaining its own cryptographic identity and structural lineage. When concurrent mutations occur, our engine resolves conflicts semantically by evaluating the structural properties of the nodes rather than relying on arbitrary string lines.

### Key Performance Primitives
* **Lock-Ordered 3-Way Merge:** Built-in protection against race conditions and deadlocks using strict `std::shared_mutex` locking hierarchies during concurrent merge sequences.
* **Deterministic AI Subsystem:** Architectural hooks that allow LLMs and agentic reasoning systems to navigate the knowledge graph natively as a single source of truth, bypassing traditional lossy vector-search chunking.
* **Native Scientific Foundations:** Integrated mathematical parsing that guarantees LaTeX syntax structural integrity is preserved across branching points.

---

## 🚀 Core Features

*   **Deterministic Knowledge Trees:** Graph-based versioning that allows independent nodes of an idea or research paper to branch, mutate, and merge concurrently.
*   **High-Concurrency Engine:** Thread-safe, low-latency tree operations engineered using modern concurrent data structures to handle high-throughput collaborative streams.
*   **Native Scientific Parsing:** Deep integration with LaTeX tokenization and mathematical parsing, ensuring syntax structural integrity is preserved across branches.
*   **Deterministic AI Subsystem:** Architectural hooks designed to allow LLMs and reasoning engines to traverse the knowledge graph deterministically rather than relying on lossy semantic vector-chunking.

## 📁 Repository Structure

The engine is engineered using a clean, modern out-of-source modular layout:

```text
sierralustra/
├── CMakeLists.txt                 # Master build orchestration rules
├── include/
│   └── sierralustra/
│       └── knowledge_graph.hpp    # Public API & Engine declarations
├── src/
│   └── knowledge_graph.cpp        # Private runtime implementations
├── apps/
│   └── main.cpp                   # Desktop/Server execution entry point
└── tests/
    └── graph_tests.cpp            # Thread-isolation and regression tests

```

## 🛠️ Quick Start
Prerequisites

    A modern C++20 compliant compiler (GCC 11+, Clang 13+, or MSVC 2022+)

    CMake (Version 3.22 or higher)

Building the Entire Workspace

To compile the core shared library, application binary, and test suite, execute the following commands from the project root:


# 1. Initialize out-of-source build isolation architecture
cmake -B build -DCMAKE_BUILD_TYPE=Release

# 2. Compile all workspace targets
cmake --build build

# 3. Verify graph boundary integrity via CTest
cd build && ctest --output-on-failure

🗺️ Engineering Roadmap

    [x] High-performance DAG branching core implementation

    [x] Thread-safe 3-Way merge with deadlock mitigation primitives

    [ ] Direct WebAssembly (Wasm) compilation compilation targeting edge execution

    [ ] Extended schema verification rules for complex mathematical notation trees

📄 Open-Core & Licensing Philosophy

Sierralustra is open-source software licensed under the GNU Affero General Public License v3.0 (AGPL-3.0).

We are fully committed to a sustainable open-core paradigm. The fundamental mathematical graph topology, memory management, and versioning engines will always remain open, auditable, and free. Enterprise-grade collaboration controls, hosted infrastructure scales, and institutional cloud tools power our managed ecosystem at Sierralustra.com.



## 🏗️ Architectural Overview

The engine treats knowledge not as flat, sequential files, but as a Directed Acycl

[ Root Node ]
     /        \

[Branch A]    [Branch B]
|             |
(Mutation)    (Mutation)
\        /
[ Merged Node ]


When two branches merge, `sierralustra-core` resolves conflicts semantically based on node-type rules (e.g., matching mathematical expressions or hierarchical outlines) rather than arbitrary text lines.

---

## 🛠️ Getting Started

### Prerequisites

*   A modern C++20 compliant compiler (GCC 11+, Clang 13+, or MSVC 2022+)
*   CMake (3.22 or higher)
*   Doxygen (Optional, for documentation generation)

### Building from Source

```bash
# Clone the repository
git clone https://github.com/sierralustra/knowledge_graph_versioning.git
cd /sierralustra_base_core folder

# Using GCC
g++ -std=c++20 -I include/ src/main.cpp -o sierralustra_demo -pthread

# Using Clang
clang++ -std=c++20 -I include/ src/main.cpp -o sierralustra_demo -pthread



# Configure and build the project for CMake and Test results

cd sierralustra_core

Remove previous build if necessairy

# 1. Initialize empty isolation build architecture
cmake -B build -DCMAKE_BUILD_TYPE=Release

# 2. Compile every target dynamically linked .
cmake --build build

# 3. Run automated regression testing suite via CTest
cd build && ctest --output-on-failure


```
## 🧪 Testing

We run comprehensive property-based and concurrent race tests to guarantee graph consistency under heavy loads.
Bash

cd build
ctest --output-on-failure



## 📄 License & Open-Core Philosophy

sierralustra-core is licensed under the GNU Affero General Public License v3.0 (AGPL-3.0).

We are fully committed to a sustainable open-core business model. The core mathematical graph and versioning engine will always remain open and free. Commercial components, managed cloud infrastructure, and enterprise collaboration controls power the ecosystem at Sierralustra.com.
