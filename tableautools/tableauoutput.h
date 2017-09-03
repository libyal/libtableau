/*
 * Common output functions for the tableau tools
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

#if !defined( _TABLEAUOUTPUT_H )
#define _TABLEAUOUTPUT_H

#include <common.h>
#include <error_string.h>

#include <errno.h>

#include <stdio.h>

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_WIDE_SYSTEM_CHARACTER_T )
#define tableauoutput_strerror( error_number ) \
        error_string_wcserror( error_number )

#else
#define tableauoutput_strerror( error_number ) \
        error_string_strerror( error_number )

#endif

void tableauoutput_copyright_fprint(
      FILE *stream );

void tableauoutput_version_fprint(
      FILE *stream,
      const character_t *program );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _TABLEAUOUTPUT_H ) */

