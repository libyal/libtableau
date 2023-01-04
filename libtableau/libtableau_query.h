/*
 * Query functions
 *
 * Copyright (C) 2008-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBTABLEAU_QUERY_H )
#define _LIBTABLEAU_QUERY_H

#include <common.h>
#include <types.h>

#include "libtableau_libcerror.h"
#include "libtableau_security_values.h"
#include "libtableau_values_table.h"

#include "tableau_header.h"
#include "tableau_page.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libtableau_query_parse_tableau_header(
     tableau_header_t *tableau_header,
     libtableau_values_table_t *values_table,
     libcerror_error_t **error );

int libtableau_query_parse_tableau_page(
     tableau_page_t *tableau_page,
     const uint8_t *tableau_page_data,
     libtableau_values_table_t *values_table,
     libtableau_security_values_t *security_values,
     libcerror_error_t **error );

int libtableau_query_parse_tableau_page_data_hpa_dco(
     tableau_page_data_hpa_dco_t *tableau_page_data_hpa_dco,
     libtableau_values_table_t *values_table,
     libtableau_security_values_t *security_values,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBTABLEAU_QUERY_H ) */

