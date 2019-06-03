#ifndef NATIVES_H_INCLUDED
#define NATIVES_H_INCLUDED

#include "main.h"
#include "errors.h"
#include "api/ppcommon.h"
#include "sdk/amx/amx.h"

#define optparam(idx, optvalue) (params[0] / sizeof(cell) < (idx) ? (optvalue) : params[idx])
#define optparamref(idx, optvalue) (params[0] / sizeof(cell) < (idx) ? &(*reinterpret_cast<cell*>(alloca(sizeof(cell))) = (optvalue)) : amx_GetAddrSafe(amx, params[idx]))
#define amx_OptStrParam(amx,idx,result,default)                             \
    do {                                                                    \
      if (params[0] / sizeof(cell) < idx) { result = default; break; }      \
      cell *amx_cstr_; int amx_length_;                                     \
      amx_cstr_ = amx_GetAddrSafe((amx), (params[idx]));                    \
      amx_StrLen(amx_cstr_, &amx_length_);                                  \
      if (amx_length_ > 0 &&                                                \
          ((result) = (char*)alloca((amx_length_ + 1) * sizeof(*(result)))) != NULL) \
        amx_GetString((char*)(result), amx_cstr_, sizeof(*(result))>1, amx_length_ + 1); \
      else (result) = NULL;                                                 \
    } while (0)

#ifdef amx_StrParam
#undef amx_StrParam
#define amx_StrParam(amx,param,result)                                      \
    do {                                                                    \
      cell *amx_cstr_; int amx_length_;                                     \
      amx_cstr_ = amx_GetAddrSafe((amx), (param));                          \
      amx_StrLen(amx_cstr_, &amx_length_);                                  \
      if (amx_length_ > 0 &&                                                \
          ((result) = (char*)alloca((amx_length_ + 1) * sizeof(*(result)))) != NULL) \
        amx_GetString((char*)(result), amx_cstr_, sizeof(*(result))>1, amx_length_ + 1); \
      else (result) = NULL;                                                 \
    } while (0)
#endif

namespace impl
{
	template <AMX_NATIVE Native>
	struct native_info;

	template <AMX_NATIVE Native>
	static cell AMX_NATIVE_CALL adapt_native(AMX *amx, cell *params) noexcept
	{
		try{
			if(params[0] < native_info<Native>::arg_count() * static_cast<cell>(sizeof(cell)))
			{
				amx_FormalError(errors::not_enough_args, native_info<Native>::arg_count(), params[0] / static_cast<cell>(sizeof(cell)));
			}
			return Native(amx, params);
		}catch(const errors::end_of_arguments_error &err)
		{
			return pp::main.raise_error(amx, params, native_info<Native>::name(), err.argbase, err.required);
		}catch(const errors::native_error &err)
		{
			return pp::main.raise_error(amx, params, native_info<Native>::name(), err.level, err.message.data());
		}catch(const errors::amx_error &err)
		{
			amx_RaiseError(amx, err.code);
			return 0;
		}
#ifndef _DEBUG
		catch(const std::exception &err)
		{
			return pp::main.raise_error(amx, params, native_info<Native>::name(), 2, errors::native_error(errors::unhandled_exception, 2, err.what()).message);
		}
#endif
	}
}

#define AMX_DEFINE_NATIVE(Name, ArgCount) \
	cell AMX_NATIVE_CALL Name(AMX *amx, cell *params); \
} \
namespace impl \
{ \
	template <> \
	struct native_info<&Natives::Name> \
	{ \
		static constexpr char *name() { return #Name; } \
		static constexpr cell arg_count() { return ArgCount; } \
	}; \
} \
namespace Natives \
{ \
	cell AMX_NATIVE_CALL Name(AMX *amx, cell *params)

#define AMX_DECLARE_NATIVE(Name) {#Name, impl::adapt_native<&Natives::Name>}

int RegisterIOConfigNatives(AMX *amx);
int RegisterIONatives(AMX *amx);

inline int RegisterNatives(AMX *amx)
{
	RegisterIOConfigNatives(amx);
	RegisterIONatives(amx);
	return AMX_ERR_NONE;
}

#endif
