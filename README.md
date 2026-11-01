# COS214 Practical 6 Project

This repository contains TIVIDY, a generic workflow engine, along with its design diagrams. The exam marking and game scenarios run on it as workflow definitions (see below).

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

## Run the UI

Docker is required. From the repository root:

```powershell
docker compose up --build
```

Then open <http://localhost:8080>.

## One engine, any workflow
TIVIDY is a generic workflow engine. A scenario is a **workflow definition** (data) loaded into it, not new classes.
In the UI, pick a definition in the *Workflow definition* panel, or build your own, then **Apply to engine**,
or **Start fresh with example** to load the definition's sample work:

| Definition | Escalation chain | External system | Scoring |
|---|---|---|---|
| Software project | Team lead → Manager → Department head → Director → Executive | Release tracker | Average |
| Exam marking | Tutor → Assistant lecturer → Lecturer → Module coordinator | Student records system | Average |
| Game studio | Lead developer → Producer → Studio head → Publisher | Store publisher | Lowest |
| Blank | Your own (1 to 5 levels) | Your own | Your choice |

A definition sets the workflow's vocabulary (what a unit of work and its parts are called), the state names shown,
the escalation chain, the external system, the scoring rule and the names of the extra behaviours.

`code/scenario1`, `code/scenario2`, `web/scenario1` and `web/scenario2` are kept for history only. They are not built or served.

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
