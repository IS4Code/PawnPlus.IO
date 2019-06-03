#include "streams.h"
#include <cstdio>

class file_stream : public io_stream
{
	FILE *file;

	const char *openmode(io_open_mode mode)
	{
		switch(mode)
		{
			case io_open_mode::open:
				return "rb";
			case io_open_mode::create:
				return "w+b";
			case io_open_mode::open_or_create:
				return "r+b";
			case io_open_mode::append:
				return "ab";
		}
		return nullptr;
	}

public:
	file_stream(const char *filename, io_open_mode mode) : file(std::fopen(filename, openmode(mode)))
	{
		if(!file)
		{
			throw errno;
		}
	}

	virtual bool can_read() const override
	{
		return true;
	}

	virtual bool can_write() const override
	{
		return true;
	}

	virtual bool can_seek() const override
	{
		return true;
	}

	virtual size_t read(char *buffer, size_t size) override
	{
		return std::fread(buffer, sizeof(char), size, file);
	}

	virtual size_t write(const char *buffer, size_t size) override
	{
		return std::fwrite(buffer, sizeof(char), size, file);
	}

	virtual size_t seek(ptrdiff_t offset, seek_whence whence) override
	{
		int origin;
		switch(whence)
		{
			case seek_whence::start:
				origin = SEEK_SET;
				break;
			case seek_whence::current:
				origin = SEEK_CUR;
				break;
			case seek_whence::end:
				origin = SEEK_END;
				break;
		}
		std::fseek(file, offset, origin);
		return std::ftell(file);
	}

	~file_stream()
	{
		if(file)
		{
			std::fclose(file);
			file = nullptr;
		}
	}
};

const std::shared_ptr<io_stream> &stream_open_file(const char *filename, io_open_mode mode)
{
	return stream_pool.emplace_derived<file_stream>(filename, mode);
}
