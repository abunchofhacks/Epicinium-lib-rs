/**
 * Part of Epicinium
 * developed by A Bunch of Hacks.
 *
 * Copyright (c) 2017-2020 A Bunch of Hacks
 *
 * Epicinium is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Epicinium is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * [authors:]
 * Sander in 't Veld (sander@abunchofhacks.coop)
 * Daan Mulder (daan@abunchofhacks.coop)
 */
#pragma once
#include "header.hpp"

/* This file can be included into every .cpp source file. */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <csignal>
#include <algorithm>

#if INCLUDE_IMGUI_ENABLED
#include "libs/imgui/imgui.h"
#include "libs/imgui/imgui_stdlib.h"
#endif

#include "libs/jsoncpp/json.h"

#define PLOG_FORCE_UTF8_MESSAGE 1
#include "libs/plog/Log.h"

/* If we are running dev, we want to be able to call profiling macros. */
#if VALGRIND_INTEGRATION_ENABLED
#include <valgrind/memcheck.h>
#include <valgrind/callgrind.h>
#include <valgrind/helgrind.h>
#include <valgrind/drd.h>
#endif

/* If we are running dev, we want as many crashes as possible. */
// Deprecated by DEBUG_ASSERT() and RETHROW_IF_DEV() in header.hpp.
#ifdef DEVELOPMENT
#define CRASHME
#endif

/* If we are running dev, we want to be able to use PERFLOG. */
#ifdef DEVELOPMENT
#define PERFLOG
#endif

/* If we are running PERFLOG, we want to be able to use it. */
#ifdef PERFLOG
#define PERFLOG_INSTANCE 123
#define PERFLOGI LOGI_(PERFLOG_INSTANCE)
#define PERFLOGV LOGV_(PERFLOG_INSTANCE)
#else
#define PERFLOGI LOGI_IF(false)
#define PERFLOGV LOGV_IF(false)
#endif


/* Portable replacement for PI */
constexpr long double pi()
{
	return 3.141592653589793238462643383279502884L; /* GNU PI */
}

/* Portable replacement for SQRT(2) */
constexpr long double sqrt2()
{
	return 1.414213562373095048801688724209698079L; /* GNU SQRT2 */
}

/* Mathematical signum */
constexpr int signum(int x)
{
	return (x > 0) ? 1 : (x < 0) ? -1 : 0;
}

/* Mathematical modulo */
constexpr int mod(int x, int n)
{
	return (x % n + n) % n;
}

constexpr long mod(long x, long n)
{
	return (x % n + n) % n;
}

/* Calculates least power of two that is greater or equal, up to 2^31. */
constexpr int nearestPowerOfTwo(int n)
{
	return (n <= 0) ? 1 : ((
		(n - 1)
			| (n >> 1)
			| (n >> 2)
			| (n >> 4)
			| (n >> 8)
			| (n >> 16)
		) + 1);
}

/* String conversion */
inline std::string tolower(std::string result)
{
	std::transform(result.begin(), result.end(), result.begin(),
		(int (*)(int))(std::tolower));
	return result;
}

inline std::string toupper(std::string result)
{
	std::transform(result.begin(), result.end(), result.begin(),
		(int (*)(int))(std::toupper));
	return result;
}

inline std::string toupper1(std::string result)
{
	if (!result.empty()) result[0] = std::toupper(result[0]);
	return result;
}

/* String sanitation */
inline std::string sanitize(const std::string& input)
{
	std::string output = input;
	for (char& x : output)
	{
		if (x == '_') continue;
		else if (x >= 'a' && x <= 'z') continue;
		else if (x >= 'A' && x <= 'Z') continue;
		else if (x >= '0' && x <= '9') continue;
		else
		{
			x = '_';
		}
	}
	return output;
}

/* Get the size of a locally declared array. */
template<size_t SIZE, class T>
constexpr size_t array_size(T (&/*arr*/)[SIZE])
{
	return SIZE;
}

/* Non-localized JSON-compatible boolean strings. */
constexpr const char* jsonify(bool value)
{
	return value ? "true" : "false";
}
