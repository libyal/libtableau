/*
 * Tableau SCSI query
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

#if !defined( _TABLEAU_QUERY_H )
#define _TABLEAU_QUERY_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#define TABLEAU_QUERY_SCSI_OPCODE		(uint8_t) 0xec

#define TABLEAU_QUERY_SUBCOMMAND_QUERY		(uint8_t) 0x00
#define TABLEAU_QUERY_SUBCOMMAND_REMOVE_DCO	(uint8_t) 0x01

/* When the subcommand query is issued only the first 6 bytes of the
 * tableau_query structure (CDB) are used.
 * When the subcommand remove dco is issued the full 12 bytes of the
 * tableau_query structure (CDB) are used.
 */

typedef struct tableau_query tableau_query_t;

struct tableau_query
{
	/* The operation code (opcode)
	 * Consists of 1 byte and should be 0xec
	 */
	uint8_t opcode;

	/* Unknown
	 * Consists of 1 byte which is 0
	 */
	uint8_t unknown1;

	/* The subcommand
	 * Consists of 1 byte
	 */
	uint8_t subcommand;

	/* Maximum byte size of the response buffer
	 * Consists of 1 byte
	 * A query could fail if the response size < 4
	 */
	uint8_t response_size;

	/* Unknown
	 * Consists of 1 byte which is 0
	 */
	uint8_t unknown2;

	/* The DCO challenge key in big endian
	 * Consists of 4 bytes which should default to 0xff
	 */
	uint8_t dco_challenge_key[ 4 ];

	/* Unknown
	 * Consists of 3 bytes which are 0
	 */
	uint8_t unknown3[ 3 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _TABLEAU_QUERY_H ) */

