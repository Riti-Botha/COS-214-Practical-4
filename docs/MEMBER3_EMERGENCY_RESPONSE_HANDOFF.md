# Member 3: Emergency Response Integration Handoff

## Theme alignment

The current team implementation models **city emergency management**. `EmergencyTask` represents a dispatchable emergency action; `IncidentGroup` represents a nested incident or command grouping; and `dispatchAmbulance` is the concrete field-response leaf. Member 3's work follows that same vocabulary and uses the existing `EmergencyTask` interface directly.

The two Member 3 decorators are:

- `PriorityDispatchDecorator`: marks a response as urgent and announces that it must be dispatched first.
- `AuditDispatchDecorator`: records dispatch start and completion in an `EmergencyAuditLog`.

They are stackable. The live program creates `AuditDispatchDecorator(PriorityDispatchDecorator(dispatchAmbulance))` for trapped-worker and hazmat responses. Because every decorator remains an `EmergencyTask`, an `IncidentGroup` owns, dispatches and traverses decorated tasks exactly as it does ordinary vehicles.

## Ownership rationale

`IncidentGroup` owns raw `EmergencyTask*` children and deletes them in its destructor. `EmergencyTaskDecorator` therefore owns its wrapped `EmergencyTask*` and deletes it in its own destructor. When a group deletes a decorator, the decorator deletes its wrapped task exactly once. `EmergencyAuditLog` is non-owning inside the audit decorator; it is created before the hierarchy and remains alive until after the hierarchy is deleted.

## Existing-traversal policy

The team's iterators copy the group's current child pointer sequence when constructed. TaskForge therefore uses an **add-only snapshot policy while an iterator is active**:

- Adding a new response is safe; an existing iterator keeps its original membership and a fresh iterator sees the new response.
- Removing or replacing an existing response is deferred until all iterators that could reference it are destroyed. This avoids dangling pointers in the current raw-pointer iterator implementation.

Scenario 2 in `main.cpp` verifies this policy by adding an audited, priority-decorated hazmat unit after creating a depth-first snapshot. The existing snapshot does not see it; the fresh snapshot does.

## GoF mapping (current integration)

| Pattern | Participant | Current class |
| --- | --- | --- |
| Composite | Component | `EmergencyTask` |
| Composite | Leaf | `dispatchAmbulance` |
| Composite | Composite | `IncidentGroup` |
| Iterator | Iterator | `TaskIterator` |
| Iterator | Concrete iterators | `DepthFirstIterator`, `ReverseIterator`, `StandardIterator`, `NullIterator` |
| Decorator | Component | `EmergencyTask` |
| Decorator | Decorator | `EmergencyTaskDecorator` |
| Decorator | Concrete decorators | `PriorityDispatchDecorator`, `AuditDispatchDecorator` |

State is deliberately not introduced in this handoff: there is no State implementation in the fetched team commits yet, and its integration remains Member 2's allocated responsibility. Once that code arrives, `main.cpp` should invoke its lifecycle transitions through `EmergencyTask` without changing the decorators' substitutability.

## Scenario coverage

1. **Coordinated power-plant fire response**: the hierarchy has three incident-group levels below the command root before vehicle tasks. Composite dispatch, depth-first traversal, reverse traversal and stacked decorator dispatch occur together.
2. **New hazard during an active incident**: an iterator snapshot exists, an audited priority hazmat unit is added at runtime, and old versus fresh snapshot visibility is demonstrated and checked.

## UML material

- `docs/diagrams/member3-emergency-class-diagram.puml`
- `docs/diagrams/member3-emergency-object-diagram.puml`
- `docs/diagrams/member3-emergency-response-activity.puml`

PNG and SVG exports are generated alongside each PlantUML source.

## Final PDF contribution draft

Member 3 implemented the runtime Decorator collaboration for the emergency-management domain. `PriorityDispatchDecorator` marks a vehicle response as urgent, while `AuditDispatchDecorator` records dispatch outcomes; both are stackable and operate through the same `EmergencyTask` abstraction as undecorated responses. Member 3 also wrote the integrated city emergency scenarios, documented the add-only snapshot policy for live incident changes, supplied the object/activity/class diagram material, and added Docker support. State behavior remains Member 2's integration responsibility; after it is merged, the team must update the final scenario narrative and GoF mapping to reference the actual State classes and commits.

## Verification

```sh
make clean
make
./taskforge
docker build -t taskforge-env .
docker run --rm taskforge-env
```

No commit, push, issue or pull request was created by Member 3 during this alignment pass.
