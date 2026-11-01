# Generic Workflow API

This reference documents the reusable C++11 workflow engine in `code/generic`.
The module models work items, their lifecycle, task scores, time limits, and
dependencies, and provides extension points for custom workflow policies.

## Starting point

Use `TIVIDY<T>` as the facade for creating and managing work items. It assigns
work-item IDs and provides operations to advance, pause, resume, and submit
work, record time, manage tasks, configure escalation, and add dependencies.

## Main components

- `WorkItem<T>` implements a work item; `AbstractWorkItem<T>` defines its
  common interface. `State<T>` and its concrete states control lifecycle
  transitions.
- `WorkflowMediator<T>` coordinates registered work items, dependencies,
  completion notifications, strategies, escalation chains, and external
  system reporting.
- `Creator<T>` and `ConcreteCreator<T>` construct work items.
  `PrototypeManager<T>` stores templates that can be cloned.
- `Strategy<T>` provides replaceable scoring calculations.
- `TaskEscalationManager<T>` and its concrete handlers process escalation
  thresholds and observe work-item changes.
- `Iterator<T>` traverses work items. `Component<T>`, `Composite<T>`, and
  `Decorator<T>` provide grouping and score/time extensions.
- `WorkItemMemento<T>` and `Caretaker<T>` save and restore work-item state.
  `StatsMemento` and `StatsCaretaker` do the same for calculated statistics.
- `Adapter` exposes the external system through the `Target` interface.

Browse **Classes** for type documentation and **Files** for source and header
references, including generated dependency, inheritance, and collaboration
diagrams.

## Regenerating this reference

From the repository root, run:

```text
doxygen Doxyfile
```

The generated HTML is written to `docs/api/generic`.
