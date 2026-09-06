#ifndef ITERATOR_H
#define ITERATOR_H

#include <vector>

// forward declaration of the component
class EmergencyTask;

// ITERATOR INTERFACE (base class)
class TaskIterator {
public:
    virtual ~TaskIterator() = default;
    
    // standard iterator methods
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual EmergencyTask* currentItem() const = 0;
};

// CONCRETE ITERATOR 1
class StandardIterator : public TaskIterator {
private:
    std::vector<EmergencyTask*> tasks;
    size_t currentPos;

public:
    StandardIterator(const std::vector<EmergencyTask*>& subTasks);
    ~StandardIterator() override = default;

    void first() override;
    void next() override;
    bool isDone() const override;
    EmergencyTask* currentItem() const override;
};

// CONCRETE ITERATOR 2
class ReverseIterator : public TaskIterator {
private:
    std::vector<EmergencyTask*> tasks;
    int currentPos;

public:
    ReverseIterator(const std::vector<EmergencyTask*>& subTasks);
    ~ReverseIterator() override = default;

    void first() override;
    void next() override;
    bool isDone() const override;
    EmergencyTask* currentItem() const override;
};


// CONCRETE ITERATOR 3 (Complete Depth-First Traversal)
class DepthFirstIterator : public TaskIterator {
private:
    std::vector<EmergencyTask*> tasks; // flat copy
    size_t currentPos;

public:
    DepthFirstIterator(const std::vector<EmergencyTask*>& subTasks);
    ~DepthFirstIterator() override = default;

    void first() override;
    void next() override;
    bool isDone() const override;
    EmergencyTask* currentItem() const override;
};

#endif