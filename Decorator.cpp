#include "Decorator.h"

#include <iostream>
#include <stdexcept>

EmergencyTaskDecorator::EmergencyTaskDecorator(EmergencyTask* task)
    : EmergencyTask(task == nullptr ? "" : task->getDescription()), wrappedTask(task) {
    if (wrappedTask == nullptr) {
        throw std::invalid_argument("A decorator must wrap an emergency task.");
    }
}

EmergencyTaskDecorator::~EmergencyTaskDecorator() {
    delete wrappedTask;
}

void EmergencyTaskDecorator::sendOut() {
    wrappedTask->sendOut();
}

void EmergencyTaskDecorator::add(EmergencyTask* task) {
    wrappedTask->add(task);
}

void EmergencyTaskDecorator::remove(EmergencyTask* task) {
    wrappedTask->remove(task);
}

TaskIterator* EmergencyTaskDecorator::createIterator() {
    return wrappedTask->createIterator();
}

TaskIterator* EmergencyTaskDecorator::createReverseIterator() {
    return wrappedTask->createReverseIterator();
}

PriorityDispatchDecorator::PriorityDispatchDecorator(EmergencyTask* task,
                                                     const std::string& label)
    : EmergencyTaskDecorator(task), priorityLabel(label) {
    if (priorityLabel.empty()) {
        throw std::invalid_argument("A priority dispatch needs a label.");
    }
}

void PriorityDispatchDecorator::sendOut() {
    std::cout << "\t PRIORITY " << priorityLabel << ": dispatch first for "
              << wrappedTask->getDescription() << std::endl;
    wrappedTask->sendOut();
}

std::string PriorityDispatchDecorator::getDescription() const {
    return wrappedTask->getDescription() + " [priority: " + priorityLabel + "]";
}

void EmergencyAuditLog::record(const std::string& entry) {
    entries.push_back(entry);
}

std::size_t EmergencyAuditLog::size() const {
    return entries.size();
}

void EmergencyAuditLog::writeTo(std::ostream& output) const {
    for (std::size_t index = 0; index < entries.size(); ++index) {
        output << "  " << index + 1 << ". " << entries[index] << std::endl;
    }
}

AuditDispatchDecorator::AuditDispatchDecorator(EmergencyTask* task,
                                               EmergencyAuditLog* log)
    : EmergencyTaskDecorator(task), auditLog(log) {
    if (auditLog == nullptr) {
        throw std::invalid_argument("An audit decorator needs an audit log.");
    }
}

void AuditDispatchDecorator::sendOut() {
    auditLog->record("Dispatch started: " + wrappedTask->getDescription());
    wrappedTask->sendOut();
    auditLog->record("Dispatch completed: " + wrappedTask->getDescription());
}

std::string AuditDispatchDecorator::getDescription() const {
    return wrappedTask->getDescription() + " [audited]";
}
