/*
 * Common input functions for the tableau tools
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
#include <character_string.h>
#include <notify.h>

#include "tableauinput.h"

character_t *tableauinput_yes_no[ 2 ] = \
 { _CHARACTER_T_STRING( "yes" ),
   _CHARACTER_T_STRING( "no" ) };

/* Determines the yes or no value from an argument string
 * Returns 1 if yes, 0 if no, or -1 on error
 */
int tableauinput_determine_yes_no(
     const character_t *argument )
{
	static char *function = "tableauinput_determine_yes_no";

	if( argument == NULL )
	{
		notify_warning_printf( "%s: invalid argument string.\n",
		 function );

		return( -1 );
	}
	else if( string_compare(
	          argument,
	          _CHARACTER_T_STRING( "yes" ),
	          3 ) == 0 )
	{
		return( 1 );
	}
	else if( string_compare(
	          argument,
	          _CHARACTER_T_STRING( "no" ),
	          2 ) == 0 )
	{
		return( 0 );
	}
	return( -1 );
}

/* Get fixed value input from the user
 * The first value is considered the default value
 */
character_t *tableauinput_get_fixed_value(
              FILE *stream,
              character_t *request_string,
              character_t **values,
              int amount,
              int default_value )
{
	character_t user_input_buffer[ 1024 ];

	character_t *user_input_buffer_ptr = &user_input_buffer[ 0 ];
	character_t *user_input            = NULL;
	static char *function              = "tableauinput_get_fixed_value";
	size_t input_length                = 0;
	size_t value_length                = 0;
	int iterator                       = 0;
	int value_match                    = 0;

	if( stream == NULL )
	{
		notify_warning_printf( "%s: invalid output stream.\n",
		 function );

		return( NULL );
	}
	if( request_string == NULL )
	{
		notify_warning_printf( "%s: invalid request string.\n",
		 function );

		return( NULL );
	}
	if( default_value >= amount )
	{
		notify_warning_printf( "%s: default value exceeds amount.\n",
		 function );

		return( NULL );
	}
	while( 1 )
	{
		fprintf( stream, "%" PRIs " (", request_string );

		for( iterator = 0; iterator < amount; iterator++ )
		{
			if( iterator > 0 )
			{
				fprintf( stream, ", " );
			}
			fprintf( stream, "%" PRIs "", values[ iterator ] );
		}
		fprintf( stream, ") [%" PRIs "]: ", values[ default_value ] );

		user_input_buffer_ptr = string_get_from_stream(
		                         user_input_buffer_ptr,
		                         1023,
		                         stdin );

		if( user_input_buffer_ptr != NULL )
		{
			iterator = 0;

			/* Remove the trailing newline character
			 */
			input_length = string_length(
			                user_input_buffer_ptr ) - 1;

			/* Check if the default value was selected
			 */
			if( input_length == 0 )
			{
				iterator = default_value;

				input_length = string_length(
				                values[ iterator ] );

				value_match  = 1;
			}
			else
			{
				while( iterator < amount )
				{
					value_length = string_length(
					                values[ iterator ] );

					if( string_compare(
					     user_input_buffer_ptr,
					     values[ iterator ],
					     value_length ) == 0 )
					{
						/* Make sure no trailing characters were given
						 */
						if( user_input_buffer_ptr[ value_length ] == (character_t) '\n' )
						{
							value_match = 1;

							break;
						}
					}
					iterator++;
				}
			}
		}
		else
		{
			fprintf( stream, "Error reading input, please try again or terminate using Ctrl^C.\n" );
		}
		if( value_match == 1 )
		{
			value_length = string_length(
			                values[ iterator ] );

#if defined( MEMWATCH )
			/* One additional character required for end of string
			 */
			user_input = memory_allocate(
			              sizeof( character_t ) * ( value_length + 1 ) );

			if( user_input == NULL )
			{
				notify_warning_printf( "%s: unable to create string.\n",
				 function );

				return( NULL );
			}
			if( string_copy(
			     user_input,
			     values[ iterator ],
			     value_length ) == NULL  )
			{
				notify_warning_printf( "%s: unable to copy string.\n",
				 function );

				memory_free(
				 user_input );

				return( NULL );
			}
			/* Make sure the string is \0 terminated
			 */
			user_input[ input_length ] = (character_t) '\0';
#else
			user_input = string_duplicate(
			              values[ iterator ],
			              value_length );

			if( user_input == NULL )
			{
				notify_warning_printf( "%s: unable to create string.\n",
				 function );

				return( NULL );
			}
#endif
			break;
		}
		else
		{
			fprintf( stream, "Selected option not supported, please try again or terminate using Ctrl^C.\n" );
		}
	}
	return( user_input );
}

