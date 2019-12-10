/*
 * Error functions
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

#if !defined( _LIBTABLEAU_INTERNAL_ERROR_H )
#define _LIBTABLEAU_INTERNAL_ERROR_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if !defined( HAVE_LOCAL_LIBTABLEAU )
#include <libtableau/error.h>
#endif

#include "libtableau_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBTABLEAU )

LIBTABLEAU_EXTERN \
void libtableau_error_free(
      libtableau_error_t **error );

LIBTABLEAU_EXTERN \
int libtableau_error_fprint(
     libtableau_error_t *error,
     FILE *stream );

LIBTABLEAU_EXTERN \
int libtableau_error_sprint(
     libtableau_error_t *error,
     char *string,
     size_t size );

LIBTABLEAU_EXTERN \
int libtableau_error_backtrace_fprint(
     libtableau_error_t *error,
     FILE *stream );

LIBTABLEAU_EXTERN \
int libtableau_error_backtrace_sprint(
     libtableau_error_t *error,
     char *string,
     size_t size );

#endif /* !defined( HAVE_LOCAL_LIBTABLEAU ) */

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBTABLEAU_INTERNAL_ERROR_H ) */

