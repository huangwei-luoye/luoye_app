#ifndef UDP_GLOBAL_H
#define UDP_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef UDP_USE_CODE
#  define UDP_EXPORT
#else
#if defined(UDP_LIBRARY)
#  define UDP_EXPORT Q_DECL_EXPORT
#else
#  define UDP_EXPORT Q_DECL_IMPORT
#endif
#endif

#endif // UDP_GLOBAL_H
