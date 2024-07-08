#ifndef GLOBAL_H
#define GLOBAL_H
#include <QtCore/qglobal.h>

#ifdef LIBDLL_LIB
#define EXPORT Q_DECL_EXPORT
#else
#define EXPORT Q_DECL_IMPORT
#endif

#endif // GLOBAL_H
