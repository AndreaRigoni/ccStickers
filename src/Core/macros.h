#ifndef MACROS_H
#define MACROS_H

#include <assert.h>
#include <stddef.h>

////////////////////////////////////////////////////////////////////////////////
//  MACROS  ////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#define MDSIPTEST_PP_STRINGIZE_I(text) #text
#define MDSIPTEST_STATIC_CONSTANT(type, assignment) static const type assignment

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))
#define COMPILE_WARNING(x) DO_PRAGMA(message ("WARNING - " #x))
#define COMPILE_ERROR(x) DO_PRAGMA(message ("ERROR - " #x))


#endif // MACROS_H

