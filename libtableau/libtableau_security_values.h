/*
 * Security values functions
 *
 * Copyright (C) 2008-2019, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBTABLEAU_SECURITY_VALUES_H )
#define _LIBTABLEAU_SECURITY_VALUES_H

#include <common.h>
#include <types.h>

#include "libtableau_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libtableau_security_values libtableau_security_values_t;

struct libtableau_security_values
{
	/* The number of sectors of the drive
	 */
	uint32_t drive_number_of_sectors;

	/* The number of sectors of the HPA
	 */
	uint32_t hpa_number_of_sectors;

	/* The number of sectors of the DCO
	 */
	uint32_t dco_number_of_sectors;

	/* Value to indicate if the security support has been detected
	 */
	uint8_t security_support;

	/* Value to indicate if the security is in use
	 */
	uint8_t security_in_use;

	/* Value to indicate if the HPA support has been detected
	 */
	uint8_t hpa_support;

	/* Value to indicate if the HPA is in use
	 */
	uint8_t hpa_in_use;

	/* Value to indicate if the DCO support has been detected
	 */
	uint8_t dco_support;

	/* Value to indicate if the DCO is in use
	 */
	uint8_t dco_in_use;

	/* The DCO challenge key necessary for DCO removal
	 */
	uint8_t dco_challenge_key[ 4 ];
};

int libtableau_security_values_initialize(
     libtableau_security_values_t **security_values,
     libcerror_error_t **error );

int libtableau_security_values_free(
     libtableau_security_values_t **security_values,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBTABLEAU_SECURITY_VALUES_H ) */

