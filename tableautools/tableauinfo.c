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
#if defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	character_t value_string[ 32 ];

	libtableau_handle_t *handle      = NULL;
	character_t *program             = _CHARACTER_T_STRING( "tableauinfo" );
#if defined( HAVE_STRERROR_R ) || defined( HAVE_STRERROR )
	system_character_t *error_string = NULL;
#endif
	system_integer_t option          = 0;
	uint32_t amount_of_sectors       = 0;
	int verbose                      = 0;

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
	                   _SYSTEM_CHARACTER_T_STRING( "hvV" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf( stderr, "Invalid argument: %s\n",
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
		fprintf( stderr, "Missing source device.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	libtableau_set_notify_values(
	 stderr,
	 verbose );

	if( libtableau_handle_initialize(
	     &handle ) != 1 )
	{
		fprintf( stderr, "Unable to initialize libtableau handle.\n" );

		return( EXIT_FAILURE );
	}
	/* Open the device
	 */
	if( libtableau_open(
	     handle,
	     argv[ optind ] ) != 1 )
	{
#if defined( HAVE_STRERROR_R ) || defined( HAVE_STRERROR )
		if( errno != 0 )
		{
			error_string = tableauoutput_strerror(
			                errno );
		}
		if( error_string != NULL )
		{
			fprintf( stderr, "Error opening device: %" PRIs_SYSTEM " with failure: %" PRIs_SYSTEM ".\n",
			 argv[ optind ], error_string );

			memory_free(
			 error_string );
		}
		else
		{
			fprintf( stderr, "Error opening device: %" PRIs_SYSTEM ".\n",
			 argv[ optind ] );
		}
#else
		fprintf( stderr, "Error opening device: %" PRIs_SYSTEM ".\n",
		 argv[ optind ] );
#endif
		return( EXIT_FAILURE );
	}
	if( libtableau_query(
	     handle ) != 1 )
	{
		fprintf( stderr, "Unable to query Tableau.\n" );

		libtableau_close(
		 handle );
		libtableau_handle_free(
		 &handle );

		return( EXIT_FAILURE );
	}
	if( libtableau_close(
	     handle ) != 0 )
	{
#if defined( HAVE_STRERROR_R ) || defined( HAVE_STRERROR )
		if( errno != 0 )
		{
			error_string = tableauoutput_strerror(
			                errno );
		}
		if( error_string != NULL )
		{
			fprintf( stderr, "Error closing device: %" PRIs_SYSTEM " with failure: %" PRIs_SYSTEM ".\n",
			 argv[ optind ], error_string );

			memory_free(
			 error_string );
		}
		else
		{
			fprintf( stderr, "Error closing device: %" PRIs_SYSTEM ".\n",
			 argv[ optind ] );
		}
#else
		fprintf( stderr, "Error closing device: %" PRIs_SYSTEM ".\n",
		 argv[ optind ] );
#endif
		return( EXIT_FAILURE );
	}
	fprintf( stdout, "Tableau forensic bridge information\n" );

	fprintf( stdout, "\tVendor:" );

	if( libtableau_get_tableau_value_bridge_vendor(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tModel:" );

	if( libtableau_get_tableau_value_bridge_model(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tSerial number:" );

	if( libtableau_get_tableau_value_bridge_serial_number(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tFirmware date:" );

	if( libtableau_get_tableau_value_bridge_firmware_date(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tFirmware time:" );

	if( libtableau_get_tableau_value_bridge_firmware_time(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tFirmware stepping:" );

	if( libtableau_get_tableau_value_bridge_firmware_stepping(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tDebug firmware:" );

	if( libtableau_get_tableau_value_bridge_debug_firmware(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tChannel index:" );

	if( libtableau_get_tableau_value_bridge_channel_index(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tChannel type:" );

	if( libtableau_get_tableau_value_bridge_channel_type(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tRead only mode:" );

	if( libtableau_get_tableau_value_bridge_mode_read_only(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tRead only reporting:" );

	if( libtableau_get_tableau_value_bridge_report_read_only(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tWrite error reporting:" );

	if( libtableau_get_tableau_value_bridge_report_write_error(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\nDrive information\n" );

	fprintf( stdout, "\tVendor:" );

	if( libtableau_get_tableau_value_drive_vendor(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tModel:" );

	if( libtableau_get_tableau_value_drive_model(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tSerial number:" );

	if( libtableau_get_tableau_value_drive_serial_number(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tRevision number:" );

	if( libtableau_get_tableau_value_drive_revision_number(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\nDrive security information\n" );

	fprintf( stdout, "\tHPA support:" );

	if( libtableau_get_tableau_value_drive_hpa_support(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tHPA in use:" );

	if( libtableau_get_tableau_value_drive_hpa_in_use(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tDCO support:" );

	if( libtableau_get_tableau_value_drive_dco_support(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tDCO in use:" );

	if( libtableau_get_tableau_value_drive_dco_in_use(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tSecurity support:" );

	if( libtableau_get_tableau_value_drive_security_support(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	fprintf( stdout, "\tSecurity in use:" );

	if( libtableau_get_tableau_value_drive_security_in_use(
	     handle,
	     value_string,
	     32 ) == 1 )
	{
		fprintf( stdout, "\t%s",
		 value_string );
	}
	fprintf( stdout, "\n" );

	if( libtableau_get_drive_amount_of_sectors(
	     handle,
	     &amount_of_sectors ) == 1 )
	{
        	fprintf( stdout, "\tAmount of sectors:\t%" PRIu32 "\n",
	         amount_of_sectors );
	}
	if( libtableau_get_hpa_amount_of_sectors(
	     handle,
	     &amount_of_sectors ) == 1 )
	{
        	fprintf( stdout, "\tHPA amount of sectors:\t%" PRIu32 "\n",
	         amount_of_sectors );
	}
	if( libtableau_get_dco_amount_of_sectors(
	     handle,
	     &amount_of_sectors ) == 1 )
	{
        	fprintf( stdout, "\tDCO amount of sectors:\t%" PRIu32 "\n",
	         amount_of_sectors );
	}

	/* TODO print additional Tableau information
	 */
	if( libtableau_handle_free(
	     &handle ) != 1 )
	{
		fprintf( stderr, "Unable to free libtableau handle.\n" );

		return( EXIT_FAILURE );
	}
	return( EXIT_SUCCESS );
}

