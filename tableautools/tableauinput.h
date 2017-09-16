/*
 * Common input functions for the tableau tools
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

#if !defined( _TABLEAUINPUT_H )
#define _TABLEAUINPUT_H

#include <common.h>
#include <character_string.h>

#if defined( __cplusplus )
extern "C" {
#endif

extern character_t *tableauinput_yes_no[ 2 ];

int tableauinput_determine_yes_no(
     const character_t *argument );

character_t *tableauinput_get_fixed_value(
              FILE *stream,
              character_t *request_string,
              character_t **values,
              int amount,
              int default_value );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _TABLEAUINPUT_H ) */

