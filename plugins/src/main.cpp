#include "main.h"
#include "natives.h"
#include "api/ppcommon.h"

#include "sdk/amx/amx.h"
#include "sdk/plugincommon.h"

logprintf_t logprintf;
extern void *pAMXFunctions;

bool pp_queried = false;
bool pp_loaded = false;

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() noexcept
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES | SUPPORTS_PROCESS_TICK;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) noexcept
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf(" PawnPlus.IO " PP_IO_VERSION_STRING " loaded");
	logprintf(" Created by IllidanS4");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() noexcept
{
	logprintf(" PawnPlus.IO " PP_IO_VERSION_STRING " unloaded");
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) noexcept
{
	if(!pp_queried)
	{
		pp_loaded = pp::load();
		pp_queried = true;
		if(!pp_loaded)
		{
			logprintf("[PawnPlus.IO] PawnPlus must be loaded to use this plugin.");
		}
	}
	if(pp_loaded)
	{
		RegisterNatives(amx);
	}
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) noexcept
{
	return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() noexcept
{

}
