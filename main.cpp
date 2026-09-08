#include "Composite.h"
#include "Decorator.h"
#include "Iterator.h"

#include <iostream>
#include <memory>
#include <stdexcept>

namespace {

void printTraversal(const std::string& heading, TaskIterator* iterator) {
    std::unique_ptr<TaskIterator> managedIterator(iterator);
    std::cout << heading << std::endl;
    if (!managedIterator) {
        std::cout << "  (leaf nodes have no children to traverse)" << std::endl;
        return;
    }

    for (managedIterator->first(); !managedIterator->isDone(); managedIterator->next()) {
        EmergencyTask* task = managedIterator->currentItem();
        if (task != nullptr) {
            std::cout << "  - " << task->getDescription() << std::endl;
        }
    }
}

void scenarioOne(EmergencyTask* cityEmergencyManager,
                 IncidentGroup* powerPlantFire,
                 EmergencyAuditLog& auditLog) {
    std::cout << "\n=== Scenario 1: coordinated power-plant fire response ===" << std::endl;
    std::cout << "The city manager dispatches a nested incident hierarchy." << std::endl;

    cityEmergencyManager->sendOut();

    printTraversal("\nDepth-first incident view:",
                   cityEmergencyManager->createIterator());
    printTraversal("\nReverse direct-unit view of the power-plant incident:",
                   powerPlantFire->createReverseIterator());

    std::cout << "\nAudit trail for the stacked dispatch decorators:" << std::endl;
    auditLog.writeTo(std::cout);
}

void scenarioTwo(IncidentGroup* powerPlantFire, EmergencyAuditLog& auditLog) {
    std::cout << "\n=== Scenario 2: new hazard during an active incident ===" << std::endl;
    std::cout << "A depth-first snapshot is created before a hazmat team is added." << std::endl;

    std::unique_ptr<TaskIterator> existingSnapshot(powerPlantFire->createIterator());
    if (!existingSnapshot) {
        throw std::runtime_error("Expected an incident group iterator.");
    }

    powerPlantFire->add(new AuditDispatchDecorator(
        new PriorityDispatchDecorator(
            new dispatchAmbulance("Hazmat unit to chemical storage"),
            "P1 - escalating chemical risk"),
        &auditLog));

    bool oldSnapshotSawHazmat = false;
    for (existingSnapshot->first(); !existingSnapshot->isDone(); existingSnapshot->next()) {
        EmergencyTask* task = existingSnapshot->currentItem();
        if (task != nullptr && task->getDescription().find("Hazmat") != std::string::npos) {
            oldSnapshotSawHazmat = true;
        }
    }

    bool freshSnapshotSawHazmat = false;
    std::unique_ptr<TaskIterator> freshSnapshot(powerPlantFire->createIterator());
    for (freshSnapshot->first(); !freshSnapshot->isDone(); freshSnapshot->next()) {
        EmergencyTask* task = freshSnapshot->currentItem();
        if (task != nullptr && task->getDescription().find("Hazmat") != std::string::npos) {
            freshSnapshotSawHazmat = true;
        }
    }

    std::cout << "Existing snapshot sees the new hazmat unit: "
              << (oldSnapshotSawHazmat ? "yes" : "no") << std::endl;
    std::cout << "Fresh snapshot sees the new hazmat unit: "
              << (freshSnapshotSawHazmat ? "yes" : "no") << std::endl;

    if (oldSnapshotSawHazmat || !freshSnapshotSawHazmat) {
        throw std::runtime_error("The documented snapshot-addition policy was violated.");
    }

    printTraversal("\nUpdated depth-first incident view:",
                   powerPlantFire->createIterator());
    std::cout << "\nDispatching the updated power-plant incident:" << std::endl;
    powerPlantFire->sendOut();
}

void scenarioThree(EmergencyTask* cityEmergencyManager) {
    std::cout << "\n=== Scenario 3: ambulance lifecycle and transition safety ==="
              << std::endl;
    dispatchAmbulance responseUnit("Emergency evaluation ambulance");

    std::cout << "Initial lifecycle state: " << responseUnit.getStateName() << std::endl;
    responseUnit.complete();  // invalid: the unit has not been dispatched
    responseUnit.dispatch();
    responseUnit.dispatch();  // invalid: duplicate dispatch
    responseUnit.arrive();
    responseUnit.arrive();
    responseUnit.cancel();    // invalid: the unit is already committed on scene
    responseUnit.complete();

    std::cout << "Final lifecycle state: " << responseUnit.getStateName() << std::endl;

    std::cout << "\nVerifying cancellation and its terminal-state rejections:"
              << std::endl;
    dispatchAmbulance cancelledUnit("Cancelled standby ambulance");
    cancelledUnit.arrive();
    cancelledUnit.complete();
    cancelledUnit.cancel();
    cancelledUnit.dispatch();
    cancelledUnit.arrive();
    cancelledUnit.complete();
    cancelledUnit.cancel();

    std::cout << "\nVerifying completion and its terminal-state rejections:"
              << std::endl;
    dispatchAmbulance completedUnit("Completed response ambulance");
    completedUnit.dispatch();
    completedUnit.dispatch();
    completedUnit.complete();
    completedUnit.arrive();
    completedUnit.dispatch();
    completedUnit.complete();
    completedUnit.arrive();
    completedUnit.arrive();
    completedUnit.complete();
    completedUnit.dispatch();
    completedUnit.arrive();
    completedUnit.complete();
    completedUnit.cancel();

    std::cout << "\nVerifying safe composite removal after all snapshots expire:"
              << std::endl;
    dispatchAmbulance* temporaryUnit =
        new dispatchAmbulance("Temporary staging ambulance");
    cityEmergencyManager->add(temporaryUnit);
    cityEmergencyManager->remove(temporaryUnit);

    std::cout << "Verifying decorator forwarding and the leaf iterator contract:"
              << std::endl;
    std::unique_ptr<EmergencyTask> decoratedLeaf(
        new PriorityDispatchDecorator(
            new dispatchAmbulance("Decorated standby ambulance"),
            "P2 - interface verification"));
    decoratedLeaf->add(nullptr);
    decoratedLeaf->remove(nullptr);

    std::unique_ptr<TaskIterator> forwardIterator(decoratedLeaf->createIterator());
    forwardIterator->first();
    forwardIterator->next();
    (void)forwardIterator->currentItem();
    (void)forwardIterator->isDone();

    std::unique_ptr<TaskIterator> reverseIterator(
        decoratedLeaf->createReverseIterator());
    reverseIterator->first();
    reverseIterator->next();
    (void)reverseIterator->currentItem();
    (void)reverseIterator->isDone();
}

}  // namespace

int main() {
    try {
        EmergencyAuditLog auditLog;
        EmergencyTask* cityEmergencyManager = new IncidentGroup("Tshwane emergency command");

        EmergencyTask* centralDistrict = new IncidentGroup("Central district response");
        EmergencyTask* industrialSector = new IncidentGroup("Industrial sector response");
        IncidentGroup* powerPlantFire = new IncidentGroup("Power-plant fire incident");

        powerPlantFire->add(new dispatchAmbulance("Fire engine 1 to the turbine hall"));
        powerPlantFire->add(new AuditDispatchDecorator(
            new PriorityDispatchDecorator(
                new dispatchAmbulance("Rescue ambulance to the turbine hall"),
                "P1 - trapped workers"),
            &auditLog));

        industrialSector->add(powerPlantFire);
        centralDistrict->add(industrialSector);
        cityEmergencyManager->add(centralDistrict);

        scenarioOne(cityEmergencyManager, powerPlantFire, auditLog);
        scenarioTwo(powerPlantFire, auditLog);
        scenarioThree(cityEmergencyManager);

        delete cityEmergencyManager;
        std::cout << "\nTaskForge emergency response scenarios completed successfully." << std::endl;
        return 0;
    } catch (const std::exception& exception) {
        std::cerr << "TaskForge failed: " << exception.what() << std::endl;
        return 1;
    }
}
