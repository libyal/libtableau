/*
 * Shows information obtained from a Tableau write blocker
 *
 * Copyright (C) 2008-2019, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "tableautools_input.h"
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
	fprintf( stream, "Usage: tableaucontrol [ -hvV ] source\n\n" );

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
	system_character_t input_buffer[ 64 ];

	libcerror_error_t *error                  = NULL;
	libtableau_handle_t *handle               = NULL;
	system_character_t *fixed_string_variable = NULL;
	system_character_t *program               = _SYSTEM_STRING( "tableaucontrol" );
	system_character_t *source                = NULL;
	system_integer_t option                   = 0;
	int8_t input_confirmed                    = -1;
	int result                                = 0;
	int verbose                               = 0;

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

		return( EXIT_FAILURE );
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
	result = libtableau_handle_detected_dco(
	          handle,
	          &error );

	if( result == -1 )
	{
		fprintf(
		 stderr,
		 "Unable to detect DCO.\n" );

		goto on_error;
	}
	else if( result != 0 )
	{
		/* Ask for confirmation
		 */
		while( input_confirmed == -1 )
		{
			result = tableautools_input_get_fixed_string_variable(
			          stdout,
			          input_buffer,
			          64,
			          _SYSTEM_STRING( "Remove DCO from connected drive" ),
			          tableautools_input_yes_no,
			          2,
			          0,
			          &fixed_string_variable,
			          &error );

			if( result == -1 )
			{
				libcnotify_print_error_backtrace(
				 error );
				libcerror_error_free(
				 &error );

				fprintf(
				 stdout,
				 "Unable to determine answer.\n" );
			}
			else
			{
				result = tableautools_input_determine_yes_no(
					  fixed_string_variable,
					  (uint8_t *) &input_confirmed,
					  &error );

				if( result != 1 )
				{
					libcnotify_print_error_backtrace(
					 error );
					libcerror_error_free(
					 &error );

					fprintf(
					 stdout,
					 "Selected option not supported, please try again or terminate using Ctrl^C.\n" );
				}
			}
	        }
		if( input_confirmed != 0 )
		{
			if( libtableau_handle_remove_dco(
			     handle,
			     &error ) != 1 )
			{
				fprintf(
				 stderr,
				 "Unable to remove DCO.\n" );

				goto on_error;
			}
			fprintf(
			 stdout,
			 "Power cycle the drive to make sure the changes are detected.\n" );
		}
	}
	else
	{
		fprintf(
		 stdout,
		 "No DCO detected.\n" );
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

