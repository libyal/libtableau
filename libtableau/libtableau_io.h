/*
 * Input/Output (IO) functions
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

#if !defined( _LIBTABLEAU_IO_H )
#define _LIBTABLEAU_IO_H

#include <common.h>
#include <types.h>

#include "libtableau_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libtableau_io_send_command(
     int file_descriptor,
     uint8_t *command,
     size_t size_command,
     uint8_t *response,
     size_t size_response,
     uint8_t *sense,
     size_t size_sense,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBTABLEAU_IO_H ) */

