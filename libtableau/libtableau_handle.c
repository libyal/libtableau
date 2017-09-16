/*
 * Handle functions
 *
 * Copyright (C) 2008-2017, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_SYS_IOCTL_H )
#include <sys/ioctl.h>
#endif

#if defined( HAVE_SCSI_SG_PT_H )
#include <scsi/sg_pt.h>

#else
#error Missing SCSI support
#endif

#include "libtableau_definitions.h"
#include "libtableau_handle.h"
#include "libtableau_io.h"
#include "libtableau_libcerror.h"
#include "libtableau_libcnotify.h"
#include "libtableau_query.h"
#include "libtableau_security_values.h"
#include "libtableau_tableau_values.h"
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
	     &( internal_handle->tableau_values ),
	     LIBTABLEAU_DEFAULT_NUMBER_OF_TABLEAU_VALUES,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create tableau values table.",
		 function );

		goto on_error;
	}
	if( libtableau_tableau_values_initialize(
	     internal_handle->tableau_values,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize tableau values.",
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
	if( internal_handle->security_values != NULL )
	{
		libtableau_security_values_free(
		 &( internal_handle->security_values ),
		 NULL );
	}
	if( internal_handle->tableau_values != NULL )
	{
		libtableau_values_table_free(
		 &( internal_handle->tableau_values ),
		 NULL );
	}
	if( internal_handle != NULL )
	{
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
		if( internal_handle->tableau_values != NULL )
		{
			if( libtableau_values_table_free(
			     &( internal_handle->tableau_values ),
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free tableau values.",
				 function );

				result = -1;
			}
		}
		if( internal_handle->security_values != NULL )
		{
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
	internal_handle->file_descriptor = scsi_pt_open_device(
	                                    filename,
	                                    1,
	                                    libcnotify_verbose );

	if( internal_handle->file_descriptor == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to open file.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Closes a device
 * Returns 0 if successful or -1 on error
 */
int libtableau_handle_close(
     libtableau_handle_t *handle,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_close";
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
	result = scsi_pt_close_device(
	          internal_handle->file_descriptor );

	if( result != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file descriptor.",
		 function );

		return( -1 );
	}
	internal_handle->file_descriptor = -1;

	return( 0 );
}

/* Queries the opened device for Tableau information
 * Returns 1 if successful or -1 on error
 */
int libtableau_query(
     libtableau_handle_t *handle,
     libcerror_error_t **error )
{
	tableau_query_t tableau_query;

	uint8_t recv_buffer[ LIBTABLEAU_RECV_SIZE ];
	uint8_t sense_buffer[ LIBTABLEAU_SENSE_SIZE ];

	libtableau_internal_handle_t *internal_handle = NULL;
	tableau_header_t *tableau_header              = NULL;
	tableau_page_t *tableau_page                  = NULL;
	static char *function                         = "libtableau_query";
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
             internal_handle->tableau_values,
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
		     internal_handle->tableau_values,
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
#if defined( HAVE_VERBOSE_OUTPUT )
	if( recv_buffer_offset < (ssize_t) sizeof( tableau_header_t ) )
	{
		notify_verbose_printf( "%s: detected trailing data.\n",
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

/* Retrieves the number of tableau values
 * Returns 1 if successful, 0 if no tableau values are present or -1 on error
 */
int libtableau_handle_get_number_of_tableau_values(
     libtableau_handle_t *handle,
     uint32_t *number_of_values,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_get_number_of_tableau_values";

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

/* TODO move into values table */
	if( number_of_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of values.",
		 function );

		return( -1 );
	}
	if( internal_handle->tableau_values == NULL )
	{
		return( 0 );
	}
	*number_of_values = internal_handle->tableau_values->number_of_values;

	return( 1 );
}

/* Retrieves the tableau value identifier specified by its index
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
int libtableau_handle_get_tableau_value_identifier(
     libtableau_handle_t *handle,
     uint32_t index,
     char *value,
     size_t length,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_get_tableau_value_identifier";

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

	if( internal_handle->tableau_values == NULL )
	{
		return( 0 );
	}
/* TODO set error */
	return( libtableau_values_table_get_identifier(
	         internal_handle->tableau_values,
	         index,
	         value,
	         length,
	         error ) );
}

/* Retrieves the tableau value specified by the identifier
 * Returns 1 if successful, 0 if value not present or -1 on error
 */
int libtableau_handle_get_tableau_value(
     libtableau_handle_t *handle,
     const char *identifier,
     char *value,
     size_t length,
     libcerror_error_t **error )
{
	libtableau_internal_handle_t *internal_handle = NULL;
	static char *function                         = "libtableau_handle_get_tableau_value";

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
		 "%s: invalid identifier.",
		 function );

		return( -1 );
	}
	if( value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid value.",
		 function );

		return( -1 );
	}
	if( internal_handle->tableau_values == NULL )
	{
		return( 0 );
	}
/* TODO set error */
	return( libtableau_values_table_get_value(
	         internal_handle->tableau_values,
	         identifier,
	         value,
	         length,
	         error ) );
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
#if defined( HAVE_VERBOSE_OUTPUT )
		notify_verbose_printf( "%s: no DCO detected.\n",
		 function );
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

