/*
 * Tableau bridge values
 *
 * Copyright (C) 2008-2022, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( HAVE_STRING_H ) || defined( WINAPI )
#include <string.h>
#endif

#include "libtableau_libcerror.h"
#include "libtableau_values.h"
#include "libtableau_values_table.h"

/* Initializes the values
 * Returns 1 if successful, or -1 otherwise
 */
int libtableau_values_initialize(
     libtableau_values_table_t *values_table,
     libcerror_error_t **error )
{
	static char *function = "libtableau_values_initialize";

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
	if( libtableau_values_table_set_identifier(
	     values_table,
	     0,
	     "bridge_firmware_stepping",
	     24,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 0.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     1,
	     "bridge_channel_index",
	     20,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 1.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     2,
	     "bridge_channel_type",
	     19,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 2.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     3,
	     "bridge_debug_firmware",
	     21,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 3.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     4,
	     "bridge_mode_read_only",
	     21,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 4.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     5,
	     "bridge_report_read_only",
	     23,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 5.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     6,
	     "bridge_report_write_error",
	     25,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 6.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     7,
	     "bridge_serial_number",
	     20,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 7.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     8,
	     "bridge_vendor",
	     13,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 8.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     9,
	     "bridge_model",
	     12,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 9.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     10,
	     "bridge_firmware_date",
	     20,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 10.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     11,
	     "bridge_firmware_time",
	     20,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 11.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     12,
	     "drive_vendor",
	     12,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 12.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     13,
	     "drive_model",
	     11,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 13.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     14,
	     "drive_serial_number",
	     19,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 14.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     15,
	     "drive_revision_number",
	     21,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 15.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     16,
	     "drive_hpa_support",
	     17,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 16.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     17,
	     "drive_hpa_in_use",
	     16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 17.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     18,
	     "drive_dco_support",
	     17,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 18.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     19,
	     "drive_dco_in_use",
	     16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 19.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     20,
	     "drive_security_support",
	     22,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 20.",
		 function );

		return( -1 );
	}
	if( libtableau_values_table_set_identifier(
	     values_table,
	     21,
	     "drive_security_in_use",
	     21,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set identifier: 21.",
		 function );

		return( -1 );
	}
	return( 1 );
}

