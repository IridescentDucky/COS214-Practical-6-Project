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
    code/generic/ConcreteHandlerA.cpp
    code/generic/ConcreteHandlerB.cpp
    code/generic/ConcreteHandlerC.cpp
    code/generic/ConcreteHandlerD.cpp
    code/generic/ConcreteHandlerE.cpp
    code/generic/ConcreteStrategyA.cpp
    code/generic/ConcreteStrategyB.cpp
    code/generic/ConcreteStrategyC.cpp
    code/generic/Creator.cpp
    code/generic/Decorator.cpp
    code/generic/PrototypeManager.cpp
    code/generic/State.cpp
    code/generic/TIVIDY.cpp
    code/generic/TaskEscalationManager.cpp
    code/generic/WorkItem.cpp
    code/generic/WorkItemIterator.cpp
    code/generic/WorkItemMemento.cpp
    code/generic/WorkflowMediator.cpp
    code/generic/StatsCaretaker.cpp)

add_library(workflow_core ${WORKFLOW_SOURCES})
target_include_directories(workflow_core PUBLIC code/generic)

add_executable(workflow_demo code/generic/main.cpp)
target_link_libraries(workflow_demo PRIVATE workflow_core)

set(EXAM_SCENARIO_SOURCES
    code/scenario1/AbstractExamPaper.cpp
    code/scenario1/ConcessionDecorator.cpp
    code/scenario1/Creator.cpp
    code/scenario1/ExamComponent.cpp
    code/scenario1/ExamDecorator.cpp
    code/scenario1/ExamDelivery.cpp
    code/scenario1/ExamDeliveryService.cpp
    code/scenario1/ExamMarkingFacade.cpp
    code/scenario1/ExamPaper.cpp
    code/scenario1/ExamPaperCollection.cpp
    code/scenario1/ExamPaperCreator.cpp
    code/scenario1/ExamPaperGroup.cpp
    code/scenario1/ExamPaperIterator.cpp
    code/scenario1/AverageMarksStrategy.cpp
    code/scenario1/ExamStatisticsOriginator.cpp
    code/scenario1/ExtraMarksDecorator.cpp
    code/scenario1/Marker.cpp
    code/scenario1/LowestMarkStrategy.cpp
    code/scenario1/Markers.cpp
    code/scenario1/States.cpp
    code/scenario1/StatisticsCaretaker.cpp
    code/scenario1/TopMarkStrategy.cpp)

add_library(exam_scenario1_core ${EXAM_SCENARIO_SOURCES})
target_include_directories(exam_scenario1_core PUBLIC code/scenario1)

add_executable(exam_scenario1_demo code/scenario1/main.cpp)
target_link_libraries(exam_scenario1_demo PRIVATE exam_scenario1_core)

add_library(game_core
    code/scenario2/Game.cpp
    code/scenario2/GameState.cpp)
target_include_directories(game_core PUBLIC code/scenario2)

add_executable(exam_demo
    code/scenario1/StatsStrategies.cpp
    code/scenario1/main.cpp)
target_link_libraries(exam_demo PRIVATE exam_scenario1_core)
target_include_directories(exam_demo PRIVATE code/scenario1)

include(FetchContent)
# Keep older fetched projects compatible with current CMake policy diagnostics.
set(CMAKE_POLICY_VERSION_MINIMUM 3.10)
FetchContent_Declare(
    googletest
    URL https://codeload.github.com/google/googletest/zip/refs/tags/release-1.12.1
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE)
set(gtest_force_shared_crt ON CACHE BOOL "Use shared CRT on Windows" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(workflow_tests tests/workflow_tests.cpp)
target_link_libraries(workflow_tests PRIVATE workflow_core GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(workflow_tests)

add_executable(scenario1_tests tests/scenario1_tests.cpp)
target_link_libraries(scenario1_tests PRIVATE exam_scenario1_core GTest::gtest_main)
gtest_discover_tests(scenario1_tests)
