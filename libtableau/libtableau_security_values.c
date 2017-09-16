/*
 * Security values functions
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

#include "libtableau_libcerror.h"
#include "libtableau_security_values.h"

/* Creates security values
 * Make sure the value security_values is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libtableau_security_values_initialize(
     libtableau_security_values_t **security_values,
     libcerror_error_t **error )
{
	static char *function = "libtableau_security_values_initialize";

	if( security_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid security values.",
		 function );

		return( -1 );
	}
	if( *security_values != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid security values value already set.",
		 function );

		return( -1 );
	}
	*security_values = memory_allocate_structure(
	                    libtableau_security_values_t );

	if( *security_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create security values.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *security_values,
	     0,
	     sizeof( libtableau_security_values_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear security values.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *security_values != NULL )
	{
		memory_free(
		 *security_values );

		*security_values = NULL;
	}
	return( -1 );
}

/* Frees security values
 * Returns 1 if successful or -1 on error
 */
int libtableau_security_values_free(
     libtableau_security_values_t **security_values,
     libcerror_error_t **error )
{
	static char *function = "libtableau_security_values_free";

	if( security_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid security values.",
		 function );

		return( -1 );
	}
	if( *security_values != NULL )
	{
		memory_free(
		 *security_values );

		*security_values = NULL;
	}
	return( 1 );
}

