#ifndef QTSIGNALSLOTMANAGER_H
#define QTSIGNALSLOTMANAGER_H

#include "qtsignalslotmanager_global.h"

class QObject;
class QtSignalSlotManagerPrivate;
class QTSIGNALSLOTMANAGERSHARED_EXPORT QtSignalSlotManager
{

private:
    QtSignalSlotManager();
    QtSignalSlotManager(const QtSignalSlotManager&);
    QtSignalSlotManager& operator=(const QtSignalSlotManager&);

public:
    static QtSignalSlotManager& getInstance();

public:
    void addSubject(int subjectId, QObject *sender, const char *signal);
    void removeSubject(int subjectId, QObject *sender, const char *signal);

public:
    void subscribe(int subjectId, QObject *receiver, const char *slot);
    void unsubscribe(int subjectId, QObject *receiver, const char *slot);

private:
    QtSignalSlotManagerPrivate * const d_ptr;
    Q_DECLARE_PRIVATE(QtSignalSlotManager)

};

#endif // QTSIGNALSLOTMANAGER_H
