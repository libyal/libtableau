/*
 * Handle functions
 *
 * Copyright (C) 2008-2019, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_SYS_IOCTL_H )
#include <sys/ioctl.h>
#endif

#if defined( HAVE_SCSI_SG_PT_H )
#include <scsi/sg_pt.h>
#endif

#if defined( HAVE_ERRNO_H )
#include <errno.h>
#endif

#include "libtableau_definitions.h"
#include "libtableau_handle.h"
#include "libtableau_io.h"
#include "libtableau_libcerror.h"
#include "libtableau_libclocale.h"
#include "libtableau_libcnotify.h"
#include "libtableau_libuna.h"
#include "libtableau_query.h"
#include "libtableau_security_values.h"
#include "libtableau_values.h"
#include "libtableau_values_table.h"

#include "tableau_header.h"
#include "tableau_page.h"
#include "tableau_query.h"

/* Creates a handle
 * Make sure the value handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libtableau_handle_initialize(
     libtableau_handle_t **handle,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_initialize";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( *handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle value already set.",
		 function );

		return( -1 );
	}
	internal_handle = memory_allocate_structure(
	                   libtableau_internal_handle_t );

	if( internal_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_handle,
	     0,
	     sizeof( libtableau_internal_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear handle.",
		 function );

		memory_free(
		 internal_handle );

		return( -1 );
	}
	if( libtableau_values_table_initialize(
	     &( internal_handle->values_table ),
	     LIBTABLEAU_DEFAULT_NUMBER_OF_TABLEAU_VALUES,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create values table.",
		 function );

		goto on_error;
	}
	if( libtableau_values_initialize(
	     internal_handle->values_table,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize values.",
		 function );

		goto on_error;
	}
	if( libtableau_security_values_initialize(
	     &( internal_handle->security_values ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create security values.",
		 function );

		goto on_error;
	}
	internal_handle->file_descriptor = -1;

	*handle = (libtableau_handle_t *) internal_handle;

	return( 1 );

on_error:
	if( internal_handle != NULL )
	{
		if( internal_handle->security_values != NULL )
		{
			libtableau_security_values_free(
			 &( internal_handle->security_values ),
			 NULL );
		}
		if( internal_handle->values_table != NULL )
		{
			libtableau_values_table_free(
			 &( internal_handle->values_table ),
			 NULL );
		}
		memory_free(
		 internal_handle );
	}
	return( -1 );
}

/* Frees a handle
 * Returns 1 if successful or -1 on error
 */
int libtableau_handle_free(
     libtableau_handle_t **handle,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_free";
	int result                                    = 1;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( *handle != NULL )
	{
		internal_handle = (libtableau_internal_handle_t *) *handle;
		*handle         = NULL;

		if( internal_handle->file_descriptor != -1 )
		{
			if( libtableau_handle_close(
			     *handle,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close handle.",
				 function );

				result = -1;
			}
		}
		if( libtableau_values_table_free(
		     &( internal_handle->values_table ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free values table.",
			 function );

			result = -1;
		}
		if( libtableau_security_values_free(
		     &( internal_handle->security_values ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free security values.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_handle );
	}
	return( result );
}

/* Opens a device
 * Returns 1 if successful or -1 on error
 */
int libtableau_handle_open(
     libtableau_handle_t *handle,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_open";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libtableau_internal_handle_t *) handle;

	if( internal_handle->file_descriptor != -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - file descriptor already set.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBTABLEAU_ACCESS_FLAG_READ ) == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported accesss flags.",
		 function );

		return( -1 );
	}
#if defined( HAVE_SCSI_SG_PT_H )
	internal_handle->file_descriptor = scsi_pt_open_device(
	                                    filename,
	                                    1,
	                                    libcnotify_verbose );

	if( internal_handle->file_descriptor == -1 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 errno,
		 "%s: unable to open file.",
		 function );

		return( -1 );
	}
	return( 1 );
#else
	libcerror_error_set(
	 error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "%s: missing SCSI support.",
	 function );

	return( -1 );

#endif /* defined( HAVE_SCSI_SG_PT_H ) */
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a device
 * Returns 1 if successful or -1 on error
 */
int libtableau_handle_open_wide(
     libtableau_handle_t *handle,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_open_wide";

#if defined( HAVE_SCSI_SG_PT_H )
	char *narrow_filename                         = NULL;
	size_t filename_length                        = 0;
	size_t narrow_filename_size                   = 0;
	int result                                    = 0;
#endif

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libtableau_internal_handle_t *) handle;

	if( internal_handle->file_descriptor != -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle - file descriptor already set.",
		 function );

		return( -1 );
	}
	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBTABLEAU_ACCESS_FLAG_READ ) == 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported accesss flags.",
		 function );

		return( -1 );
	}
#if defined( HAVE_SCSI_SG_PT_H )
	filename_length = wide_string_length(
	                   filename );

	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) filename,
		          filename_length + 1,
		          &narrow_filename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) filename,
		          filename_length + 1,
		          &narrow_filename_size,
		          error );
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) filename,
		          filename_length + 1,
		          libclocale_codepage,
		          &narrow_filename_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) filename,
		          filename_length + 1,
		          libclocale_codepage,
		          &narrow_filename_size,
		          error );
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow filename size.",
		 function );

		goto on_error;
	}
	narrow_filename = narrow_string_allocate(
	                   narrow_filename_size );

	if( narrow_filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create narrow filename.",
		 function );

		goto on_error;
	}
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_filename,
		          narrow_filename_size,
		          (libuna_utf32_character_t *) filename,
		          filename_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_filename,
		          narrow_filename_size,
		          (libuna_utf16_character_t *) filename,
		          filename_length + 1,
		          error );
#endif /* SIZEOF_WCHAR_T */
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_filename,
		          narrow_filename_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) filename,
		          filename_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_filename,
		          narrow_filename_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) filename,
		          filename_length + 1,
		          error );
#endif /* SIZEOF_WCHAR_T */
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow filename.",
		 function );

		return( -1 );
	}
	internal_handle->file_descriptor = scsi_pt_open_device(
	                                    narrow_filename,
	                                    1,
	                                    libcnotify_verbose );

	if( internal_handle->file_descriptor == -1 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 errno,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( narrow_filename != NULL )
	{
		memory_free(
		 narrow_filename );
	}
	return( -1 );
#else
	libcerror_error_set(
	 error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "%s: missing SCSI support.",
	 function );

	return( -1 );

#endif /* defined( HAVE_SCSI_SG_PT_H ) */
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Closes a device
 * Returns 0 if successful or -1 on error
 */
int libtableau_handle_close(
     libtableau_handle_t *handle,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_close";

#if defined( HAVE_SCSI_SG_PT_H )
	int result                                    = 0;
#endif

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libtableau_internal_handle_t *) handle;

	if( internal_handle->file_descriptor == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file descriptor.",
		 function );

		return( -1 );
	}
#if defined( HAVE_SCSI_SG_PT_H )
	result = scsi_pt_close_device(
	          internal_handle->file_descriptor );

	if( result != 0 )
	{
		libcerror_system_set_error(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 errno,
		 "%s: unable to close file descriptor.",
		 function );

		return( -1 );
	}
	internal_handle->file_descriptor = -1;

	return( 0 );
#else
	libcerror_error_set(
	 error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "%s: missing SCSI support.",
	 function );

	return( -1 );

#endif /* defined( HAVE_SCSI_SG_PT_H ) */
}

/* Queries the opened device for Tableau information
 * Returns 1 if successful or -1 on error
 */
int libtableau_handle_query(
     libtableau_handle_t *handle,
     libcerror_error_t **error )
{
	tableau_query_t tableau_query;

	uint8_t recv_buffer[ LIBTABLEAU_RECV_SIZE ];
	uint8_t sense_buffer[ LIBTABLEAU_SENSE_SIZE ];

	libtableau_internal_handle_t *internal_handle = NULL;
	tableau_header_t *tableau_header              = NULL;
	tableau_page_t *tableau_page                  = NULL;
	static char *function                         = "libtableau_handle_query";
	ssize_t recv_buffer_offset                    = 0;
	int result                                    = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libtableau_internal_handle_t *) handle;

	if( internal_handle->file_descriptor == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file descriptor.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     &tableau_query,
	     0,
	     sizeof( tableau_query_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear tableau query.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     recv_buffer,
	     0,
	     LIBTABLEAU_RECV_SIZE ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear recv buffer.",
		 function );

		return( -1 );
	}
	if( memory_set(
	     sense_buffer,
	     0,
	     LIBTABLEAU_SENSE_SIZE ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear sense buffer.",
		 function );

		return( -1 );
	}
	tableau_query.opcode        = TABLEAU_QUERY_SCSI_OPCODE;
	tableau_query.subcommand    = TABLEAU_QUERY_SUBCOMMAND_QUERY;
	tableau_query.response_size = LIBTABLEAU_RECV_SIZE;

	result = libtableau_io_send_command(
	          internal_handle->file_descriptor,
	          (uint8_t *) &tableau_query,
	          6,
	          recv_buffer,
	          LIBTABLEAU_RECV_SIZE,
	          sense_buffer,
	          LIBTABLEAU_SENSE_SIZE,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to send command.",
		 function );

		return( -1 );
	}
	tableau_header = (tableau_header_t *) recv_buffer;

	if( libtableau_query_parse_tableau_header(
	     tableau_header,
             internal_handle->values_table,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GENERIC,
		 "%s: unable to parse tableau header.",
		 function );

		return( -1 );
	}
	recv_buffer_offset = (ssize_t) sizeof( tableau_header_t );

	while( ( recv_buffer_offset + sizeof( tableau_page_t ) ) < (ssize_t) tableau_header->response_size )
	{
		tableau_page = (tableau_page_t *) &( recv_buffer[ recv_buffer_offset ] );

		if( libtableau_query_parse_tableau_page(
		     tableau_page,
		     &( recv_buffer[ recv_buffer_offset + sizeof( tableau_page_t ) ] ),
		     internal_handle->values_table,
		     internal_handle->security_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to parse tableau page.",
			 function );

			return( -1 );
		}
		recv_buffer_offset += (size_t) tableau_page->size;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( ( libcnotify_verbose != 0 )
	 && ( recv_buffer_offset < (ssize_t) sizeof( tableau_header_t ) ) )
	{
		libcnotify_printf(
		 "%s: detected trailing data.\n",
		 function );
	}
#endif
	return( 1 );
}

/* Retrieves the number of drive sectors
 * Returns 1 if successful, 0 if no number of drive sectors value is present or -1 on error
 */
int libtableau_handle_get_drive_number_of_sectors(
     libtableau_handle_t *handle,
     uint32_t *number_of_sectors,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_get_drive_number_of_sectors";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libtableau_internal_handle_t *) handle;

	if( number_of_sectors == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of sectors.",
		 function );

		return( -1 );
	}
	if( internal_handle->security_values == NULL )
	{
		return( 0 );
	}
	*number_of_sectors = internal_handle->security_values->drive_number_of_sectors;

	return( 1 );
}

/* Retrieves the number of HPA sectors
 * Returns 1 if successful, 0 if no number of HPA sectors value is present or -1 on error
 */
int libtableau_handle_get_hpa_number_of_sectors(
     libtableau_handle_t *handle,
     uint32_t *number_of_sectors,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_get_hpa_number_of_sectors";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libtableau_internal_handle_t *) handle;

	if( number_of_sectors == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of sectors.",
		 function );

		return( -1 );
	}
	if( internal_handle->security_values == NULL )
	{
		return( 0 );
	}
	*number_of_sectors = internal_handle->security_values->hpa_number_of_sectors;

	return( 1 );
}

/* Retrieves the number of DCO sectors
 * Returns 1 if successful, 0 if no number of DCO sectors value is present or -1 on error
 */
int libtableau_handle_get_dco_number_of_sectors(
     libtableau_handle_t *handle,
     uint32_t *number_of_sectors,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_get_dco_number_of_sectors";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libtableau_internal_handle_t *) handle;

	if( number_of_sectors == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of sectors.",
		 function );

		return( -1 );
	}
	if( internal_handle->security_values == NULL )
	{
		return( 0 );
	}
	*number_of_sectors = internal_handle->security_values->dco_number_of_sectors;

	return( 1 );
}

/* Retrieves the number of values
 * Returns 1 if successful, 0 if no values are present or -1 on error
 */
int libtableau_handle_get_number_of_values(
     libtableau_handle_t *handle,
     int *number_of_values,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_get_number_of_values";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libtableau_internal_handle_t *) handle;

	if( libtableau_values_table_get_number_of_values(
	     internal_handle->values_table,
	     number_of_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of values.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the value identifier specified by its index
 * Returns 1 if successful, 0 if not set or -1 on error
 */
int libtableau_handle_get_value_identifier(
     libtableau_handle_t *handle,
     int value_index,
     char *string,
     size_t string_size,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_get_value_identifier";
	int result                                    = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libtableau_internal_handle_t *) handle;

	result = libtableau_values_table_get_identifier(
	          internal_handle->values_table,
	          value_index,
	          string,
	          string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value identifier: %d.",
		 function,
		 value_index );

		return( -1 );
	}
	return( result );
}

/* Retrieves the value specified by the identifier
 * Returns 1 if successful, 0 if not set or -1 on error
 */
int libtableau_handle_get_value(
     libtableau_handle_t *handle,
     const char *identifier,
     char *string,
     size_t string_size,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_get_value";
	size_t identifier_length                      = 0;
	int result                                    = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libtableau_internal_handle_t *) handle;

	if( identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid values identifier.",
		 function );

		return( -1 );
	}
	identifier_length = narrow_string_length(
	                     identifier );

	result = libtableau_values_table_get_value_by_identifier(
	          internal_handle->values_table,
	          identifier,
	          identifier_length,
	          string,
	          string_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Detects the DCO from the opened device
 * Returns 1 if a DCO is present, 0 if no DCO is present or -1 on error
 */
int libtableau_handle_detected_dco(
     libtableau_handle_t *handle,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_detected_dco";

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libtableau_internal_handle_t *) handle;

	if( internal_handle->security_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing security values.",
		 function );

		return( -1 );
	}
	return( internal_handle->security_values->dco_number_of_sectors != internal_handle->security_values->hpa_number_of_sectors );
}

/* Removes the DCO from the opened device
 * Returns 1 if successful, 0 if no DCO is present or -1 on error
 */
int libtableau_handle_remove_dco(
     libtableau_handle_t *handle,
     libcerror_error_t **error )
{
	tableau_query_t tableau_query;

	uint8_t recv_buffer[ LIBTABLEAU_RECV_SIZE ];
	uint8_t sense_buffer[ LIBTABLEAU_SENSE_SIZE ];

	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_remove_dco";
	int result                                    = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libtableau_internal_handle_t *) handle;

	if( internal_handle->security_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing security values.",
		 function );

		return( -1 );
	}
	if( internal_handle->file_descriptor <= -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing file descriptor.",
		 function );

		return( -1 );
	}
	/* Check if the Tableau was queried
	 * and if a DCO is present
	 */
	if( internal_handle->security_values->dco_number_of_sectors == internal_handle->security_values->hpa_number_of_sectors )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: no DCO detected.\n",
			 function );
		}
#endif
		return( 0 );
	}
	if( memory_set(
	     &tableau_query,
	     0,
	     sizeof( tableau_query_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear tableau query.",
		 function );

		return( -1 );
	}
	tableau_query.opcode     = TABLEAU_QUERY_SCSI_OPCODE;
	tableau_query.subcommand = TABLEAU_QUERY_SUBCOMMAND_REMOVE_DCO;

	if( memory_copy(
	     &( tableau_query.dco_challenge_key ),
	     internal_handle->security_values->dco_challenge_key,
	     4 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy DCO challenge key.",
		 function );

		return( -1 );
	}
	result = libtableau_io_send_command(
	          internal_handle->file_descriptor,
	          (uint8_t *) &tableau_query,
	          12,
	          recv_buffer,
	          LIBTABLEAU_RECV_SIZE,
	          sense_buffer,
	          LIBTABLEAU_SENSE_SIZE,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to send command.",
		 function );

		return( -1 );
	}
	return( 1 );
}

