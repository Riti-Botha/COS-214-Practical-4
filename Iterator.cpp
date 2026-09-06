#include "Iterator.h"
#include "Composite.h" 

// CONCRETE ITERATOR 1
// we use snapshot traversal, so we make a flat copy of the vector of children and traverse that
StandardIterator::StandardIterator(const std::vector<EmergencyTask*>& subTasks) {
    tasks = subTasks; // here we make a flat copy of the vector of children and traverse that
    currentPos = 0;
}

void StandardIterator::first() {
    currentPos = 0; // reset to beginning
}

void StandardIterator::next() {
    if (!isDone()) {
        currentPos++;
    }
}

bool StandardIterator::isDone() const {
    return currentPos >= tasks.size();
}

EmergencyTask* StandardIterator::currentItem() const {
    if (isDone()) {
        return nullptr;
    }
    return tasks[currentPos];
}

// CONCRETE ITERATOR 2

ReverseIterator::ReverseIterator(const std::vector<EmergencyTask*>& subTasks) {
    tasks = subTasks; // here we make a flat copy of the vector of children and traverse that

    int size = tasks.size();
    currentPos = size - 1; 
}

void ReverseIterator::first() {
    int size = tasks.size();
    currentPos = size - 1;
}

void ReverseIterator::next() {
    if (!isDone()) {
        currentPos--;
    }
}

bool ReverseIterator::isDone() const {
    return currentPos < 0;
}

EmergencyTask* ReverseIterator::currentItem() const {
    if (isDone()) {
        return nullptr;
    }
    return tasks[currentPos];
}

// CONCRETE ITERATOR 3

DepthFirstIterator::DepthFirstIterator(const std::vector<EmergencyTask*>& subTasks) { // we pass a reference because we don't want to copy the vector, but we will make a flat copy of the vector of children and traverse that
    currentPos = 0;
    for (int i = 0; i < subTasks.size(); i++) {
        EmergencyTask* task = subTasks[i];
        
        // this is a recursive traversal, so we will add the task to the flat copy and then traverse its children if it has any
        if (task != nullptr) {
            tasks.push_back(task);
            
            
            TaskIterator* subIt = task->createIterator(); // this line call createIterator because we are using the composite pattern, so we don't know if the task is a leaf or a composite, so we call createIterator to get the iterator for the task, and then we use that iterator to traverse the children of the task
            
            // here we check if the subIt is not null, because if it is null, then the task is a leaf and we don't need to traverse its children, but if it is not null, then the task is a composite and we need to traverse its children
            if (subIt != nullptr) {
                for (subIt->first(); !subIt->isDone(); subIt->next()) {
                    tasks.push_back(subIt->currentItem());
                }
                delete subIt; 
            }
        }
    }
}

void DepthFirstIterator::first() {
    currentPos = 0;
}

void DepthFirstIterator::next() {
    if (!isDone()) {
        currentPos++;
    }
}

bool DepthFirstIterator::isDone() const {
    return currentPos >= tasks.size();
}

EmergencyTask* DepthFirstIterator::currentItem() const { // this method returns the current item in the iterator, which is the current task in the flat copy of the vector of children, and if the iterator is done, then it returns nullptr
    if (isDone()) {
        return nullptr;
    }
    return tasks[currentPos];
}
