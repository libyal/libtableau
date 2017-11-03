/*
 * Shows information obtained from a Tableau write blocker
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
#include <file_stream.h>
#include <memory.h>
#include <system_string.h>
#include <types.h>

#include <stdio.h>

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "tableautools_libcerror.h"
#include "tableautools_libclocale.h"
#include "tableautools_libcnotify.h"
#include "tableautools_libtableau.h"
#include "tableautools_output.h"

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Usage: tableauinfo [ -hvV ] source\n\n" );

	fprintf( stream, "\t-h: shows this help\n" );
	fprintf( stream, "\t-v: verbose output to stderr\n" );
	fprintf( stream, "\t-V: print version\n" );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	system_character_t value_string[ 32 ];

	libcerror_error_t *error    = NULL;
	libtableau_handle_t *handle = NULL;
	system_character_t *program = _SYSTEM_STRING( "tableauinfo" );
	system_character_t *source  = NULL;
	system_integer_t option     = 0;
	uint32_t number_of_sectors  = 0;
	int result                  = 0;
	int verbose                 = 0;

	libcnotify_stream_set(
	 stderr,
	 NULL );
	libcnotify_verbose_set(
	 1 );

	if( libclocale_initialize(
	     "tableautools",
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize locale values.\n" );

		goto on_error;
	}
	if( tableautools_output_initialize(
	     _IONBF,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize output settings.\n" );

		goto on_error;
	}
	tableauoutput_version_fprint(
	 stdout,
	 program );

	while( ( option = getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "hvV" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %s\n",
				 argv[ optind ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (system_integer_t) 'v':
				verbose = 1;

				break;

			case (system_integer_t) 'V':
				tableauoutput_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source device.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

	libcnotify_verbose_set(
	 verbose );
	libtableau_notify_set_stream(
	 stderr,
	 NULL );
	libtableau_notify_set_verbose(
	 verbose );

	if( libtableau_handle_initialize(
	     &handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize libtableau handle.\n" );

		goto on_error;
	}
	/* Open the device
	 */
	if( libtableau_handle_open(
	     handle,
	     source,
	     LIBTABLEAU_OPEN_READ,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Error opening device: %" PRIs_SYSTEM ".\n",
		 source );

		goto on_error;
	}
	if( libtableau_handle_query(
	     handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to query Tableau.\n" );

		goto on_error;
	}
	if( libtableau_handle_close(
	     handle,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Error closing device: %" PRIs_SYSTEM ".\n",
		 source );

		goto on_error;
	}
	fprintf(
	 stdout,
	 "Tableau forensic bridge information\n" );

	fprintf(
	 stdout,
	 "\tVendor:" );

	result = libtableau_handle_get_value_bridge_vendor(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve bridge vendor.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tModel:" );

	result = libtableau_handle_get_value_bridge_model(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve bridge model.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tSerial number:" );

	result = libtableau_handle_get_value_bridge_serial_number(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve bridge serial number.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tFirmware date:" );

	result = libtableau_handle_get_value_bridge_firmware_date(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve bridge firmware date.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tFirmware time:" );

	result = libtableau_handle_get_value_bridge_firmware_time(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve bridge firmware date and time.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tFirmware stepping:" );

	result = libtableau_handle_get_value_bridge_firmware_stepping(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve bridge firmware stepping.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tDebug firmware:" );

	result = libtableau_handle_get_value_bridge_debug_firmware(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve bridge debug firmware.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tChannel index:" );

	result = libtableau_handle_get_value_bridge_channel_index(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve bridge channel index.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tChannel type:" );

	result = libtableau_handle_get_value_bridge_channel_type(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve bridge channel type.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tRead only mode:" );

	result = libtableau_handle_get_value_bridge_mode_read_only(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve bridge mode read-only.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tRead only reporting:" );

	result = libtableau_handle_get_value_bridge_report_read_only(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve bridge report read-only.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tWrite error reporting:" );

	result = libtableau_handle_get_value_bridge_report_write_error(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve bridge report write-error.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\nDrive information\n" );

	fprintf(
	 stdout,
	 "\tVendor:" );

	result = libtableau_handle_get_value_drive_vendor(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve drive vendor.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tModel:" );

	result = libtableau_handle_get_value_drive_model(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve drive model.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tSerial number:" );

	result = libtableau_handle_get_value_drive_serial_number(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve drive serial number.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tRevision number:" );

	result = libtableau_handle_get_value_drive_revision_number(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve drive revision number.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\nDrive security information\n" );

	fprintf(
	stdout,
	 "\tHPA support:" );

	result = libtableau_handle_get_value_drive_hpa_support(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve drive HPA support.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tHPA in use:" );

	result = libtableau_handle_get_value_drive_hpa_in_use(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve drive HPA in use.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tDCO support:" );

	result = libtableau_handle_get_value_drive_dco_support(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve drive DCO support.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tDCO in use:" );

	result = libtableau_handle_get_value_drive_dco_in_use(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve drive DCO in use.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tSecurity support:" );

	result = libtableau_handle_get_value_drive_security_support(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve drive security support.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	fprintf(
	 stdout,
	 "\tSecurity in use:" );

	result = libtableau_handle_get_value_drive_security_in_use(
	          handle,
	          value_string,
	          32,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve drive security in use.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
		fprintf(
		 stdout,
		 "\t%s",
		 value_string );
	}
	fprintf(
	 stdout,
	 "\n" );

	result = libtableau_handle_get_drive_number_of_sectors(
	          handle,
	          &number_of_sectors,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve drive number of sectors.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
        	fprintf(
		 stdout,
		 "\tNumber of sectors:\t%" PRIu32 "\n",
	         number_of_sectors );
	}
	result = libtableau_handle_get_hpa_number_of_sectors(
	          handle,
	          &number_of_sectors,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve HPA number of sectors.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
        	fprintf(
		 stdout,
		 "\tHPA number of sectors:\t%" PRIu32 "\n",
	         number_of_sectors );
	}
	result = libtableau_handle_get_dco_number_of_sectors(
	          handle,
	          &number_of_sectors,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve DCO number of sectors.\n" );

		goto on_error;
	}
	else if( result == 1 )
	{
        	fprintf(
		 stdout,
		 "\tDCO number of sectors:\t%" PRIu32 "\n",
	         number_of_sectors );
	}

	/* TODO print additional Tableau information
	 */
	if( libtableau_handle_free(
	     &handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free libtableau handle.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcnotify_print_error_backtrace(
		 error );
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libtableau_handle_free(
		 &handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

