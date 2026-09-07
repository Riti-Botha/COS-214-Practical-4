#ifndef COMPOSITE_H
#define COMPOSITE_H
#include "Iterator.h"
#include <string>
#include <vector>

class TaskIterator;
class TaskState;

// component (so this is the base class)
class EmergencyTask {
protected:
    std::string description;
 
public:
    EmergencyTask(const std::string& desc) : description(desc) {}
    virtual ~EmergencyTask() = default; 

    virtual void sendOut() = 0; 
    virtual void add(EmergencyTask* task) {}
    virtual void remove(EmergencyTask* task) {}

    virtual std::string getDescription() const { return description; }
    virtual TaskIterator* createIterator() = 0; 
    virtual TaskIterator* createReverseIterator() = 0;

};

// LEAF (individual emergency action)
// also the CONTEXT for the State pattern: its lifecycle is delegated to currentState
class dispatchAmbulance : public EmergencyTask {
private:
    TaskState* currentState;

public:
    dispatchAmbulance(const std::string& desc);
    ~dispatchAmbulance() override;

    void sendOut();

    // used by TaskState subclasses to transition the context to a new state
    void setState(TaskState* newState);
    std::string getStateName() const;

    // lifecycle actions, delegated to currentState
    void dispatch();
    void arrive();
    void complete();
    void cancel();

    TaskIterator* createIterator() override { return nullptr; } // leaves do not have children, so they return a null iterator
    TaskIterator* createReverseIterator() override { return nullptr; } // leaves do not have children, so they return a null iterator


};

// COMPOSITE (so vector of )
class IncidentGroup : public EmergencyTask { // so let's say IncidentGroup* fireIncident = new IncidentGroup("Fire");
private:
    std::vector<EmergencyTask*> children; 

public:
    IncidentGroup(const std::string& desc) : EmergencyTask(desc) {}
    ~IncidentGroup() override;
    void sendOut() override;
    void add(EmergencyTask* task) override;
    void remove(EmergencyTask* task) override;

    TaskIterator* createIterator() override;
    TaskIterator* createReverseIterator() override;
};

#endif
