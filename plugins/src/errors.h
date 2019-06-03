#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

#include "sdk/amx/amx.h"
#include <string>
#include <stdio.h>
#include <stdarg.h>

[[noreturn]] void amx_FormalError(int code, ...);
[[noreturn]] void amx_LogicError(int code, ...);
cell *amx_GetAddrSafe(AMX *amx, cell amx_addr);

namespace errors
{
	struct native_error
	{
		std::string message;
		int level;

		native_error(int code, va_list args, int level);
		native_error(int code, int level, ...);

		native_error(std::string &&message, int level) : level(level), message(std::move(message))
		{

		}
	};

	struct end_of_arguments_error
	{
		const cell *argbase;
		size_t required;

		end_of_arguments_error(const cell *argbase, size_t required) : argbase(argbase), required(required)
		{

		}
	};

	struct amx_error
	{
		int code;

		amx_error(int code) : code(code)
		{

		}
	};

	constexpr int not_enough_args = 0;
	constexpr int pointer_invalid = 1;
	constexpr int cannot_acquire = 2;
	constexpr int cannot_release = 3;
	constexpr int operation_not_supported = 4;
	constexpr int out_of_range = 5;
	constexpr int element_not_present = 6;
	constexpr int func_not_found = 7;
	constexpr int var_not_found = 8;
	constexpr int arg_empty = 9;
	constexpr int inner_error = 10;
	constexpr int no_debug_error = 11;
	constexpr int unhandled_exception = 12;
	constexpr int invalid_format = 13;
}

#endif
