#include "errors.h"
#include "api/ppcommon.h"

errors::native_error::native_error(int code, va_list args, int level) : level(level)
{
	const char *format = pp::main.get_error(code);
	message = std::string(vsnprintf(NULL, 0, format, args), '\0');
	vsprintf(&message[0], format, args);
}

errors::native_error::native_error(int code, int level, ...) : level(level)
{
	va_list args;
	va_start(args, level);
	const char *format = pp::main.get_error(code);
	message = std::string(vsnprintf(NULL, 0, format, args), '\0');
	vsprintf(&message[0], format, args);
	va_end(args);
}

[[noreturn]] void amx_FormalError(int code, ...)
{
	va_list args;
	va_start(args, code);
	errors::native_error err(code, args, 3);
	va_end(args);
	throw err;
}

[[noreturn]] void amx_LogicError(int code, ...)
{
	va_list args;
	va_start(args, code);
	errors::native_error err(code, args, 2);
	va_end(args);
	throw err;
}

cell *amx_GetAddrSafe(AMX *amx, cell amx_addr)
{
	cell *addr;
	int err = amx_GetAddr(amx, amx_addr, &addr);
	if(err != AMX_ERR_NONE)
	{
		throw errors::amx_error(err);
	}
	if(amx_addr % sizeof(cell) != 0 && amx_addr >= 0 && amx_addr < amx->stp && (amx_addr < amx->hea || amx_addr >= amx->stk))
	{
		// if amx_GetAddr verifies the address but it is not inside the valid range, a hook is in place
		throw errors::amx_error(AMX_ERR_MEMACCESS);
	}
	return addr;
}
