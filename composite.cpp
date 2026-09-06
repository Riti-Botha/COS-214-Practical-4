#include "Composite.h"
#include "Iterator.h"

#include <iostream>

//emergency task


void dispatchAmbulance::sendOut() {
    std::cout << "\t INDIVIDUAL VEHICLE SENT OUT FOR " << description << std::endl;
}


IncidentGroup::~IncidentGroup() {
    for (int i = 0; i < children.size(); ++i) {
        delete children[i]; // delete each child
    }
    children.clear();
}

void IncidentGroup::sendOut() {
    std::cout << "New emergency: " << description << std::endl;
    
    // loop/recurse through the entire vector
    for (int i = 0; i < children.size(); i++) {
        if (children[i] != nullptr) {
            children[i]->sendOut(); // eventually will reach a leaf
        }
    }
    
    std::cout << "Completed " << description << std::endl;
}

void IncidentGroup::add(EmergencyTask* task) {
    if (task != nullptr) {
        children.push_back(task); // to end of vector
    }
}

void IncidentGroup::remove(EmergencyTask* task) {
    for (int i = 0; i < children.size(); i++) {
        if (children[i] == task) {
            delete children[i]; // delete the child
            children.erase(children.begin() + i); // shifts all elements one spot to the left
            break; 
        }
    }
}

TaskIterator* IncidentGroup::createIterator() {
    return new DepthFirstIterator(children);
}

TaskIterator* IncidentGroup::createReverseIterator() {
    return new ReverseIterator(children);
}
