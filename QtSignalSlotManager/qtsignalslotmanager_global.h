#ifndef QTSIGNALSLOTMANAGER_GLOBAL_H
#define QTSIGNALSLOTMANAGER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTSIGNALSLOTMANAGER_LIBRARY)
#  define QTSIGNALSLOTMANAGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTSIGNALSLOTMANAGERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QTSIGNALSLOTMANAGER_GLOBAL_H
