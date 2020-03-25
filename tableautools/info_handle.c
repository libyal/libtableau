/*
 * Info handle
 *
 * Copyright (C) 2008-2020, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#include "info_handle.h"
#include "tableautools_libcerror.h"
#include "tableautools_libtableau.h"

#define INFO_HANDLE_NOTIFY_STREAM	stdout

/* Creates an info handle
 * Make sure the value info_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_initialize";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid info handle value already set.",
		 function );

		return( -1 );
	}
	*info_handle = memory_allocate_structure(
	                info_handle_t );

	if( *info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create info handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *info_handle,
	     0,
	     sizeof( info_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear info handle.",
		 function );

		goto on_error;
	}
	if( libtableau_handle_initialize(
	     &( ( *info_handle )->input_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize intput handle.",
		 function );

		goto on_error;
	}
	( *info_handle )->notify_stream = INFO_HANDLE_NOTIFY_STREAM;

	return( 1 );

on_error:
	if( *info_handle != NULL )
	{
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( -1 );
}

/* Frees an info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_free(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_free";
	int result            = 1;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		if( libtableau_handle_free(
		     &( ( *info_handle )->input_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free input handle.",
			 function );

			result = -1;
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( result );
}

/* Signals the info handle to abort
 * Returns 1 if successful or -1 on error
 */
int info_handle_signal_abort(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_signal_abort";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	info_handle->abort = 1;

	return( 1 );
}

/* Opens the input handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_open_input(
     info_handle_t *info_handle,
     const system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "info_handle_open_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libtableau_handle_open_wide(
	     info_handle->input_handle,
	     filename,
	     LIBTABLEAU_OPEN_READ,
	     error ) != 1 )
#else
	if( libtableau_handle_open(
	     info_handle->input_handle,
	     filename,
	     LIBTABLEAU_OPEN_READ,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Closes the input handle
 * Returns the 0 if succesful or -1 on error
 */
int info_handle_close_input(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_close_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libtableau_handle_close(
	     info_handle->input_handle,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input handle.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Prints the device information
 * Returns 1 if successful or -1 on error
 */
int info_handle_device_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	char value_string[ 32 ];

	static char *function      = "info_handle_device_fprint";
	uint32_t number_of_sectors = 0;
	int result                 = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( libtableau_handle_query(
	     info_handle->input_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to query Tableau.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "Tableau forensic bridge information\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tVendor:" );

	result = libtableau_handle_get_value_bridge_vendor(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve bridge vendor.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tModel:" );

	result = libtableau_handle_get_value_bridge_model(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve bridge model.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tSerial number:" );

	result = libtableau_handle_get_value_bridge_serial_number(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve bridge serial number.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tFirmware date:" );

	result = libtableau_handle_get_value_bridge_firmware_date(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve bridge firmware date.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tFirmware time:" );

	result = libtableau_handle_get_value_bridge_firmware_time(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve bridge firmware date and time.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tFirmware stepping:" );

	result = libtableau_handle_get_value_bridge_firmware_stepping(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve bridge firmware stepping.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tDebug firmware:" );

	result = libtableau_handle_get_value_bridge_debug_firmware(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve bridge debug firmware.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tChannel index:" );

	result = libtableau_handle_get_value_bridge_channel_index(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve bridge channel index.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tChannel type:" );

	result = libtableau_handle_get_value_bridge_channel_type(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve bridge channel type.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tRead only mode:" );

	result = libtableau_handle_get_value_bridge_mode_read_only(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve bridge mode read-only.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tRead only reporting:" );

	result = libtableau_handle_get_value_bridge_report_read_only(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve bridge report read-only.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tWrite error reporting:" );

	result = libtableau_handle_get_value_bridge_report_write_error(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve bridge report write-error.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\nDrive information\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tVendor:" );

	result = libtableau_handle_get_value_drive_vendor(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve drive vendor.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tModel:" );

	result = libtableau_handle_get_value_drive_model(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve drive model.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tSerial number:" );

	result = libtableau_handle_get_value_drive_serial_number(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve drive serial number.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tRevision number:" );

	result = libtableau_handle_get_value_drive_revision_number(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve drive revision number.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\nDrive security information\n" );

	fprintf(
	info_handle->notify_stream,
	 "\tHPA support:" );

	result = libtableau_handle_get_value_drive_hpa_support(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve drive HPA support.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tHPA in use:" );

	result = libtableau_handle_get_value_drive_hpa_in_use(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve drive HPA in use.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tDCO support:" );

	result = libtableau_handle_get_value_drive_dco_support(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve drive DCO support.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tDCO in use:" );

	result = libtableau_handle_get_value_drive_dco_in_use(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve drive DCO in use.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tSecurity support:" );

	result = libtableau_handle_get_value_drive_security_support(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve drive security support.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	fprintf(
	 info_handle->notify_stream,
	 "\tSecurity in use:" );

	result = libtableau_handle_get_value_drive_security_in_use(
	          info_handle->input_handle,
	          value_string,
	          32,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve drive security in use.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\t%s",
		 value_string );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	result = libtableau_handle_get_drive_number_of_sectors(
	          info_handle->input_handle,
	          &number_of_sectors,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve drive number of sectors.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
        	fprintf(
		 info_handle->notify_stream,
		 "\tNumber of sectors:\t%" PRIu32 "\n",
	         number_of_sectors );
	}
	result = libtableau_handle_get_hpa_number_of_sectors(
	          info_handle->input_handle,
	          &number_of_sectors,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve HPA number of sectors.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
        	fprintf(
		 info_handle->notify_stream,
		 "\tHPA number of sectors:\t%" PRIu32 "\n",
	         number_of_sectors );
	}
	result = libtableau_handle_get_dco_number_of_sectors(
	          info_handle->input_handle,
	          &number_of_sectors,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve DCO number of sectors.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
        	fprintf(
		 info_handle->notify_stream,
		 "\tDCO number of sectors:\t%" PRIu32 "\n",
	         number_of_sectors );
	}
	/* TODO print additional information
	 */
	return( 1 );
}

