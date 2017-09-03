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

#include "tableauinput.h"
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
#if defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libtableau_handle_t *handle      = NULL;
	character_t *program             = _CHARACTER_T_STRING( "tableaucontrol" );
	character_t *user_input          = NULL;
#if defined( HAVE_STRERROR_R ) || defined( HAVE_STRERROR )
	system_character_t *error_string = NULL;
#endif

	system_integer_t option          = 0;
	int input_confirmed              = -1;
	int verbose                      = 0;
	int result                       = 0;

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
	result = libtableau_detected_dco(
	          handle );

	if( result == -1 )
	{
		fprintf( stderr, "Unable to detect DCO.\n" );

		libtableau_close(
		 handle );
		libtableau_handle_free(
		 &handle );

		return( EXIT_FAILURE );
	}
	else if( result != 0 )
	{
		/* Ask for confirmation
		 */
		while( input_confirmed == -1 )
		{
			user_input = tableauinput_get_fixed_value(
			              stdout,
			              _CHARACTER_T_STRING( "Remove DCO from connected drive" ),
			              tableauinput_yes_no,
			              2,
			              1 );

			input_confirmed = tableauinput_determine_yes_no(
			                   user_input );

	                memory_free(
        	         user_input );

	                if( input_confirmed <= -1 )
	                {
        	                fprintf( stdout, "Selected option not supported, please try again or terminate using Ctrl^C.\n" );
	                }
	        }
		if( input_confirmed != 0 )
		{
			if( libtableau_remove_dco(
			     handle ) != 1 )
			{
				fprintf( stderr, "Unable to remove DCO.\n" );

				libtableau_close(
				 handle );
				libtableau_handle_free(
				 &handle );

				return( EXIT_FAILURE );
			}
			fprintf( stdout, "Power cycle the drive to make sure the changes are detected.\n" );
		}
	}
	else
	{
		fprintf( stdout, "No DCO detected.\n" );
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
	if( libtableau_handle_free(
	     &handle ) != 1 )
	{
		fprintf( stderr, "Unable to free libtableau handle.\n" );

		return( EXIT_FAILURE );
	}
	return( EXIT_SUCCESS );
}

