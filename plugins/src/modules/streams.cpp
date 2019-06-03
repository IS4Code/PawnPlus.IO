#include "streams.h"

aux::shared_id_set_pool<io_stream> stream_pool;

size_t io_stream::read_unpacked(cell *buffer, size_t size)
{
	for(size_t i = 0; i < size; i++)
	{
		buffer[i] = 0;
		size_t num = read(reinterpret_cast<char*>(buffer + i), sizeof(char));
		if(num == 0)
		{
			return i;
		}
	}
	return size;
}

size_t io_stream::read_packed(char *buffer, size_t size)
{
	for(size_t i = 0; i < size; i++)
	{
		size_t num = read(reinterpret_cast<char*>(buffer + (i ^ (sizeof(cell) - 1))), sizeof(char));
		if(num == 0)
		{
			return i;
		}
	}
	return size;
}

size_t io_stream::write_unpacked(const cell *buffer, size_t size)
{
	for(size_t i = 0; i < size; i++)
	{
		size_t num = write(reinterpret_cast<const char*>(buffer + i), sizeof(char));
		if(num == 0)
		{
			return i;
		}
	}
	return size;
}

size_t io_stream::write_packed(const char *buffer, size_t size)
{
	for(size_t i = 0; i < size; i++)
	{
		size_t num = write(reinterpret_cast<const char*>(buffer + (i ^ (sizeof(cell) - 1))), sizeof(char));
		if(num == 0)
		{
			return i;
		}
	}
	return size;
}
