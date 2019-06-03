#include "streams.h"
#include <vector>
#include <cstring>

class memory_stream : public io_stream
{
	std::vector<char> data;
	size_t position = 0;

public:
	memory_stream()
	{

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
		if(position + size > data.size())
		{
			size = data.size() - position;
		}
		std::memcpy(buffer, &data[position], size);
		position += size;
		return size;
	}

	virtual size_t write(const char *buffer, size_t size) override
	{
		size_t newsize = position + size;
		if(newsize > data.size())
		{
			data.resize(newsize);
		}
		std::memcpy(&data[position], buffer, size);
		position += size;
		return size;
	}

	virtual size_t seek(ptrdiff_t offset, seek_whence whence) override
	{
		switch(whence)
		{
			case seek_whence::start:
				if(offset < 0)
				{
					return position = 0;
				}else if(static_cast<size_t>(offset) > data.size())
				{
					return position = data.size();
				}else{
					return position = offset;
				}
			case seek_whence::current:
				if(offset < 0 && static_cast<size_t>(-offset) > position)
				{
					return position = 0;
				}else if(offset > 0 && position + offset > data.size())
				{
					return position = data.size();
				}else{
					return position += offset;
				}
			case seek_whence::end:
				if(offset >= 0)
				{
					return position = data.size();
				}else if(static_cast<size_t>(-offset) > data.size())
				{
					return position = 0;
				}else{
					return position = data.size() + offset;
				}
		}
		return -1;
	}
};

const std::shared_ptr<io_stream> &stream_open_memory()
{
	return stream_pool.emplace_derived<memory_stream>();
}
