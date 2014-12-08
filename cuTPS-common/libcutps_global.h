#ifndef LIBCUTPS_GLOBAL_H
#define LIBCUTPS_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(LIBCUTPS_LIBRARY)
#define LIBCUTPS_EXPORT Q_DECL_EXPORT
#else
#define LIBCUTPS_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBCUTPS_GLOBAL_H
