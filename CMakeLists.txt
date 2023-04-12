
cmake_minimum_required(VERSION 3.10)

project(MetricGraphs VERSION 1.0)
find_package(GTest CONFIG REQUIRED)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

include_directories(${PROJECT_SOURCE_DIR})

add_executable(MetricGraphs main.cpp src/graphs/universalGraph.cpp src/graphs/trees/generalTree.cpp src/simulation/simulation.cpp)
target_link_libraries(MetricGraphs gmp gmpxx)

enable_testing()

add_executable(
        treeTest
        test/treeTest.cpp
        src/graphs/universalGraph.cpp
        src/graphs/trees/generalTree.cpp
)
target_link_libraries(
        treeTest
        GTest::gtest_main
        gmp
        gmpxx
)

include(GoogleTest)
gtest_discover_tests(treeTest)