#ifndef STREAMS_H_INCLUDED
#define STREAMS_H_INCLUDED

#include "utils/shared_id_set_pool.h"

#include <memory>

enum class io_open_mode
{
	open,
	create,
	create_new,
	open_or_create,
	append,
};

enum class seek_whence
{
	start,
	current,
	end,
};

class io_stream
{
public:
	io_stream() = default;

	virtual bool can_read() const = 0;
	virtual bool can_write() const = 0;
	virtual bool can_seek() const = 0;
	virtual size_t read(char *buffer, size_t size) = 0;
	virtual size_t read_unpacked(cell *buffer, size_t size);
	virtual size_t read_packed(char *buffer, size_t size);
	virtual size_t write(const char *buffer, size_t size) = 0;
	virtual size_t write_unpacked(const cell *buffer, size_t size);
	virtual size_t write_packed(const char *buffer, size_t size);
	virtual size_t seek(ptrdiff_t offset, seek_whence whence) = 0;

	virtual ~io_stream() = default;
};

extern aux::shared_id_set_pool<io_stream> stream_pool;

const std::shared_ptr<io_stream> &stream_open_file(const char *filename, io_open_mode mode);
const std::shared_ptr<io_stream> &stream_open_memory();

#endif
