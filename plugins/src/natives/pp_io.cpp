#include "natives.h"
#include "main.h"

namespace Natives
{
	// native pp_io_version();
	AMX_DEFINE_NATIVE(pp_io_version, 0)
	{
		return PP_IO_VERSION_NUMBER;
	}
}

static AMX_NATIVE_INFO native_list[] =
{
	AMX_DECLARE_NATIVE(pp_io_version),
};

int RegisterIOConfigNatives(AMX *amx)
{
	return amx_Register(amx, native_list, sizeof(native_list) / sizeof(*native_list));
}
