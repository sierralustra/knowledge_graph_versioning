
cmake_minimum_required(VERSION 3.22)
project(SierralustraEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

# Define Core Shared Library Primitive
add_library(sierralustra_core src/knowledge_graph.cpp)
target_include_directories(sierralustra_core PUBLIC include)
target_link_libraries(sierralustra_core PRIVATE Threads::Threads)

if(MSVC)
    target_compile_options(sierralustra_core PRIVATE /W4 /WX)
else()
    target_compile_options(sierralustra_core PRIVATE -Wall -Wextra -Werror)
endif()

# Enable testing framework globally
enable_testing()

# CRITICAL CHECK: Ensure each directory is added ONLY ONCE here
add_subdirectory(apps)
add_subdirectory(tests)
