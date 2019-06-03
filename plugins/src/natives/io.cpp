#include "natives.h"
#include "main.h"
#include "modules/streams.h"

namespace Natives
{
	// native Stream:io_open(const name[], io_open_mode:mode);
	AMX_DEFINE_NATIVE(io_open, 2)
	{
		const char *name;
		amx_StrParam(amx, params[1], name);
		io_open_mode mode;
		switch(params[2])
		{
			case 0:
				mode = io_open_mode::open;
				break;
			case 1:
				mode = io_open_mode::create;
				break;
			case 2:
				mode = io_open_mode::open_or_create;
				break;
			case 3:
				mode = io_open_mode::append;
				break;
			default:
				amx_LogicError(errors::out_of_range, "mode");
				break;
		}
		auto &ptr = stream_open_file(name, mode);
		return stream_pool.get_id(ptr);
	}
	
	// native Stream:io_buffer();
	AMX_DEFINE_NATIVE(io_buffer, 0)
	{
		auto &ptr = stream_open_memory();
		return stream_pool.get_id(ptr);
	}

	// native io_close(Stream:stream);
	AMX_DEFINE_NATIVE(io_close, 1)
	{
		io_stream *ptr;
		if(!stream_pool.get_by_id(params[1], ptr)) amx_LogicError(errors::pointer_invalid, "stream", params[1]);

		return stream_pool.remove(ptr);
	}

	// native io_write(Stream:stream, const data[], io_data_mode:mode=io_data_raw, size=sizeof(data));
	AMX_DEFINE_NATIVE(io_write_arr, 4)
	{
		io_stream *ptr;
		if(!stream_pool.get_by_id(params[1], ptr)) amx_LogicError(errors::pointer_invalid, "stream", params[1]);

		cell *addr = amx_GetAddrSafe(amx, params[2]);
		size_t size;
		if(params[4] >= 0)
		{
			if(params[3] == 1)
			{
				size = params[4];
			}else{
				size = params[4] * sizeof(cell);
			}
		}else{
			size = -params[4];
		}

		switch(params[3])
		{
			case 0:
				return ptr->write(reinterpret_cast<char*>(addr), size);
			case 1:
				return ptr->write_unpacked(addr, size);
			case 2:
				return ptr->write_packed(reinterpret_cast<char*>(addr), size);
		}

		return 0;
	}

	// native io_read(Stream:stream, data[], io_data_mode:mode=io_data_raw, size=sizeof(data));
	AMX_DEFINE_NATIVE(io_read_arr, 4)
	{
		io_stream *ptr;
		if(!stream_pool.get_by_id(params[1], ptr)) amx_LogicError(errors::pointer_invalid, "stream", params[1]);

		cell *addr = amx_GetAddrSafe(amx, params[2]);
		size_t size;
		if(params[4] >= 0)
		{
			if(params[3] == 1)
			{
				size = params[4];
			}else{
				size = params[4] * sizeof(cell);
			}
		}else{
			size = -params[4];
		}

		switch(params[3])
		{
			case 0:
				return ptr->read(reinterpret_cast<char*>(addr), size);
			case 1:
				return ptr->read_unpacked(addr, size);
			case 2:
				return ptr->read_packed(reinterpret_cast<char*>(addr), size);
		}

		return 0;
	}
	
	// native io_seek(Stream:stream, position, io_seek_whence:whence=io_seek_start);
	AMX_DEFINE_NATIVE(io_seek, 2)
	{
		io_stream *ptr;
		if(!stream_pool.get_by_id(params[1], ptr)) amx_LogicError(errors::pointer_invalid, "stream", params[1]);

		seek_whence whence;
		switch(optparam(3, 0))
		{
			case 0:
				whence = seek_whence::start;
				break;
			case 1:
				whence = seek_whence::current;
				break;
			case 2:
				whence = seek_whence::end;
				break;
			default:
				amx_LogicError(errors::out_of_range, "whence");
				break;
		}

		return ptr->seek(params[2], whence);
	}
}

static AMX_NATIVE_INFO native_list[] =
{
	AMX_DECLARE_NATIVE(io_open),
	AMX_DECLARE_NATIVE(io_buffer),
	AMX_DECLARE_NATIVE(io_close),
	AMX_DECLARE_NATIVE(io_write_arr),
	AMX_DECLARE_NATIVE(io_read_arr),
	AMX_DECLARE_NATIVE(io_seek),
};

int RegisterIONatives(AMX *amx)
{
	return amx_Register(amx, native_list, sizeof(native_list) / sizeof(*native_list));
}
