cmake_minimum_required(VERSION 3.14)
project(GenericWorkflowDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(WORKFLOW_SOURCES
    code/generic/AbstractWorkItem.cpp
    code/generic/Adaptee.cpp
    code/generic/Adapter.cpp
    code/generic/BonusScoreDecorator.cpp
    code/generic/BonusTimeDecorator.cpp
    code/generic/Caretaker.cpp
    code/generic/Component.cpp
    code/generic/Composite.cpp
    code/generic/ConcreteCreator.cpp
    code/generic/ConcreteHandler.cpp
    code/generic/ConcreteObserver.cpp
    code/generic/ConcreteStrategyA.cpp
    code/generic/ConcreteStrategyB.cpp
    code/generic/ConcreteStrategyC.cpp
    code/generic/Creator.cpp
    code/generic/Decorator.cpp
    code/generic/Observer.cpp
    code/generic/State.cpp
    code/generic/TIVIDY.cpp
    code/generic/TaskEscalationManager.cpp
    code/generic/WorkItem.cpp
    code/generic/WorkItemIterator.cpp
    code/generic/WorkItemMemento.cpp
    code/generic/WorkflowMediator.cpp)

add_library(workflow_core ${WORKFLOW_SOURCES})
target_include_directories(workflow_core PUBLIC code/generic)

add_executable(workflow_demo code/generic/main.cpp)
target_link_libraries(workflow_demo PRIVATE workflow_core)

add_library(game_core
    code/scenario2/Game.cpp
    code/scenario2/GameState.cpp)
target_include_directories(game_core PUBLIC code/scenario2)

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
