#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "sdk/amx/amx.h"
#include <utility>

#define PP_IO_VERSION_STRING "v0.1"
#define PP_IO_VERSION_NUMBER 0x010

typedef void(*logprintf_t)(const char* format, ...);
extern logprintf_t logprintf;

extern bool pp_loaded;

#endif
