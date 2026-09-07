#ifndef STATE_H
#define STATE_H

#include <string>

// forward declaration of the context
class dispatchAmbulance;

// STATE (abstract base class)
class TaskState {
public:
    virtual ~TaskState() = default;

    virtual void dispatch(dispatchAmbulance* context) = 0;
    virtual void arrive(dispatchAmbulance* context) = 0;
    virtual void complete(dispatchAmbulance* context) = 0;
    virtual void cancel(dispatchAmbulance* context) = 0;

    virtual std::string getStateName() const = 0;
};

// CONCRETE STATE 1
class PendingState : public TaskState {
public:
    void dispatch(dispatchAmbulance* context) override;
    void arrive(dispatchAmbulance* context) override;
    void complete(dispatchAmbulance* context) override;
    void cancel(dispatchAmbulance* context) override;

    std::string getStateName() const override { return "Pending"; }
};

// CONCRETE STATE 2
class DispatchedState : public TaskState {
public:
    void dispatch(dispatchAmbulance* context) override;
    void arrive(dispatchAmbulance* context) override;
    void complete(dispatchAmbulance* context) override;
    void cancel(dispatchAmbulance* context) override;

    std::string getStateName() const override { return "Dispatched"; }
};

// CONCRETE STATE 3
class EnRouteState : public TaskState {
public:
    void dispatch(dispatchAmbulance* context) override;
    void arrive(dispatchAmbulance* context) override;
    void complete(dispatchAmbulance* context) override;
    void cancel(dispatchAmbulance* context) override;

    std::string getStateName() const override { return "En Route"; }
};

// CONCRETE STATE 4
class OnSceneState : public TaskState {
public:
    void dispatch(dispatchAmbulance* context) override;
    void arrive(dispatchAmbulance* context) override;
    void complete(dispatchAmbulance* context) override;
    void cancel(dispatchAmbulance* context) override;

    std::string getStateName() const override { return "On Scene"; }
};

// CONCRETE STATE 5
class CompletedState : public TaskState {
public:
    void dispatch(dispatchAmbulance* context) override;
    void arrive(dispatchAmbulance* context) override;
    void complete(dispatchAmbulance* context) override;
    void cancel(dispatchAmbulance* context) override;

    std::string getStateName() const override { return "Completed"; }
};

// CONCRETE STATE 6 (reachable from Pending, Dispatched or En Route only)
class CancelledState : public TaskState {
public:
    void dispatch(dispatchAmbulance* context) override;
    void arrive(dispatchAmbulance* context) override;
    void complete(dispatchAmbulance* context) override;
    void cancel(dispatchAmbulance* context) override;

    std::string getStateName() const override { return "Cancelled"; }
};

#endif
