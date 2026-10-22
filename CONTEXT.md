# Project Implementation Context

## Purpose and scope

This is a C++ proof-of-concept workflow demo for showing how GoF patterns can
coexist and interact.  It is intended to represent, but not be a production workplace.

Primary completion criteria:

- implementations compile and are structurally coherent;
- focused unit tests pass, with a small number of integration tests and one
  end-to-end demonstration test;
- every existing pattern is exercised at least once by the demo, while the
  main focus is the interaction between State, Observer, and Mediator.

All implementation code must remain C++11 compatible.

## Repository layout

- `code/generic/`: the implementation to complete and test.
- `code/generic/main.cpp`: compact executable demonstration of every pattern.
- `code/scenario1/main.cpp`: empty placeholder; do not use as a second
  executable unless the build is deliberately extended to support it.
- `docs/` and `README.md`: external explanation material; leave it alone for
  implementation work unless the user explicitly asks otherwise.

The root `CMakeLists.txt` builds the `workflow_core` library, `workflow_demo`,
and `workflow_tests`.  It sets C++11 and fetches GoogleTest release 1.12.1.

## Current architecture

### Workflow core

- `TIVIDY` is the facade/client API.  It owns a `WorkflowMediator`, allocates
  numeric work-item IDs, and delegates work-item commands.
- `WorkflowMediator` owns all registered `AbstractWorkItem*` objects, supports
  lookup/listing, and coordinates dependency fan-out after completion.
- `AbstractWorkItem` stores ID, name, current `WorkItemState*`, and mediator.
- `WorkItem` is the concrete item.  It is also a `Component` (Decorator) and
  a `Subject` (Observer).
- `TIVIDY` exposes `addDependency(predecessorId, successorId)` and the
  read-only `getWorkItemState(id)` query for clients/tests.
- State classes in `State.*` implement this lifecycle:

  `Created -> Delivered -> InProgress -> Validation -> Completed -> Archived`

  Other paths include pause/resume, failed delivery, failure, exception, and
  validation rework.  `Validation::nextState` calls `notifyWorkflow()` only
  after changing to `Completed` when data is non-empty.

### Agreed Mediator behaviour

Implement explicit dependency fan-out:

- expose an API such as `addDependency(predecessorId, successorId)`;
- after a predecessor successfully completes validation, its mediator
  activates every registered successor;
- activation is one normal state advancement (`Created -> Delivered`), so the
  State pattern still owns transition logic;
- guard invalid IDs, duplicate relationships, self-dependencies, and already
  activated/non-`Created` successors in a simple, deterministic way;
- do not build scheduling, cycle detection, persistence, or a full workflow
  language for this demo.

Implemented API semantics:

- `addDependency` returns `false` for self-dependencies, missing work-item
  IDs, and duplicate edges.
- `notify` ignores non-completed colleagues and only advances successors that
  are still `Created`; this makes completion notifications idempotent for this
  proof of concept.

The main meaningful interaction is therefore:

`WorkItem State transition -> WorkItem::notifyWorkflow -> WorkflowMediator -> dependent WorkItem state transition -> Observer notifications`.

### Other pattern implementations present

- **State:** `State.*`, used by `WorkItem`.
- **Mediator:** `WorkflowMediator.*`, called from successful validation.
- **Observer:** `Observer`, `ConcreteObserver`, and `WorkItem` observer list.
- **Memento:** `WorkItemMemento` and `Caretaker`.
- **Decorator:** `Component`, `Decorator`, `ConcreteDecoratorA/B`.
- **Abstract Factory:** workflow factory/product hierarchies and
  `TIVIDY::runWorkflow`.
- **Strategy:** `Strategy` plus three concrete strategies.
- **Chain of Responsibility:** `TaskEscalationManager` plus two handlers.

## Build and tests

Use the root `CMakeLists.txt` with a CMake version of at least 3.14. It uses
C++11 and a `workflow_tests` target using GoogleTest release 1.12.1 through
`FetchContent`. Production `.cpp` files are in a reusable library target; the
demo executable and tests link to it. `scenario1/main.cpp` is intentionally
not part of the build.

Recommended test layers:

- unit: State transitions/guards, mediator relationship registration and
  fan-out, memento restore, observer attach/detach, factory product families;
- integration: completion of a predecessor activates dependents and notifies
  their observers; facade commands operate through the mediator;
- end-to-end: construct a small dependency workflow through `TIVIDY`, take it
  through valid transitions and submission, then verify final statuses.

Implemented and verified tests (`tests/workflow_tests.cpp`):

- State: validation success/rework, deadline guard, pause/resume.
- Mediator: relationship validation and fan-out to two dependents, including
  repeated-notification idempotence.
- Memento: restore of an independent state snapshot.
- Observer: attach/notify/detach behavior.
- Abstract Factory: distinct product families.
- End-to-end: facade-created predecessor completion activates its dependent.

On 2026-10-22, the suite passed: 9 tests in 6 suites.

Where behaviour currently only writes to `std::cout`, prefer adding a small
observable query/counter only if tests cannot otherwise assert meaningful
state.  Avoid making output text the primary test contract.

## Main demo requirements

The final `code/generic/main.cpp` should visibly exercise every pattern at
least once.  Keep it deterministic and compact.  Lead with the integrated
State/Observer/Mediator dependency story; then make short calls that exercise
Memento, Decorator, Abstract Factory, Strategy, and Chain of Responsibility.
Ensure stack/heap lifetime ordering is safe (observers die before the observed
item, and decorators do not outlive their wrapped component).
