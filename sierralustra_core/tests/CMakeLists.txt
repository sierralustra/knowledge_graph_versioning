
# Make sure the filename here matches your actual file exactly!
add_executable(sierralustra_test graph_tests.cpp) 
target_link_libraries(sierralustra_test PRIVATE sierralustra_core)
#add_test(NAME CoreGraphIntegrityTest COMMAND sierralustra_test)

# Add the test runner executable target
#add_executable(sierralustra_test graph_tests.cpp)

# Link the core engine library
target_link_libraries(sierralustra_test PRIVATE sierralustra_core)

# Register the test binary with the CTest framework
add_test(NAME CoreGraphIntegrityTest COMMAND sierralustra_test)

