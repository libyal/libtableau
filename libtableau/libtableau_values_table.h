/*
 * Values table
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

#if !defined( _LIBTABLEAU_VALUES_TABLE_H )
#define _LIBTABLEAU_VALUES_TABLE_H

#include <common.h>
#include <types.h>

#include "libtableau_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libtableau_values_table libtableau_values_table_t;

struct libtableau_values_table
{
	/* The number of values
	 */
	int number_of_values;

	/* The value identifiers
	 */
	char **identifiers;

	/* The values
	 */
	char **values;
};

int libtableau_values_table_initialize(
     libtableau_values_table_t **values_table,
     int number_of_values,
     libcerror_error_t **error );

int libtableau_values_table_free(
     libtableau_values_table_t **values_table,
     libcerror_error_t **error );

/* TODO: refactor to resize */
int libtableau_values_table_realloc(
     libtableau_values_table_t *values_table,
     int previous_number_of_values,
     int new_number_of_values,
     libcerror_error_t **error );

int libtableau_values_table_get_index(
     libtableau_values_table_t *values_table,
     const char *identifier,
     libcerror_error_t **error );

int libtableau_values_table_get_identifier(
     libtableau_values_table_t *values_table,
     int value_index,
     char *identifier,
     size_t length,
     libcerror_error_t **error );

int libtableau_values_table_get_value(
     libtableau_values_table_t *values_table,
     const char *identifier,
     char *value,
     size_t length,
     libcerror_error_t **error );

int libtableau_values_table_set_value(
     libtableau_values_table_t *values_table,
     const char *identifier,
     char *value,
     size_t length,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBTABLEAU_VALUES_TABLE_H ) */

