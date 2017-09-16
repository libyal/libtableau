/*
 * Handle functions
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

#if !defined( _LIBTABLEAU_INTERNAL_HANDLE_H )
#define _LIBTABLEAU_INTERNAL_HANDLE_H

#include <common.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "libtableau_extern.h"
#include "libtableau_libcerror.h"
#include "libtableau_security_values.h"
#include "libtableau_types.h"
#include "libtableau_values_table.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libtableau_internal_handle libtableau_internal_handle_t;

struct libtableau_internal_handle
{
	/* libsgutils file descriptor
	 */
	int file_descriptor;

	/* The device filename
	 */
	char *filename;

	/* Tableau values
	 */
	libtableau_values_table_t *tableau_values;

	/* Security values
	 */
	libtableau_security_values_t *security_values;
};

LIBTABLEAU_EXTERN \
int libtableau_handle_initialize(
     libtableau_handle_t **handle,
     libcerror_error_t **error );

LIBTABLEAU_EXTERN \
int libtableau_handle_free(
     libtableau_handle_t **handle,
     libcerror_error_t **error );

LIBTABLEAU_EXTERN \
int libtableau_handle_open(
     libtableau_handle_t *handle,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBTABLEAU_EXTERN \
int libtableau_handle_open_wide(
     libtableau_handle_t *handle,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBTABLEAU_EXTERN \
int libtableau_handle_close(
     libtableau_handle_t *handle,
     libcerror_error_t **error );

LIBTABLEAU_EXTERN \
int libtableau_handle_query(
     libtableau_handle_t *handle,
     libcerror_error_t **error );

LIBTABLEAU_EXTERN \
int libtableau_handle_get_drive_number_of_sectors(
     libtableau_handle_t *handle,
     uint32_t *number_of_sectors,
     libcerror_error_t **error );

LIBTABLEAU_EXTERN \
int libtableau_handle_get_hpa_number_of_sectors(
     libtableau_handle_t *handle,
     uint32_t *number_of_sectors,
     libcerror_error_t **error );

LIBTABLEAU_EXTERN \
int libtableau_handle_get_dco_number_of_sectors(
     libtableau_handle_t *handle,
     uint32_t *number_of_sectors,
     libcerror_error_t **error );

LIBTABLEAU_EXTERN \
int libtableau_handle_get_number_of_tableau_values(
     libtableau_handle_t *handle,
     uint32_t *number_of_values,
     libcerror_error_t **error );

LIBTABLEAU_EXTERN \
int libtableau_handle_get_tableau_value_identifier(
     libtableau_handle_t *handle,
     uint32_t index,
     char *value,
     size_t length,
     libcerror_error_t **error );

LIBTABLEAU_EXTERN \
int libtableau_handle_get_tableau_value(
     libtableau_handle_t *handle,
     const char *identifier,
     char *value,
     size_t length,
     libcerror_error_t **error );

LIBTABLEAU_EXTERN \
int libtableau_detected_dco(
     libtableau_handle_t *handle,
     libcerror_error_t **error );

LIBTABLEAU_EXTERN \
int libtableau_remove_dco(
     libtableau_handle_t *handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBTABLEAU_INTERNAL_HANDLE_H ) */

