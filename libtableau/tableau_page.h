/*
 * Tableau page
 *
 * Copyright (C) 2008-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _TABLEAU_PAGE_H )
#define _TABLEAU_PAGE_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#define TABLEAU_PAGE_IDENTIFIER_HPA_DCO		(uint8_t) 0x00

typedef struct tableau_page tableau_page_t;

struct tableau_page
{
	/* The page identifier
	 * Consists of 1 byte
	 */
	uint8_t identifier;

	/* The page size
	 * Consists of 1 byte
	 */
	uint8_t size;

	/* The page data for the identifier
	 */
};

/* For the HPA/DCO page data the page header contains:
 * identifier : 0x00
 * size       : 0x20
 */

#define TABLEAU_PAGE_DATA_HPA_DCO_FLAG_SECURITY_IN_USE		(uint8_t) 0x20
#define TABLEAU_PAGE_DATA_HPA_DCO_FLAG_SECURITY_SUPPORT		(uint8_t) 0x10
#define TABLEAU_PAGE_DATA_HPA_DCO_FLAG_DCO_IN_USE		(uint8_t) 0x08
#define TABLEAU_PAGE_DATA_HPA_DCO_FLAG_DCO_SUPPORT		(uint8_t) 0x04
#define TABLEAU_PAGE_DATA_HPA_DCO_FLAG_HPA_IN_USE		(uint8_t) 0x02
#define TABLEAU_PAGE_DATA_HPA_DCO_FLAG_HPA_SUPPORT		(uint8_t) 0x01

typedef struct tableau_page_data_hpa_dco tableau_page_data_hpa_dco_t;

struct tableau_page_data_hpa_dco
{
	/* The flags
	 * Consists of:
	 * - 0x80 unknown
	 * - 0x40 unknown
	 * - 0x20 security in use
	 * - 0x10 security support
	 * - 0x08 DCO in use
	 * - 0x04 DCO support
	 * - 0x02 HPA in use
	 * - 0x01 HPA support
	 */
	uint8_t flags;

	/* Error code
	 * Consists of:
	 * - 0xf0
	 * - 0x0f HPA disable error code (lower 4 bits)
	 */
	uint8_t error_code;

	/* Unknown
	 */
	uint8_t unknown1[ 4 ];

	/* Drive number of sectors
	 * Consists of 4 bytes in big endian
	 */
	uint8_t drive_number_of_sectors[ 4 ];

	/* Unknown
	 */
	uint8_t unknown2[ 4 ];

	/* HPA number of sectors
	 * Consists of 4 bytes in big endian
	 */
	uint8_t hpa_number_of_sectors[ 4 ];

	/* Unknown
	 */
	uint8_t unknown3[ 4 ];

	/* DCO number of sectors
	 * Consists of 4 bytes in big endian
	 */
	uint8_t dco_number_of_sectors[ 4 ];

	/* DCO challenge key
	 * Required to remove DCO
	 * Consists of 4 bytes
	 */
	uint8_t dco_challenge_key[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _TABLEAU_PAGE_H ) */

