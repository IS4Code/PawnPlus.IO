/** PawnPlus.IO v0.1 by IllidanS4 **/
//github.com/IllidanS4/PawnPlus.IO

#if defined _inc_PawnPlus_IO
#undef _inc_PawnPlus_IO
#endif

#if defined _PawnPlus_IO_included
#endinput
#endif
#define _PawnPlus_IO_included

/*                 */
/*      Setup      */
/*                 */

const PP_IO_VERSION = 0x010;


/*                 */
/*  Configuration  */
/*                 */

native pp_io_version();


/*                 */
/*       I/O       */
/*                 */

enum io_open_mode
{
	io_open_open = 0,
	io_open_create = 1,
	io_open_open_or_create = 2,
	io_open_append = 3,
}

enum io_data_mode
{
    io_data_raw = 0,
    io_data_unpacked = 1,
    io_data_packed = 2,
}

enum io_seek_whence
{
    io_seek_start = 0,
    io_seek_current = 1,
    io_seek_end = 2,
}

native Stream:io_open(const name[], io_open_mode:mode);
native Stream:io_buffer();
native io_close(Stream:stream);

native io_write_arr(Stream:stream, const data[], io_data_mode:mode=io_data_raw, size=sizeof(data));
native io_read_arr(Stream:stream, data[], io_data_mode:mode=io_data_raw, size=sizeof(data));
native io_seek(Stream:stream, position, io_seek_whence:whence=io_seek_start);
