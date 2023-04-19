
cmake_minimum_required(VERSION 3.10)

project(MetricGraphs VERSION 1.0)
find_package(GTest CONFIG REQUIRED)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

include_directories(${PROJECT_SOURCE_DIR})

add_executable(MetricGraphs main.cpp src/graphs/universalGraph.cpp
                            src/graphs/trees/generalTree.cpp
                            src/simulation/simulation.cpp
                            src/simulation/verification/baseGenerator.cpp
                            src/simulation/verification/treeGenerator.cpp)

target_link_libraries(MetricGraphs gmp gmpxx)

add_executable(MetricTreeAutotest src/simulation/verification/autoTreeVerification.cpp
        src/graphs/universalGraph.cpp
        src/graphs/trees/generalTree.cpp
        src/simulation/simulation.cpp
        src/simulation/verification/baseGenerator.cpp
        src/simulation/verification/treeGenerator.cpp)

target_link_libraries(MetricTreeAutotest gmp gmpxx)

enable_testing()

add_executable(
        treeTest
        test/treeTest.cpp
        src/graphs/universalGraph.cpp
        src/graphs/trees/generalTree.cpp
        src/simulation/simulation.cpp
        src/simulation/verification/baseGenerator.cpp
        src/simulation/verification/treeGenerator.cpp
)
target_link_libraries(
        treeTest
        GTest::gtest_main
        gmp
        gmpxx
)

add_executable(
        formulaTest
        test/formulaSimulationTest.cpp
        src/graphs/universalGraph.cpp
        src/graphs/trees/generalTree.cpp
        src/simulation/simulation.cpp
        src/simulation/verification/baseGenerator.cpp
        src/simulation/verification/treeGenerator.cpp
        src/simulation/verification/chainGenerator.cpp
)

target_link_libraries(
        formulaTest
        GTest::gtest_main
        gmp
        gmpxx
)

include(GoogleTest)
gtest_discover_tests(treeTest)