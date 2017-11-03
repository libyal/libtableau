/*
 * Tableau bridge values
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
	values_table->identifiers[ 0 ] = strndup(
	                                  "bridge_firmware_stepping",
	                                  24 );

	values_table->identifiers[ 1 ] = strndup(
	                                  "bridge_channel_index",
	                                  20 );

	values_table->identifiers[ 2 ] = strndup(
	                                  "bridge_channel_type",
	                                  19 );

	values_table->identifiers[ 3 ] = strndup(
	                                  "bridge_debug_firmware",
	                                  21 );

	values_table->identifiers[ 4 ] = strndup(
	                                  "bridge_mode_read_only",
	                                  21 );

	values_table->identifiers[ 5 ] = strndup(
	                                  "bridge_report_read_only",
	                                  23 );

	values_table->identifiers[ 6 ] = strndup(
	                                  "bridge_report_write_error",
	                                  25 );

	values_table->identifiers[ 7 ] = strndup(
	                                  "bridge_serial_number",
	                                  20 );

	values_table->identifiers[ 8 ] = strndup(
	                                  "bridge_vendor",
	                                  13 );

	values_table->identifiers[ 9 ] = strndup(
	                                  "bridge_model",
	                                  12 );

	values_table->identifiers[ 10 ] = strndup(
	                                   "bridge_firmware_date",
	                                   20 );

	values_table->identifiers[ 11 ] = strndup(
	                                   "bridge_firmware_time",
	                                   20 );

	values_table->identifiers[ 12 ] = strndup(
	                                   "drive_vendor",
	                                   12 );

	values_table->identifiers[ 13 ] = strndup(
	                                   "drive_model",
	                                   11 );

	values_table->identifiers[ 14 ] = strndup(
	                                   "drive_serial_number",
	                                   19 );

	values_table->identifiers[ 15 ] = strndup(
	                                   "drive_revision_number",
	                                   21 );

	values_table->identifiers[ 16 ] = strndup(
	                                   "drive_hpa_support",
	                                   17 );

	values_table->identifiers[ 17 ] = strndup(
	                                   "drive_hpa_in_use",
	                                   16 );

	values_table->identifiers[ 18 ] = strndup(
	                                   "drive_dco_support",
	                                   17 );

	values_table->identifiers[ 19 ] = strndup(
	                                   "drive_dco_in_use",
	                                   16 );

	values_table->identifiers[ 20 ] = strndup(
	                                   "drive_security_support",
	                                   22 );

	values_table->identifiers[ 21 ] = strndup(
	                                   "drive_security_in_use",
	                                   21 );

	return( 1 );
}

