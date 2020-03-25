/*
 * Tableau header
 *
 * Copyright (C) 2008-2020, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _TABLEAU_HEADER_H )
#define _TABLEAU_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

#define TABLEAU_HEADER_CHANNEL_TYPE_PATA		(uint8_t) 0x00
#define TABLEAU_HEADER_CHANNEL_TYPE_SATA		(uint8_t) 0x01
#define TABLEAU_HEADER_CHANNEL_TYPE_SCSI		(uint8_t) 0x02
#define TABLEAU_HEADER_CHANNEL_TYPE_USB			(uint8_t) 0x03

#define TABLEAU_HEADER_FLAG_WRITE_ERROR_REPORTING	(uint8_t) 0x08
#define TABLEAU_HEADER_FLAG_WRITE_BLOCKED_REPORTING	(uint8_t) 0x04
#define TABLEAU_HEADER_FLAG_WRITE_PERMITTED             (uint8_t) 0x02
#define TABLEAU_HEADER_FLAG_DEBUG_FIRMWARE              (uint8_t) 0x01

typedef struct tableau_header tableau_header_t;

struct tableau_header
{
	/* Unknown
	 * Consists of 1 byte
	 * Probably the header identifier
	 */
	uint8_t unknown1;

	/* The size of the response
	 * Consists of 1 byte
	 */
	uint8_t response_size;

	/* The response signature
	 * Consists of 2 bytes in big endian
	 * Should be 0x0e 0xcc for a valid response
	 */
	uint8_t signature[ 2 ];

	/* Unknown
	 * Consists of 1 byte
	 */
	uint8_t unknown2;

	/* Firmware stepping
	 * Consists of 1 byte
	 */
	uint8_t firmware_stepping;

	/* Channel data
	 * Consists of:
	 * - 0xf0 channel index (upper 4 bits)
	 * - 0x0f channel type (lower 4 bits)
	 */
	uint8_t channel_data;

	/* Flags
	 * Consists of:
	 * - 0x80 unknown
	 * - 0x40 unknown
	 * - 0x20 unknown
	 * - 0x10 unknown
	 * - 0x08 write error reporting disabled (0) or enabled (1)
	 * - 0x04 host informed about read only or write-blocking (0) or read/write (1) mode
	 * - 0x02 read only or write-blocking (0) or read/write or write-permitting (1) mode
	 * - 0x01 release (0) or debug (1) firmware
	 */
	uint8_t flags;

	/* The Tableau bridge serial number
	 * Consists of 8 bytes
	 * Format is binary
	 */
	uint8_t bridge_serial_number[ 8 ];

	/* The Tableau bridge vendor
	 * Consists of 8 bytes
	 * Format is a byte character string (ASCII)
	 */
	uint8_t bridge_vendor[ 8 ];

	/* The Tableau bridge model
	 * Consists of 8 bytes
	 * Format is a byte character string (ASCII)
	 */
	uint8_t bridge_model[ 8 ];

	/* The Tableau bridge firmware date
	 * Consists of 12 bytes
	 * Format is a byte character string (ASCII)
	 */
	uint8_t bridge_firmware_date[ 12 ];

	/* The Tableau bridge firmware time
	 * Consists of 12 bytes
	 * Format is a byte character string (ASCII)
	 */
	uint8_t bridge_firmware_time[ 12 ];

	/* The connected drive vendor
	 * Consists of 8 bytes
	 * Format is a byte character string (ASCII)
	 */
	uint8_t drive_vendor[ 8 ];

	/* The connected drive model
	 * Consists of 28 bytes
	 * Format is a byte character string (ASCII)
	 */
	uint8_t drive_model[ 28 ];

	/* The connected drive serial number
	 * Consists of 20 bytes
	 * Format is a byte character string (ASCII)
	 */
	uint8_t drive_serial_number[ 20 ];

	/* The connected drive revision number
	 * Consists of 8 bytes
	 * Format is a byte character string (ASCII)
	 */
	uint8_t drive_revision_number[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _TABLEAU_HEADER_H ) */

