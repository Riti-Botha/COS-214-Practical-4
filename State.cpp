#include "State.h"
#include "Composite.h"

// ===== PendingState =====
// TODO: dispatch() -> valid, moves to DispatchedState
void PendingState::dispatch(dispatchAmbulance* context) {}
// TODO: arrive() -> invalid, must be dispatched first
void PendingState::arrive(dispatchAmbulance* context) {}
// TODO: complete() -> invalid, must be dispatched first
void PendingState::complete(dispatchAmbulance* context) {}
// TODO: cancel() -> valid, moves to CancelledState
void PendingState::cancel(dispatchAmbulance* context) {}

// ===== DispatchedState =====
// TODO: dispatch() -> invalid, already dispatched
void DispatchedState::dispatch(dispatchAmbulance* context) {}
// TODO: arrive() -> valid, moves to EnRouteState
void DispatchedState::arrive(dispatchAmbulance* context) {}
// TODO: complete() -> invalid, must arrive on scene first
void DispatchedState::complete(dispatchAmbulance* context) {}
// TODO: cancel() -> valid, moves to CancelledState
void DispatchedState::cancel(dispatchAmbulance* context) {}

// ===== EnRouteState =====
// TODO: dispatch() -> invalid, already dispatched
void EnRouteState::dispatch(dispatchAmbulance* context) {}
// TODO: arrive() -> valid, moves to OnSceneState
void EnRouteState::arrive(dispatchAmbulance* context) {}
// TODO: complete() -> invalid, must arrive on scene first
void EnRouteState::complete(dispatchAmbulance* context) {}
// TODO: cancel() -> valid, moves to CancelledState
void EnRouteState::cancel(dispatchAmbulance* context) {}

// ===== OnSceneState =====
// TODO: dispatch() -> invalid, already en route/on scene
void OnSceneState::dispatch(dispatchAmbulance* context) {}
// TODO: arrive() -> invalid, already on scene
void OnSceneState::arrive(dispatchAmbulance* context) {}
// TODO: complete() -> valid, moves to CompletedState
void OnSceneState::complete(dispatchAmbulance* context) {}
// TODO: cancel() -> invalid, response already committed on scene
void OnSceneState::cancel(dispatchAmbulance* context) {}

// ===== CompletedState (terminal) =====
// TODO: dispatch() -> invalid, task already finished
void CompletedState::dispatch(dispatchAmbulance* context) {}
// TODO: arrive() -> invalid, task already finished
void CompletedState::arrive(dispatchAmbulance* context) {}
// TODO: complete() -> invalid, already completed
void CompletedState::complete(dispatchAmbulance* context) {}
// TODO: cancel() -> invalid, cannot cancel a finished task
void CompletedState::cancel(dispatchAmbulance* context) {}

// ===== CancelledState (terminal) =====
// TODO: dispatch() -> invalid, task was cancelled
void CancelledState::dispatch(dispatchAmbulance* context) {}
// TODO: arrive() -> invalid, task was cancelled
void CancelledState::arrive(dispatchAmbulance* context) {}
// TODO: complete() -> invalid, task was cancelled
void CancelledState::complete(dispatchAmbulance* context) {}
// TODO: cancel() -> invalid, already cancelled
void CancelledState::cancel(dispatchAmbulance* context) {}
