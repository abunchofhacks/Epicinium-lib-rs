#pragma once

/* This file can be included into every .hpp header file. */

#include <cstdlib>
#include <cstdint>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
#include <iosfwd>
#include <cassert>
#include <array>

/* If we are running dev, we want as many crashes as possible. */
// Usage: "DEBUG_ASSERT(xyz);"
#ifdef DEVELOPMENT
#define DEBUG_ASSERT(x) assert(x)
#else
#define DEBUG_ASSERT(x) do { (void)sizeof(x); } while (0) // "Stupid C++ Tricks"
#endif
// Usage: "RETHROW_IF_DEV();"
#ifdef DEVELOPMENT
#define RETHROW_IF_DEV() throw
#else
#define RETHROW_IF_DEV() ((void)0)
#endif

#include "libs/jsoncpp/json-forwards.h"

#ifdef PLATFORMDEBIAN32
#define PLATFORMDEBIAN
#define PLATFORMUNIX
#endif
#ifdef PLATFORMDEBIAN64
#define PLATFORMDEBIAN
#define PLATFORMUNIX
#endif
#ifdef PLATFORMOSX32
#define PLATFORMOSX
#define PLATFORMUNIX
#endif
#ifdef PLATFORMOSX64
#define PLATFORMOSX
#define PLATFORMUNIX
#endif
#ifdef PLATFORMWINDOWS32
#define PLATFORMWINDOWS
#endif
#ifdef PLATFORMWINDOWS64
#define PLATFORMWINDOWS
#endif

struct stringref;

#if defined(__GNUC__) || defined(__clang__)
#define ATTRIBUTE_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#define ATTRIBUTE_WARN_UNUSED_RESULT
#endif

/* We can turn these features on or off; they are not available everywhere. */

#ifndef COREDUMP_ENABLED
#ifdef PLATFORMUNIX
#define COREDUMP_ENABLED true
#else
#define COREDUMP_ENABLED false
#endif
#endif

#ifndef STATIC_WRITER_ENABLED
#define STATIC_WRITER_ENABLED true
#endif

#ifndef INCLUDE_IMGUI_ENABLED
#define INCLUDE_IMGUI_ENABLED true
#endif

#ifndef LOG_REPLACE_WITH_CALLBACK_ENABLED
#define LOG_REPLACE_WITH_CALLBACK_ENABLED false
#endif

#ifndef DICTATOR_ENABLED
#ifdef DEVELOPMENT
#define DICTATOR_ENABLED true
#else
#define DICTATOR_ENABLED false
#endif
#endif

#ifndef LIBLOADER_ENABLED
#define LIBLOADER_ENABLED false
#endif

#ifndef VALGRIND_INTEGRATION_ENABLED
#define VALGRIND_INTEGRATION_ENABLED false
#endif

#ifndef DISCORD_GUEST_ENABLED
#define DISCORD_GUEST_ENABLED false
#endif
