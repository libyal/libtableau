/*
 * Values table
 *
 * Copyright (C) 2008-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_STRING_H ) || defined( WINAPI )
#include <string.h>
#endif

#include "libtableau_definitions.h"
#include "libtableau_libcerror.h"
#include "libtableau_values_table.h"
#include "libtableau_string.h"

/* Creates values table
 * Make sure the value values_table is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libtableau_values_table_initialize(
     libtableau_values_table_t **values_table,
     int number_of_values,
     libcerror_error_t **error )
{
	static char *function    = "libtableau_values_table_initialize";
	size_t values_table_size = 0;

	if( values_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid values table.",
		 function );

		return( -1 );
	}
	if( *values_table != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid values table value already set.",
		 function );

		return( -1 );
	}
	if( number_of_values <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid number of values value zero or less.",
		 function );

		return( -1 );
	}
	values_table_size = number_of_values * sizeof( char * );

	if( ( values_table_size == 0 )
	 || ( values_table_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid number of values value out of bounds.",
		 function );

		return( -1 );
	}
	*values_table = memory_allocate_structure(
	                 libtableau_values_table_t );

	if( *values_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create values table.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *values_table,
	     0,
	     sizeof( libtableau_values_table_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear values table.",
		 function );

		memory_free(
		 *values_table );

		*values_table = NULL;

		return( -1 );
	}
	( *values_table )->identifiers = (char **) memory_allocate(
	                                            values_table_size );

	if( ( *values_table )->identifiers == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create identifiers.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     ( *values_table )->identifiers,
	     0,
	     values_table_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear identifiers.",
		 function );

		goto on_error;
	}
	( *values_table )->values = (char **) memory_allocate(
	                                       values_table_size );

	if( ( *values_table )->values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     ( *values_table )->values,
	     0,
	     values_table_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear values.",
		 function );

		goto on_error;
	}
	( *values_table )->number_of_values = number_of_values;

	return( 1 );

on_error:
	if( *values_table != NULL )
	{
		if( ( *values_table )->values != NULL )
		{
			memory_free(
			 ( *values_table )->values );
		}
		if( ( *values_table )->identifiers != NULL )
		{
			memory_free(
			 ( *values_table )->identifiers );
		}
		memory_free(
		 *values_table );

		*values_table = NULL;
	}
	return( -1 );
}

/* Frees values table
 * Returns 1 if successful or -1 on error
 */
int libtableau_values_table_free(
     libtableau_values_table_t **values_table,
     libcerror_error_t **error )
{
	static char *function = "libtableau_values_table_free";
	int value_index       = 0;

	if( values_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid values table.",
		 function );

		return( -1 );
	}
	if( *values_table != NULL )
	{
		for( value_index = 0;
		     value_index < ( *values_table )->number_of_values;
		     value_index++ )
		{
			if( ( ( *values_table )->identifiers )[ value_index ] != NULL )
			{
				memory_free(
				 ( ( *values_table )->identifiers )[ value_index ] );
			}
			if( ( ( *values_table )->values )[ value_index ] != NULL )
			{
				memory_free(
				 ( ( *values_table )->values )[ value_index ] );
			}
		}
		if( ( *values_table )->identifiers != NULL )
		{
			memory_free(
			 ( *values_table )->identifiers );
		}
		if( ( *values_table )->values != NULL )
		{
			memory_free(
			 ( *values_table )->values );
		}
		memory_free(
		 *values_table );

		*values_table = NULL;
	}
	return( 1 );
}

/* Resizes the values table
 * Returns 1 if successful, or -1 on error
 */
int libtableau_values_table_resize(
     libtableau_values_table_t *values_table,
     int number_of_values,
     libcerror_error_t **error )
{
	static char *function = "libtableau_values_table_resize";
	char **reallocation   = NULL;
	size_t current_size   = 0;
	size_t new_size       = 0;

	if( values_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid values table.",
		 function );

		return( -1 );
	}
	if( values_table->number_of_values <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid values table - number of values value zero or less.",
		 function );

		return( -1 );
	}
	if( number_of_values <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid number of values value zero or less.",
		 function );

		return( -1 );
	}
	if( number_of_values <= values_table->number_of_values )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: new number of values smaller than previous.",
		 function );

		return( -1 );
	}
	current_size = values_table->number_of_values * sizeof( char * );
	new_size     = number_of_values * sizeof( char * );

	if( ( current_size > (size_t) SSIZE_MAX )
	 || ( new_size > (ssize_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
	reallocation = (char **) memory_reallocate(
	                          values_table->identifiers,
	                          new_size );

	if( reallocation == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to reallocate identifiers.",
		 function );

		return( -1 );
	}
	values_table->identifiers = reallocation;

        if( memory_set(
             &( values_table->identifiers[ values_table->number_of_values ] ),
             0,
             ( new_size - current_size ) ) == NULL )
        {
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
                 "%s: unable to clear identifiers.",
                 function );

                return( -1 );
        }
	reallocation = (char **) memory_reallocate(
	                          values_table->values,
	                          new_size );

	if( reallocation == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to reallocate values.",
		 function );

		return( -1 );
	}
	values_table->values = reallocation;

        if( memory_set(
             &( values_table->values[ values_table->number_of_values ] ),
             0,
             ( new_size - current_size ) ) == NULL )
        {
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
                 "%s: unable to clear values.",
                 function );

                return( -1 );
        }
	values_table->number_of_values = number_of_values;

	return( 1 );
}

/* Retrieves the number of values in the table
 * Returns 1 if successful, or -1 on error
 */
int libtableau_values_table_get_number_of_values(
     libtableau_values_table_t *values_table,
     int *number_of_values,
     libcerror_error_t **error )
{
	static char *function = "libtableau_values_table_get_number_of_values";

	if( values_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid values table.",
		 function );

		return( -1 );
	}
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
	*number_of_values = values_table->number_of_values;

	return( 1 );
}

/* Retrieves the value index number, or -1 on error
 * The value index will be larger than the number_of_values when the identifier is not set in the values table
 */
int libtableau_values_table_get_index(
     libtableau_values_table_t *values_table,
     const char *identifier,
     size_t identifier_length,
     libcerror_error_t **error )
{
	static char *function = "libtableau_values_table_get_index";
	size_t string_length  = 0;
	int value_index       = 0;

	if( values_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid values table.",
		 function );

		return( -1 );
	}
	if( values_table->number_of_values <= 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid values table - number of values value zero or less.",
		 function );

		return( -1 );
	}
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
	if( ( identifier_length == 0 )
	 || ( identifier_length > (size_t) ( SSIZE_MAX - 1 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid identifier length value out of bounds.",
		 function );

		return( -1 );
	}
	for( value_index = 0;
	     value_index < values_table->number_of_values;
	     value_index++ )
	{
		if( values_table->identifiers[ value_index ] == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing identifier for index: %d.",
			 function,
			 value_index );

			return( -1 );
		}
		string_length = narrow_string_length(
		                 values_table->identifiers[ value_index ] );

		if( string_length == 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: unable to determine length of identifier of index: %d.",
			 function,
			 value_index );

			return( -1 );
		}
		if( string_length != identifier_length )
		{
			continue;
		}
		if( narrow_string_compare(
		     identifier,
		     values_table->identifiers[ value_index ],
		     identifier_length ) == 0 )
		{
			return( value_index );
		}
	}
	return( value_index );
}

/* Retrieves an identifier in the values table
 * The string size should include the end of string character
 * Returns 1 if successful, 0 if not set or -1 on error
 */
int libtableau_values_table_get_identifier(
     libtableau_values_table_t *values_table,
     int value_index,
     char *string,
     size_t string_size,
     libcerror_error_t **error )
{
	static char *function    = "libtableau_values_table_get_identifier";
	size_t identifier_length = 0;

	if( values_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid values table.",
		 function );

		return( -1 );
	}
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
	if( ( string_size == 0 )
	 || ( string_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid string size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( value_index < 0 )
	 || ( value_index >= values_table->number_of_values ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid value index value out of bounds.",
		 function );

		return( -1 );
	}
	if( values_table->identifiers[ value_index ] == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing identifier for value index: %" PRIu32 ".",
		 function,
		 value_index );

		return( -1 );
	}
	identifier_length = narrow_string_length(
	                     values_table->identifiers[ value_index ] );

	/* Do not bother with empty values
	 */
	if( identifier_length == 0 )
	{
		return( 0 );
	}
	if( identifier_length > ( string_size - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: string too small.",
		 function );

		return( -1 );
	}
	if( narrow_string_copy(
	     string,
	     values_table->identifiers[ value_index ],
	     identifier_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier.",
		 function );

		return( -1 );
	}
	string[ identifier_length ] = 0;

	return( 1 );
}

/* Sets an identifier in the values table
 * Frees an existing identifier if necessary
 * Returns 1 if successful or -1 on error
 */
int libtableau_values_table_set_identifier(
     libtableau_values_table_t *values_table,
     int value_index,
     const char *string,
     size_t string_length,
     libcerror_error_t **error )
{
	static char *function = "libtableau_values_table_set_identifier";

	if( values_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid values table.",
		 function );

		return( -1 );
	}
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
	if( ( string_length == 0 )
	 || ( string_length > (size_t) ( MEMORY_MAXIMUM_ALLOCATION_SIZE - 1 ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid string length value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( value_index < 0 )
	 || ( value_index >= values_table->number_of_values ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid value index value out of bounds.",
		 function );

		return( -1 );
	}
	if( values_table->identifiers[ value_index ] != NULL )
	{
		memory_free(
		 values_table->identifiers[ value_index ] );

		values_table->identifiers[ value_index ] = NULL;
	}
	values_table->identifiers[ value_index ] = (char *) memory_allocate(
	                                                     sizeof( char ) * ( string_length + 1 ) );

	if( values_table->identifiers[ value_index ] == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create identifier: %d.",
		 function,
		 value_index );

		goto on_error;
	}
	if( narrow_string_copy(
	     values_table->identifiers[ value_index ],
	     string,
	     string_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: %d.",
		 function,
		 value_index );

		goto on_error;
	}
	( values_table->identifiers[ value_index ] )[ string_length ] = 0;

	return( 1 );

on_error:
	if( values_table->identifiers[ value_index ] != NULL )
	{
		memory_free(
		 values_table->identifiers[ value_index ] );

		values_table->identifiers[ value_index ] = NULL;
	}
	return( -1 );
}

/* Retrieves a value in the values table
 * The string size should include the end of string character
 * Returns 1 if successful, 0 if not set or -1 on error
 */
int libtableau_values_table_get_value_by_identifier(
     libtableau_values_table_t *values_table,
     const char *identifier,
     size_t identifier_length,
     char *string,
     size_t string_size,
     libcerror_error_t **error )
{
	static char *function = "libtableau_values_table_get_value_by_identifier";
	size_t value_length   = 0;
	int value_index       = 0;

	if( values_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid values table.",
		 function );

		return( -1 );
	}
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
	if( ( string_size == 0 )
	 || ( string_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid string size value out of bounds.",
		 function );

		return( -1 );
	}
	value_index = libtableau_values_table_get_index(
	               values_table,
	               identifier,
	               identifier_length,
	               error );

	if( value_index <= -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to find value index for identifier: %s.",
		 function,
		 identifier );

		return( -1 );
	}
	if( value_index >= values_table->number_of_values )
	{
		return( 0 );
	}
	if( values_table->values[ value_index ] == NULL )
	{
		return( 0 );
	}
	value_length = narrow_string_length(
	                values_table->values[ value_index ] );

	/* Do not bother with empty values
	 */
	if( value_length == 0 )
	{
		return( 0 );
	}
	if( value_length > ( string_size - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: value too small.",
		 function );

		return( -1 );
	}
	if( narrow_string_copy(
	     string,
	     values_table->values[ value_index ],
	     value_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value: %d.",
		 function,
		 value_index );

		return( -1 );
	}
	string[ value_length ] = 0;

	return( 1 );
}

/* Set a value in the values table
 * Frees an existing value if necessary
 * Returns 1 if successful or -1 on error
 */
int libtableau_values_table_set_value(
     libtableau_values_table_t *values_table,
     const char *identifier,
     size_t identifier_length,
     char *string,
     size_t string_length,
     libcerror_error_t **error )
{
	static char *function = "libtableau_values_table_set_value";
	int value_index       = 0;

	if( values_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid values table.",
		 function );

		return( -1 );
	}
	value_index = libtableau_values_table_get_index(
	               values_table,
	               identifier,
	               identifier_length,
	               error );

	if( value_index < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to find value index for identifier: %s.",
		 function,
		 identifier );

		return( -1 );
	}
	if( value_index >= values_table->number_of_values )
	{
		if( libtableau_values_table_resize(
		     values_table,
		     value_index + 1,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to resize values table.",
			 function );

			goto on_error;
		}
		if( libtableau_values_table_set_identifier(
		     values_table,
		     value_index,
		     identifier,
		     identifier_length,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set identifier: %d.",
			 function,
			 value_index );

			goto on_error;
		}
	}
	if( values_table->values[ value_index ] != NULL )
	{
		memory_free(
		 values_table->values[ value_index ] );

		values_table->values[ value_index ] = NULL;
	}
	/* Do not bother with empty values
	 */
	if( ( string == NULL )
	 || ( string_length == 0 ) )
	{
		return( 1 );
	}
	if( string_length > (size_t) ( MEMORY_MAXIMUM_ALLOCATION_SIZE - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string length value exceeds maximum.",
		 function );

		goto on_error;
	}
	values_table->values[ value_index ] = (char *) memory_allocate(
	                                                sizeof( char ) * ( string_length + 1 ) );

	if( values_table->values[ value_index ] == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create value: %d.",
		 function,
		 value_index );

		goto on_error;
	}
	if( narrow_string_copy(
	     values_table->values[ value_index ],
	     string,
	     string_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value: %d.",
		 function,
		 value_index );

		goto on_error;
	}
	( values_table->values[ value_index ] )[ string_length ] = 0;

	return( 1 );

on_error:
	if( values_table->values[ value_index ] != NULL )
	{
		memory_free(
		 values_table->values[ value_index ] );

		values_table->values[ value_index ] = NULL;
	}
	return( -1 );
}

