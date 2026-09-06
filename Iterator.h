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
    int currentPos;

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
    int currentPos;

public:
    DepthFirstIterator(const std::vector<EmergencyTask*>& subTasks);
    ~DepthFirstIterator() override = default;

    void first() override;
    void next() override;
    bool isDone() const override;
    EmergencyTask* currentItem() const override;
};

// CONCRETE ITERATOR 4 (Null Iterator for Leaf Nodes)
class NullIterator : public TaskIterator {
public:
    NullIterator() = default;
    ~NullIterator() override = default;

    void first() override {}
    void next() override {}
    bool isDone() const override { return true;}
    EmergencyTask* currentItem() const override { return nullptr; } // nullptr because isDone() is true, no children, so not iterating anymore, so not at a current object
};

#endif
