#include "Composite.h"
#include "Iterator.h"
#include <iostream>

int main() {
    EmergencyTask* EmergencyMngr = new IncidentGroup("City Emergencies");

    //level 1 composites in root component
    EmergencyTask* City1 = new IncidentGroup("City 1 emergency");
    EmergencyTask* City2 = new IncidentGroup("City 2 emergency");

    // level 2 composites in each city
    EmergencyTask* powerPlantFire = new IncidentGroup("Power plant fire emergency");
    EmergencyTask* highwayCrash = new IncidentGroup("Highway crash emergency");

    // level 3 leaves
    EmergencyTask* fireTruck1 = new dispatchAmbulance("Truck 1 to power plant");
    EmergencyTask* fireTruck2 = new dispatchAmbulance("Truck 2 to power plant");
    EmergencyTask* ambulance1 = new dispatchAmbulance("Ambulance 1 to highway");
    EmergencyTask* ambulance2 = new dispatchAmbulance("Ambulance 2 to highway");


    powerPlantFire->add(fireTruck1);
    powerPlantFire->add(fireTruck2);
    highwayCrash->add(ambulance1);
    City1->add(ambulance2);

    City1->add(powerPlantFire);
    City2->add(highwayCrash);

    EmergencyMngr->add(City1);
    EmergencyMngr->add(City2);

    //test composite
    EmergencyMngr->sendOut(); // recursive traversal

    // depth first iterator test
    TaskIterator* dfIt = City1->createIterator();
    for (dfIt->first(); !dfIt->isDone(); dfIt->next()) {
        EmergencyTask* task = dfIt->currentItem();
        if (task != nullptr) {
            std::cout << "DF: " << task->getDescription() << std::endl;
        }
    }
    delete dfIt;

    // reverse iterator test
    TaskIterator* revIt = City1->createReverseIterator();
    for (revIt->first(); !revIt->isDone(); revIt->next()) {
        EmergencyTask* task = revIt->currentItem();
        if (task != nullptr) {
            std::cout << "Reverse: " << task->getDescription() << std::endl;
        }
    }
    delete revIt;

    delete EmergencyMngr;

    return 0;
}
