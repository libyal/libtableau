/*
 * String functions
 *
 * Copyright (C) 2008-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <narrow_string.h>
#include <types.h>

#include "libtableau_libcerror.h"
#include "libtableau_string.h"

/* Copies a byte string to a character string
 * and trims whitespace and non readable characters
 * Returns the resulting string length if successful or -1 on error
 */
ssize_t libtableau_string_trim_copy(
         uint8_t *destination,
         const uint8_t *source,
         size_t source_length,
         libcerror_error_t **error )
{
	static char *function   = "libtableau_string_trim_copy";
	ssize_t first_character = 0;
	ssize_t last_character  = 0;

	if( destination == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination.",
		 function );

		return( -1 );
	}
	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( source_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid source length value exceeds maximum.",
		 function );

		return( -1 );
	}
	for( first_character = 0;
	     first_character < (ssize_t) source_length;
	     first_character++ )
	{
		if( ( source[ first_character ] >= (uint8_t) 0x21 )
		 && ( source[ first_character ] <= (uint8_t) 0x7e ) )
		{
			break;
		}
	}
	for( last_character = (ssize_t) ( source_length - 1 );
	     last_character >= 0;
	     last_character-- )
	{
		if( ( source[ last_character ] >= (uint8_t) 0x21 )
		 && ( source[ last_character ] <= (uint8_t) 0x7e ) )
		{
			break;
		}
	}
	if( last_character <= first_character )
	{
		return( 0 );
	}
	last_character -= first_character - 1;

	if( narrow_string_copy(
	     destination,
	     &( source[ first_character ] ),
	     last_character ) != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy trimmed string.",
		 function );

		return( -1 );
	}
	destination[ last_character + 1 ] = 0;

	return( last_character );
}

