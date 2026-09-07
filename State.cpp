#include "State.h"
#include "Composite.h"

#include <iostream>

namespace {

void rejectTransition(const dispatchAmbulance* context, const std::string& action) {
    std::cout << "\t [REJECTED] Cannot " << action << " \"" << context->getDescription()
              << "\" while in state: " << context->getStateName() << std::endl;
}

}  // namespace

// ===== PendingState =====
void PendingState::dispatch(dispatchAmbulance* context) {
    std::cout << "\t [STATE] " << context->getDescription()
              << " dispatched: Pending -> Dispatched" << std::endl;
    context->setState(new DispatchedState());
}
void PendingState::arrive(dispatchAmbulance* context) {
    rejectTransition(context, "arrive on scene (not dispatched yet)");
}
void PendingState::complete(dispatchAmbulance* context) {
    rejectTransition(context, "complete (not dispatched yet)");
}
void PendingState::cancel(dispatchAmbulance* context) {
    std::cout << "\t [STATE] " << context->getDescription()
              << " cancelled: Pending -> Cancelled" << std::endl;
    context->setState(new CancelledState());
}

// ===== DispatchedState =====
void DispatchedState::dispatch(dispatchAmbulance* context) {
    rejectTransition(context, "dispatch (already dispatched)");
}
void DispatchedState::arrive(dispatchAmbulance* context) {
    std::cout << "\t [STATE] " << context->getDescription()
              << " en route: Dispatched -> En Route" << std::endl;
    context->setState(new EnRouteState());
}
void DispatchedState::complete(dispatchAmbulance* context) {
    rejectTransition(context, "complete (not on scene yet)");
}
void DispatchedState::cancel(dispatchAmbulance* context) {
    std::cout << "\t [STATE] " << context->getDescription()
              << " cancelled: Dispatched -> Cancelled" << std::endl;
    context->setState(new CancelledState());
}

// ===== EnRouteState =====
void EnRouteState::dispatch(dispatchAmbulance* context) {
    rejectTransition(context, "dispatch (already dispatched)");
}
void EnRouteState::arrive(dispatchAmbulance* context) {
    std::cout << "\t [STATE] " << context->getDescription()
              << " on scene: En Route -> On Scene" << std::endl;
    context->setState(new OnSceneState());
}
void EnRouteState::complete(dispatchAmbulance* context) {
    rejectTransition(context, "complete (not on scene yet)");
}
void EnRouteState::cancel(dispatchAmbulance* context) {
    std::cout << "\t [STATE] " << context->getDescription()
              << " cancelled: En Route -> Cancelled" << std::endl;
    context->setState(new CancelledState());
}

// ===== OnSceneState =====
void OnSceneState::dispatch(dispatchAmbulance* context) {
    rejectTransition(context, "dispatch (already en route/on scene)");
}
void OnSceneState::arrive(dispatchAmbulance* context) {
    rejectTransition(context, "arrive on scene (already on scene)");
}
void OnSceneState::complete(dispatchAmbulance* context) {
    std::cout << "\t [STATE] " << context->getDescription()
              << " completed: On Scene -> Completed" << std::endl;
    context->setState(new CompletedState());
}
void OnSceneState::cancel(dispatchAmbulance* context) {
    rejectTransition(context, "cancel (response already committed on scene)");
}

// ===== CompletedState (terminal) =====
void CompletedState::dispatch(dispatchAmbulance* context) {
    rejectTransition(context, "dispatch (task already completed)");
}
void CompletedState::arrive(dispatchAmbulance* context) {
    rejectTransition(context, "arrive on scene (task already completed)");
}
void CompletedState::complete(dispatchAmbulance* context) {
    rejectTransition(context, "complete (already completed)");
}
void CompletedState::cancel(dispatchAmbulance* context) {
    rejectTransition(context, "cancel (task already completed)");
}

// ===== CancelledState (terminal) =====
void CancelledState::dispatch(dispatchAmbulance* context) {
    rejectTransition(context, "dispatch (task was cancelled)");
}
void CancelledState::arrive(dispatchAmbulance* context) {
    rejectTransition(context, "arrive on scene (task was cancelled)");
}
void CancelledState::complete(dispatchAmbulance* context) {
    rejectTransition(context, "complete (task was cancelled)");
}
void CancelledState::cancel(dispatchAmbulance* context) {
    rejectTransition(context, "cancel (already cancelled)");
}
