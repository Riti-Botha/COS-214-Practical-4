#ifndef DECORATOR_H
#define DECORATOR_H

#include "Composite.h"

#include <cstddef>
#include <ostream>
#include <string>
#include <vector>

/**
 * Decorator base. It owns the wrapped EmergencyTask, so an IncidentGroup can
 * own and destroy a decorated task exactly as it owns an ordinary leaf.
 */
class EmergencyTaskDecorator : public EmergencyTask {
protected:
    EmergencyTask* wrappedTask;

public:
    explicit EmergencyTaskDecorator(EmergencyTask* task);
    ~EmergencyTaskDecorator() override;

    void sendOut() override;
    void add(EmergencyTask* task) override;
    void remove(EmergencyTask* task) override;
    TaskIterator* createIterator() override;
    TaskIterator* createReverseIterator() override;
};

/** Adds a dispatch-priority instruction without changing the vehicle task. */
class PriorityDispatchDecorator : public EmergencyTaskDecorator {
private:
    std::string priorityLabel;

public:
    PriorityDispatchDecorator(EmergencyTask* task, const std::string& label);
    ~PriorityDispatchDecorator() override = default;

    void sendOut() override;
    std::string getDescription() const override;
};

/** A shared release-style audit sink for emergency dispatch events. */
class EmergencyAuditLog {
private:
    std::vector<std::string> entries;

public:
    void record(const std::string& entry);
    std::size_t size() const;
    void writeTo(std::ostream& output) const;
};

/** Records the outcome of dispatching a task while preserving its interface. */
class AuditDispatchDecorator : public EmergencyTaskDecorator {
private:
    EmergencyAuditLog* auditLog;  // non-owning; caller keeps it alive

public:
    AuditDispatchDecorator(EmergencyTask* task, EmergencyAuditLog* log);
    ~AuditDispatchDecorator() override = default;

    void sendOut() override;
    std::string getDescription() const override;
};

#endif
