#include "qtsignalslotmanager.h"

#include <QObject>
#include <QMultiHash>

struct StSignalSlotInfo
{
    StSignalSlotInfo(int id, QObject *obj, const char *method) {
        m_id = id;
        m_obj = obj;
        m_method = method;
    }

    int m_id;
    QObject *m_obj;
    const char *m_method;
};

class QtSignalSlotManagerPrivate
{
public:
    QtSignalSlotManagerPrivate(QtSignalSlotManager *p)
        :q_ptr(p)
    {

    }
    ~QtSignalSlotManagerPrivate()
    {
        qDeleteAll(m_hashSenders);
        qDeleteAll(m_hashReceivers);
    }

public:
    inline void addSender(int subjectId, QObject *sender, const char *signal)
    {
        add(m_hashSenders, subjectId, sender, signal);
    }
    inline void removeSender(int subjectId, StSignalSlotInfo *senderInfo)
    {
        remove(m_hashSenders, subjectId, senderInfo);
    }
    inline bool isSenderExists(int subjectId, QObject *sender, const char *signal)
    {
        return isExists(m_hashSenders, subjectId, sender, signal);
    }
    inline StSignalSlotInfo* getSenderInfo(int subjectId, QObject *sender, const char *signal)
    {
        return getInfo(m_hashSenders, subjectId, sender, signal);
    }
    inline QList<StSignalSlotInfo*> getSenderInfos(int subjectId)
    {
        return getInfos(m_hashSenders, subjectId);
    }

public:
    inline void addReceiver(int subjectId, QObject *receiver, const char *slot)
    {
        add(m_hashReceivers, subjectId, receiver, slot);
    }
    inline void removeReceiver(int subjectId, StSignalSlotInfo *receiverInfo)
    {
        remove(m_hashReceivers, subjectId, receiverInfo);
    }
    inline bool isReceiverExists(int subjectId, QObject *receiver, const char *slot)
    {
        return isExists(m_hashReceivers, subjectId, receiver, slot);
    }
    inline StSignalSlotInfo* getReceiverInfo(int subjectId, QObject *receiver, const char *slot)
    {
        return getInfo(m_hashReceivers, subjectId, receiver, slot);
    }
    inline QList<StSignalSlotInfo*> getReceiverInfos(int subjectId)
    {
        return getInfos(m_hashReceivers, subjectId);
    }

private:
    void add(QMultiHash<int, StSignalSlotInfo*> &hash, int subjectId, QObject *object, const char *method);
    void remove(QMultiHash<int, StSignalSlotInfo*> &hash, int subjectId, StSignalSlotInfo *info);
    bool isExists(QMultiHash<int, StSignalSlotInfo*> &hash, int subjectId, QObject *object, const char *method);
    StSignalSlotInfo* getInfo(QMultiHash<int, StSignalSlotInfo*> &hash, int subjectId, QObject *object, const char *method);
    QList<StSignalSlotInfo*> getInfos(QMultiHash<int, StSignalSlotInfo*> &hash, int subjectId);

private:
    QMultiHash<int, StSignalSlotInfo*> m_hashSenders;
    QMultiHash<int, StSignalSlotInfo*> m_hashReceivers;

private:
    Qt::ConnectionType m_autoUniqueConnection = Qt::ConnectionType(Qt::UniqueConnection | Qt::AutoConnection);

private:
    QtSignalSlotManager * const q_ptr;
    Q_DECLARE_PUBLIC(QtSignalSlotManager)
};

void QtSignalSlotManagerPrivate::add(QMultiHash<int, StSignalSlotInfo*> &hash, int subjectId, QObject *object, const char *method)
{
    auto info = new StSignalSlotInfo(subjectId, object, method);
    hash.insertMulti(subjectId, info);
}

void QtSignalSlotManagerPrivate::remove(QMultiHash<int, StSignalSlotInfo*> &hash, int subjectId, StSignalSlotInfo *info)
{
    hash.remove(subjectId, info);
    delete info;
}

bool QtSignalSlotManagerPrivate::isExists(QMultiHash<int, StSignalSlotInfo*> &hash, int subjectId, QObject *object, const char *method)
{
    return nullptr != getInfo(hash, subjectId, object, method);
}

StSignalSlotInfo* QtSignalSlotManagerPrivate::getInfo(QMultiHash<int, StSignalSlotInfo*> &hash, int subjectId, QObject *object, const char *method)
{
    StSignalSlotInfo *result = nullptr;
    auto senders = hash.values(subjectId);
    for (StSignalSlotInfo *info : senders)
    {
        if(info->m_id == subjectId && info->m_obj == object && strcmp(info->m_method, method) == 0)
        {
            result = info;
            break;
        }
    }
    return result;
}

QList<StSignalSlotInfo*> QtSignalSlotManagerPrivate::getInfos(QMultiHash<int, StSignalSlotInfo*> &hash, int subjectId)
{
    return hash.values(subjectId);
}

QtSignalSlotManager::QtSignalSlotManager()
    :d_ptr(new QtSignalSlotManagerPrivate(this))
{

}

QtSignalSlotManager& QtSignalSlotManager::getInstance()
{
    static QtSignalSlotManager instance;
    return instance;
}

void QtSignalSlotManager::addSubject(int subjectId, QObject *sender, const char *signal)
{
    Q_D(QtSignalSlotManager);
    if(!d->isSenderExists(subjectId, sender, signal))
    {
        d->addSender(subjectId, sender, signal);
    }

    auto cachedRecvInfos = d->getReceiverInfos(subjectId);
    for (auto recvInfo : cachedRecvInfos)
    {
        QObject::connect(sender, signal, recvInfo->m_obj, recvInfo->m_method, d->m_autoUniqueConnection);
    }
}

void QtSignalSlotManager::removeSubject(int subjectId, QObject *sender, const char *signal)
{
    Q_D(QtSignalSlotManager);
    auto senderInfo = d->getSenderInfo(subjectId, sender, signal);
    if(nullptr == senderInfo)
        return;

    //slots connected outer of this QtSignalSlotManager may not work
//    QObject::disconnect(sender, signal, nullptr, nullptr);
    auto recvInfos = d->getReceiverInfos(subjectId);
    for (auto recvInfo : recvInfos)
    {
        QObject::disconnect(sender, signal, recvInfo->m_obj, recvInfo->m_method);
    }

    d->removeSender(subjectId, senderInfo);
}

void QtSignalSlotManager::subscribe(int subjectId, QObject *receiver, const char *slot)
{
    Q_D(QtSignalSlotManager);
    if(d->isReceiverExists(subjectId, receiver, slot))
        return;

    auto sendInfos = d->getSenderInfos(subjectId);
    for (auto sendInfo : sendInfos)
    {
        QObject::connect(sendInfo->m_obj, sendInfo->m_method, receiver, slot, d->m_autoUniqueConnection);
    }

    d->addReceiver(subjectId, receiver, slot);
}

void QtSignalSlotManager::unsubscribe(int subjectId, QObject *receiver, const char *slot)
{
    Q_D(QtSignalSlotManager);
    auto recvInfo = d->getReceiverInfo(subjectId, receiver, slot);
    if(nullptr == recvInfo)
        return;

    auto sendInfos = d->getSenderInfos(subjectId);
    for (auto sendInfo : sendInfos)
    {
        QObject::disconnect(sendInfo->m_obj, sendInfo->m_method, receiver, slot);
    }

    d->removeReceiver(subjectId, recvInfo);
}
