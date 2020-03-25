/*
 * Common input functions for the tableau tools
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
#include <narrow_string.h>
#include <types.h>
#include <system_string.h>
#include <wide_string.h>

#include "tableautools_input.h"

system_character_t *tableautools_input_yes_no[ 2 ] = {
	_SYSTEM_STRING( "yes" ),
	_SYSTEM_STRING( "no" ) };

/* Determines the yes or no value from a string
 * Returns 1 if successful, 0 if unsupported value or -1 on error
 */
int tableautools_input_determine_yes_no(
     const system_character_t *string,
     uint8_t *yes_no_value,
     libcerror_error_t **error )
{
	static char *function = "tableautools_input_determine_yes_no";
	size_t string_length  = 0;
	int result            = 0;

	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( yes_no_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid yes no value.",
		 function );

		return( -1 );
	}
	string_length = system_string_length(
	                 string );

	if( string_length == 2 )
	{
		if( system_string_compare(
		     string,
		     _SYSTEM_STRING( "no" ),
		     2 ) == 0 )
		{
			*yes_no_value = 0;
			result        = 1;
		}
	}
	else if( string_length == 3 )
	{
		if( system_string_compare(
		     string,
		     _SYSTEM_STRING( "yes" ),
		     3 ) == 0 )
		{
			*yes_no_value = 1;
			result        = 1;
		}
	}
	return( result );
}

/* Retrieves a fixed value string variable
 * Returns 1 if successful, 0 if no input was provided or -1 on error
 */
int tableautools_input_get_fixed_string_variable(
     FILE *stream,
     system_character_t *input_buffer,
     size_t input_buffer_size,
     const system_character_t *request_string,
     system_character_t **values,
     uint8_t number_of_values,
     uint8_t default_value,
     system_character_t **fixed_string_variable,
     libcerror_error_t **error )
{

	system_character_t *end_of_input  = NULL;
	system_character_t *result_string = NULL;
	static char *function             = "tableautools_input_get_fixed_string_variable";
	size_t value_length               = 0;
	ssize_t input_length              = 0;
	uint8_t value_iterator            = 0;

	if( stream == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid output stream.",
		 function );

		return( -1 );
	}
	if( input_buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid input buffer.",
		 function );

		return( -1 );
	}
#if SIZEOF_SIZE_T > SIZEOF_INT
	if( input_buffer_size > (size_t) INT_MAX )
#else
	if( input_buffer_size > (size_t) SSIZE_MAX )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid input buffer size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( request_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid request string.",
		 function );

		return( -1 );
	}
	if( default_value >= number_of_values )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: default value exceeds number of values.",
		 function );

		return( -1 );
	}
	if( fixed_string_variable == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid fixed string variable.",
		 function );

		return( -1 );
	}
	while( 1 )
	{
		fprintf(
		 stream,
		 "%" PRIs_SYSTEM " (",
		 request_string );

		for( value_iterator = 0;
		     value_iterator < number_of_values;
		     value_iterator++ )
		{
			if( value_iterator > 0 )
			{
				fprintf(
				 stream,
				 ", " );
			}
			fprintf(
			 stream,
			 "%" PRIs_SYSTEM "",
			 values[ value_iterator ] );
		}
		fprintf(
		 stream,
		 ") [%" PRIs_SYSTEM "]: ",
		 values[ default_value ] );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result_string = file_stream_get_string_wide(
		                 stdin,
		                 input_buffer,
		                 (int) ( input_buffer_size - 1 ) );
#else
		result_string = file_stream_get_string(
		                 stdin,
		                 input_buffer,
		                 (int) ( input_buffer_size - 1 ) );
#endif
		if( result_string != NULL )
		{
			end_of_input = system_string_search_character(
			                input_buffer,
			                (system_character_t) '\n',
			                input_buffer_size );

			/* Input was larger than size of buffer
			 */
			if( end_of_input == NULL )
			{
				/* Flush the stdin stream
				 */
				while( end_of_input == NULL )
				{
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
					result_string = file_stream_get_string_wide(
					                 stdin,
					                 input_buffer,
					                 (int) ( input_buffer_size - 1 ) );
#else
					result_string = file_stream_get_string(
					                 stdin,
					                 input_buffer,
					                 (int) ( input_buffer_size - 1 ) );
#endif
					end_of_input = system_string_search_character(
					                input_buffer,
					                (system_character_t) '\n',
					                input_buffer_size );

				}
				return( -1 );
			}
			input_length = (ssize_t) ( end_of_input - input_buffer );

			if( input_length < 0 )
			{
				return( -1 );
			}
			else if( input_length == 0 )
			{
				*fixed_string_variable = values[ default_value ];

				return( 0 );
			}
			for( value_iterator = 0;
			     value_iterator < number_of_values;
			     value_iterator++ )
			{
				value_length = system_string_length(
						values[ value_iterator ] );

				if( ( value_length == (size_t) input_length )
				 && ( system_string_compare(
				       input_buffer,
				       values[ value_iterator ],
				       value_length ) == 0 ) )
				{
					break;
				}
			}
			if( value_iterator < number_of_values )
			{
				*fixed_string_variable = values[ value_iterator ];

				break;
			}
			fprintf(
			 stream,
			 "Selected option not supported, please try again or terminate using Ctrl^C.\n" );
		}
		else
		{
			fprintf(
			 stream,
			 "Error reading input, please try again or terminate using Ctrl^C.\n" );
		}
	}
	return( 1 );
}

