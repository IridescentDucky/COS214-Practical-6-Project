cmake_minimum_required(VERSION 3.14)
project(GenericWorkflowDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(WORKFLOW_SOURCES
    code/generic/AbstractWorkflowFactory.cpp
    code/generic/AbstractWorkflowInstanceA.cpp
    code/generic/AbstractWorkflowInstanceB.cpp
    code/generic/Caretaker.cpp
    code/generic/Component.cpp
    code/generic/ConcreteDecoratorA.cpp
    code/generic/ConcreteDecoratorB.cpp
    code/generic/ConcreteHandler1.cpp
    code/generic/ConcreteHandler2.cpp
    code/generic/ConcreteObserver.cpp
    code/generic/ConcreteWorkflowFactory1.cpp
    code/generic/ConcreteWorkflowFactory2.cpp
    code/generic/Decorator.cpp
    code/generic/Observer.cpp
    code/generic/State.cpp
    code/generic/TIVIDY.cpp
    code/generic/WorkItem.cpp
    code/generic/WorkItemIterator.cpp
    code/generic/WorkItemMemento.cpp
    code/generic/WorkflowInstanceA1.cpp
    code/generic/WorkflowInstanceA2.cpp
    code/generic/WorkflowInstanceB1.cpp
    code/generic/WorkflowInstanceB2.cpp
    code/generic/WorkflowMediator.cpp)

add_library(workflow_core ${WORKFLOW_SOURCES})
target_include_directories(workflow_core PUBLIC code/generic)

add_executable(workflow_demo code/generic/main.cpp)
target_link_libraries(workflow_demo PRIVATE workflow_core)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://codeload.github.com/google/googletest/zip/refs/tags/release-1.12.1)
set(gtest_force_shared_crt ON CACHE BOOL "Use shared CRT on Windows" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(workflow_tests tests/workflow_tests.cpp)
target_link_libraries(workflow_tests PRIVATE workflow_core GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(workflow_tests)
