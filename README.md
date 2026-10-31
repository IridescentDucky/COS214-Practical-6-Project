# COS214 Practical 6 Project

This repository contains the Generic Workflow, Exam Marking (Scenario 1), and Game (Scenario 2) projects, along with their design diagrams.

## Dependencies

- CMake 3.14 or newer
- A C++ compiler with C++11 support (for example, MSVC, GCC, or Clang)
- Internet access on the first CMake configure, to download GoogleTest for the test targets

Docker is only needed for the UI, not for building or running the C++ projects.

## Configure and build

Run these commands from the repository root:

```powershell
cmake -S . -B build
cmake --build build --config Debug
```

The examples below use PowerShell and assume a single-configuration generator such as MinGW Makefiles or Ninja, which places executables directly in `build`. With a multi-configuration generator such as Visual Studio, executables are usually under `build\Debug` (or the configuration you built).

## Generic Workflow

### Run

```powershell
.\build\workflow_demo.exe
```

### Test

Run the Generic Workflow test executable:

```powershell
.\build\workflow_tests.exe
```

The Generic Workflow tests cover state transitions and deadline/data validation; dependency creation and activation; invalid and duplicate dependencies; observer attach/detach and lifetime behavior; chain routing and escalation boundaries; facade handling of invalid IDs and inputs; iterator edge cases; memento restore; and prototype cloning and instance isolation.

Or run all registered tests with CTest:

```powershell
ctest --test-dir build --output-on-failure -C Debug
```

## Exam Marking (Scenario 1)

### Run

```powershell
.\build\exam_scenario1_demo.exe
```

The demo prompts for question marks and escalation flags. Enter a score for each question, then answer each escalation prompt with `y` or `n`.

### Test

```powershell
.\build\scenario1_tests.exe
```

Scenario 1 tests cover paper lifecycle transitions, validation, exceptions, pause/resume and failure; marker notification and chain routing, including Lecturer escalation; invalid and non-finite question scores and escalation resolutions; facade ownership and rejection of foreign papers; question metric calculations; cohort statistics and year filtering; and decorators/groups.

Or run all registered tests with CTest:

```powershell
ctest --test-dir build --output-on-failure -C Debug
```

## Game (Scenario 2)

Scenario 2 is not yet complete. The commands below are placeholders and will be updated when its application and tests are ready.

### Dependencies

TBD — document Scenario 2-specific dependencies, if any.

### Build

TBD — document the Scenario 2 build target and command.

### Run

TBD — document the Scenario 2 executable and run command.

### Test

TBD — document the Scenario 2 test target and command.

## Run the UI

Docker is required. From the repository root:

```powershell
docker compose up --build
```

Then open <http://localhost:8080>.

## Google Docs - research

<https://docs.google.com/document/d/18jkW9gRDppPR8AhWRa4KiVEVAtO7DtYo8ME8rW1wpag/edit?tab=t.0>

## Team members

- Isabelle Engelbrecht u25090501
- Sudud Abughazaleh u25282728
- Tamlyn Kahn u24675815
- Yoshua Smit u25433726
- Jonathan Witter u25108582

## Bonus Marks

The GitHub Actions workflow in `.github/workflows/cpp-ci.yml` configures and builds the CMake project, then runs the registered C++ tests with CTest on every push and pull request. It can also be started manually from the repository's Actions tab. The workflow reports build or test failures but does not deploy or publish executables.
