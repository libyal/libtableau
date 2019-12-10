/*
 * Common input functions for the tableau tools
 *
 * Copyright (C) 2008-2019, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _TABLEAUTOOLS_INPUT_H )
#define _TABLEAUTOOLS_INPUT_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "tableautools_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern system_character_t *tableautools_input_yes_no[ 2 ];

int tableautools_input_determine_yes_no(
     const system_character_t *string,
     uint8_t *yes_no_value,
     libcerror_error_t **error );

int tableautools_input_get_fixed_string_variable(
     FILE *stream,
     system_character_t *input_buffer,
     size_t input_buffer_size,
     const system_character_t *request_string,
     system_character_t **values,
     uint8_t number_of_values,
     uint8_t default_value,
     system_character_t **fixed_string_variable,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _TABLEAUTOOLS_INPUT_H ) */

