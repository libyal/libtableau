/*
 * Query functions
 *
 * Copyright (C) 2008-2021, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include <libtableau/definitions.h>

#include "libtableau_definitions.h"
#include "libtableau_handle.h"
#include "libtableau_io.h"
#include "libtableau_libcerror.h"
#include "libtableau_libcnotify.h"
#include "libtableau_query.h"
#include "libtableau_security_values.h"
#include "libtableau_string.h"
#include "libtableau_values_table.h"

#include "tableau_query.h"

/* Parse the tableau header
 * Returns 1 if successful or -1 on error
 */
int libtableau_query_parse_tableau_header(
     tableau_header_t *tableau_header,
     libtableau_values_table_t *values_table,
     libcerror_error_t **error )
{
	uint8_t value_string[ 32 ];

	const char *bridge_channel_type   = "Unknown";
	static char *function             = "libtableau_query_parse_tableau_header";
	char *true_false_string           = NULL;
	size_t bridge_channel_type_length = 0;
	size_t true_false_string_length   = 0;
	ssize_t value_string_length       = 0;
	uint8_t digit                     = 0;
	int value_iterator                = 0;
	int value_string_iterator         = 0;

	if( tableau_header == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid tableau header.",
		 function );

		return( -1 );
	}
	if( values_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid values table.",
		 function );

		return( -1 );
	}
	if( tableau_header->response_size < (uint8_t) sizeof( tableau_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: unsupported tableau header size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: Tableau header:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) tableau_header,
		 sizeof( tableau_header_t ),
		 0 );
	}
#endif
	if( ( tableau_header->signature[ 0 ] != 0x0e )
	 || ( tableau_header->signature[ 1 ] != 0xcc ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported tableau header signature: 0x%02x 0x%02x.",
		 function,
		 tableau_header->signature[ 0 ],
		 tableau_header->signature[ 1 ] );

		return( -1 );
	}
	/* Bridge firmware stepping
	 */
	value_string_iterator = 0;

	digit = tableau_header->firmware_stepping;

	if( digit >= 100 )
	{
		value_string[ value_string_iterator++ ] = (uint8_t) '0' + (uint8_t) ( digit / 10 );

		digit %= 100;
	}
	if( digit >= 10 )
	{
		value_string[ value_string_iterator++ ] = (uint8_t) '0' + (uint8_t) ( digit / 10 );

		digit %= 10;
	}
	value_string[ value_string_iterator++ ] = (uint8_t) '0' + (uint8_t) digit;
	value_string[ value_string_iterator ]   = (uint8_t) '\0';

	if( libtableau_values_table_set_value(
	     values_table,
	     "bridge_firmware_stepping",
	     24,
	     (char *) value_string,
	     value_string_iterator,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set bridge firmware stepping value.",
		 function );

		return( -1 );
	}
	/* Bridge channel index
	 */
	value_string_iterator = 0;

	digit = ( tableau_header->channel_data >> 4 ) & 0x0f;

	if( digit >= 10 )
	{
		value_string[ value_string_iterator++ ] = (uint8_t) '0' + (uint8_t) ( digit / 10 );

		digit %= 10;
	}
	value_string[ value_string_iterator++ ] = (uint8_t) '0' + (uint8_t) digit;
	value_string[ value_string_iterator ]   = (uint8_t) '\0';

	if( libtableau_values_table_set_value(
	     values_table,
	     "bridge_channel_index",
	     20,
	     (char *) value_string,
	     value_string_iterator,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set bridge channel index value.",
		 function );

		return( -1 );
	}
	/* Bridge channel type
	 */
	if( ( tableau_header->channel_data & 0xf ) == TABLEAU_HEADER_CHANNEL_TYPE_PATA )
	{
		bridge_channel_type        = "PATA";
		bridge_channel_type_length = 4;
	}
	else if( ( tableau_header->channel_data & 0xf ) == TABLEAU_HEADER_CHANNEL_TYPE_SATA )
	{
		bridge_channel_type        = "SATA";
		bridge_channel_type_length = 4;
	}
	else if( ( tableau_header->channel_data & 0xf ) == TABLEAU_HEADER_CHANNEL_TYPE_SCSI )
	{
		bridge_channel_type        = "SCSI";
		bridge_channel_type_length = 4;
	}
	else if( ( tableau_header->channel_data & 0xf ) == TABLEAU_HEADER_CHANNEL_TYPE_USB )
	{
		bridge_channel_type        = "USB";
		bridge_channel_type_length = 3;
	}
	if( libtableau_values_table_set_value(
	     values_table,
	     "bridge_channel_type",
	     19,
	     (char *) bridge_channel_type,
	     bridge_channel_type_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set bridge channel type value.",
		 function );

		return( -1 );
	}
	/* Bridge debug firmware
	 */
	if( ( tableau_header->flags & TABLEAU_HEADER_FLAG_DEBUG_FIRMWARE ) != 0 )
	{
		true_false_string        = "true";
		true_false_string_length = 4;
	}
	else
	{
		true_false_string        = "false";
		true_false_string_length = 5;
	}
	if( libtableau_values_table_set_value(
	     values_table,
	     "bridge_debug_firmware",
	     21,
	     true_false_string,
	     true_false_string_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set bridge debug firmware value.",
		 function );

		return( -1 );
	}
	/* Bridge read only mode
	 */
	if( ( tableau_header->flags & TABLEAU_HEADER_FLAG_WRITE_PERMITTED ) != 0 )
	{
		true_false_string        = "false";
		true_false_string_length = 5;
	}
	else
	{
		true_false_string        = "true";
		true_false_string_length = 4;
	}
	if( libtableau_values_table_set_value(
	     values_table,
	     "bridge_mode_read_only",
	     21,
	     true_false_string,
	     true_false_string_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set bridge read only mode value.",
		 function );

		return( -1 );
	}
	/* Bridge read only reporting
	 */
	if( ( tableau_header->flags & TABLEAU_HEADER_FLAG_WRITE_BLOCKED_REPORTING ) != 0 )
	{
		true_false_string        = "true";
		true_false_string_length = 4;
	}
	else
	{
		true_false_string        = "false";
		true_false_string_length = 5;
	}
	if( libtableau_values_table_set_value(
	     values_table,
	     "bridge_report_read_only",
	     23,
	     true_false_string,
	     true_false_string_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set bridge read only report value.",
		 function );

		return( -1 );
	}
	/* Bridge write error reporting
	 */
	if( ( tableau_header->flags & TABLEAU_HEADER_FLAG_WRITE_ERROR_REPORTING ) != 0 )
	{
		true_false_string        = "true";
		true_false_string_length = 4;
	}
	else
	{
		true_false_string        = "false";
		true_false_string_length = 5;
	}
	if( libtableau_values_table_set_value(
	     values_table,
	     "bridge_report_write_error",
	     25,
	     true_false_string,
	     true_false_string_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set bridge write error report value.",
		 function );

		return( -1 );
	}
	/* Bride serial number
	 */
	value_string_iterator = 0;

	for( value_iterator = 0; value_iterator < 8; value_iterator++ )
	{
		digit = ( tableau_header->bridge_serial_number[ value_iterator ] >> 4 ) & 0x0f;

		if( digit <= 9 )
		{
			value_string[ value_string_iterator++ ] = (uint8_t) '0' + (uint8_t) digit;
		}
		else
		{
			value_string[ value_string_iterator++ ] = (uint8_t) 'a' + (uint8_t) ( digit - 10 );
		}
		digit = tableau_header->bridge_serial_number[ value_iterator ] & 0x0f;

		if( digit <= 9 )
		{
			value_string[ value_string_iterator++ ] = (uint8_t) '0' + (uint8_t) digit;
		}
		else
		{
			value_string[ value_string_iterator++ ] = (uint8_t) 'a' + (uint8_t) ( digit - 10 );
		}
	}
	value_string[ value_string_iterator ] = (uint8_t) '\0';

	if( libtableau_values_table_set_value(
	     values_table,
	     "bridge_serial_number",
	     20,
	     (char *) value_string,
	     value_string_iterator,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set bridge serial number value.",
		 function );

		return( -1 );
	}
	/* Bride vendor
	 */
	value_string_length = libtableau_string_trim_copy(
	                       value_string,
	                       tableau_header->bridge_vendor,
	                       8,
	                       error );

	if( value_string_length < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to trim bridge vendor value.",
		 function );

		return( -1 );
	}
	else if( libtableau_values_table_set_value(
	          values_table,
	          "bridge_vendor",
	          13,
	          (char *) value_string,
	          value_string_length,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set bridge vendor value.",
		 function );

		return( -1 );
	}
	/* Bride model
	 */
	value_string_length = libtableau_string_trim_copy(
	                       value_string,
	                       tableau_header->bridge_model,
	                       8,
	                       error );

	if( value_string_length < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to trim bridge model value.",
		 function );

		return( -1 );
	}
	else if( libtableau_values_table_set_value(
	          values_table,
	          "bridge_model",
	          12,
	          (char *) value_string,
	          value_string_length,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set bridge model value.",
		 function );

		return( -1 );
	}
	/* Bride firmware date
	 */
	value_string_length = libtableau_string_trim_copy(
	                       value_string,
	                       tableau_header->bridge_firmware_date,
	                       12,
	                       error );

	if( value_string_length < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to trim bridge firmware date value.",
		 function );

		return( -1 );
	}
	else if( libtableau_values_table_set_value(
	          values_table,
	          "bridge_firmware_date",
	          20,
	          (char *) value_string,
	          value_string_length,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set bridge firmware date value.",
		 function );

		return( -1 );
	}
	/* Bride firmware time
	 */
	value_string_length = libtableau_string_trim_copy(
	                       value_string,
	                       tableau_header->bridge_firmware_time,
	                       12,
	                       error );

	if( value_string_length < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to trim bridge firmware time value.",
		 function );

		return( -1 );
	}
	else if( libtableau_values_table_set_value(
	          values_table,
	          "bridge_firmware_time",
	          20,
	          (char *) value_string,
	          value_string_length,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set bridge firmware time value.",
		 function );

		return( -1 );
	}
	/* Drive vendor
	 */
	value_string_length = libtableau_string_trim_copy(
	                       value_string,
	                       tableau_header->drive_vendor,
	                       8,
	                       error );

	if( value_string_length < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to trim drive vendor value.",
		 function );

		return( -1 );
	}
	else if( libtableau_values_table_set_value(
	          values_table,
	          "drive_vendor",
	          12,
	          (char *) value_string,
	          value_string_length,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set drive vendor value.",
		 function );

		return( -1 );
	}
	/* Drive model
	 */
	value_string_length = libtableau_string_trim_copy(
	                       value_string,
	                       tableau_header->drive_model,
	                       28,
	                       error );

	if( value_string_length < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to trim drive model value.",
		 function );

		return( -1 );
	}
	else if( libtableau_values_table_set_value(
	          values_table,
	          "drive_model",
	          11,
	          (char *) value_string,
	          value_string_length,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set drive model value.",
		 function );

		return( -1 );
	}
	/* Drive serial number
	 */
	value_string_length = libtableau_string_trim_copy(
	                       value_string,
	                       tableau_header->drive_serial_number,
	                       20,
	                       error );

	if( value_string_length < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to trim drive serial number value.",
		 function );

		return( -1 );
	}
	else if( libtableau_values_table_set_value(
	          values_table,
	          "drive_serial_number",
	          19,
	          (char *) value_string,
	          value_string_length,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set drive serial number value.",
		 function );

		return( -1 );
	}
	/* Drive revision number
	 */
	value_string_length = libtableau_string_trim_copy(
	                       value_string,
	                       tableau_header->drive_revision_number,
	                       20,
	                       error );

	if( value_string_length < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to trim drive revision number value.",
		 function );

		return( -1 );
	}
	else if( libtableau_values_table_set_value(
	          values_table,
	          "drive_revision_number",
	          21,
	          (char *) value_string,
	          value_string_length,
	          error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set drive revision number value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Parse the tableau page
 * Returns 1 if successful or -1 on error
 */
int libtableau_query_parse_tableau_page(
     tableau_page_t *tableau_page,
     const uint8_t *tableau_page_data,
     libtableau_values_table_t *values_table,
     libtableau_security_values_t *security_values,
     libcerror_error_t **error )
{
	static char *function = "libtableau_query_parse_tableau_page";

	if( tableau_page == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid tableau page.",
		 function );

		return( -1 );
	}
	if( tableau_page_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid tableau page data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: Tableau page header:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) tableau_page,
		 sizeof( tableau_page_t ),
		 0 );

		libcnotify_printf(
		 "%s: Tableau page data:\n",
		 function );
		libcnotify_print_data(
		 tableau_page_data,
		 tableau_page->size,
		 0 );
	}
#endif
	if( tableau_page->identifier == TABLEAU_PAGE_IDENTIFIER_HPA_DCO )
	{
		if( tableau_page->size != (uint8_t) ( sizeof( tableau_page_t ) + sizeof( tableau_page_data_hpa_dco_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported tableau HPA/DCO page size.",
			 function );

			return( -1 );
		}
		if( libtableau_query_parse_tableau_page_data_hpa_dco(
		     (tableau_page_data_hpa_dco_t *) tableau_page_data,
		     values_table,
		     security_values,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GENERIC,
			 "%s: unable to parse tableau HPA/DCO page data.",
			 function );

			return( -1 );
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	else if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: unsupported tableau page identifier: 0x%02x.\n",
		 function,
		 tableau_page->identifier );
	}
#endif
	return( 1 );
}

/* Parse the tableau HPA/DCO page data
 * Returns 1 if successful or -1 on error
 */
int libtableau_query_parse_tableau_page_data_hpa_dco(
     tableau_page_data_hpa_dco_t *tableau_page_data_hpa_dco,
     libtableau_values_table_t *values_table,
     libtableau_security_values_t *security_values,
     libcerror_error_t **error )
{
	static char *function           = "libtableau_query_parse_tableau_page_data_hpa_dco";
	char *true_false_string         = NULL;
	size_t true_false_string_length = 0;

	if( tableau_page_data_hpa_dco == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid tableau page data.",
		 function );

		return( -1 );
	}
	if( values_table == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid values table.",
		 function );

		return( -1 );
	}
	if( security_values == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid security values.",
		 function );

		return( -1 );
	}
	if( ( tableau_page_data_hpa_dco->flags & TABLEAU_PAGE_DATA_HPA_DCO_FLAG_HPA_SUPPORT ) != 0 )
	{
		security_values->hpa_support = 1;
	}
	if( ( tableau_page_data_hpa_dco->flags & TABLEAU_PAGE_DATA_HPA_DCO_FLAG_HPA_IN_USE ) != 0 )
	{
		security_values->hpa_in_use = 1;
	}
	if( ( tableau_page_data_hpa_dco->flags & TABLEAU_PAGE_DATA_HPA_DCO_FLAG_DCO_SUPPORT ) != 0 )
	{
		security_values->dco_support = 1;
	}
	if( ( tableau_page_data_hpa_dco->flags & TABLEAU_PAGE_DATA_HPA_DCO_FLAG_DCO_IN_USE ) != 0 )
	{
		security_values->dco_in_use = 1;
	}
	if( ( tableau_page_data_hpa_dco->flags & TABLEAU_PAGE_DATA_HPA_DCO_FLAG_SECURITY_SUPPORT ) != 0 )
	{
		security_values->security_support = 1;
	}
	if( ( tableau_page_data_hpa_dco->flags & TABLEAU_PAGE_DATA_HPA_DCO_FLAG_SECURITY_IN_USE ) != 0 )
	{
		security_values->security_in_use = 1;
	}
	byte_stream_copy_to_uint32_big_endian(
	 tableau_page_data_hpa_dco->drive_number_of_sectors,
	 security_values->drive_number_of_sectors );

	byte_stream_copy_to_uint32_big_endian(
	 tableau_page_data_hpa_dco->hpa_number_of_sectors,
	 security_values->hpa_number_of_sectors );

	byte_stream_copy_to_uint32_big_endian(
	 tableau_page_data_hpa_dco->dco_number_of_sectors,
	 security_values->dco_number_of_sectors );

	if( memory_copy(
	     security_values->dco_challenge_key,
	     tableau_page_data_hpa_dco->dco_challenge_key,
	     4 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy DCO challenge key.",
		 function );

		return( -1 );
	}
	/* HPA support
	 */
	if( security_values->hpa_support != 0 )
	{
		true_false_string        = "true";
		true_false_string_length = 4;
	}
	else
	{
		true_false_string        = "false";
		true_false_string_length = 5;
	}
	if( libtableau_values_table_set_value(
	     values_table,
	     "drive_hpa_support",
	     17,
	     true_false_string,
	     true_false_string_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set drive hpa support value.",
		 function );

		return( -1 );
	}
	/* HPA in use
	 */
	if( security_values->hpa_in_use != 0 )
	{
		true_false_string        = "true";
		true_false_string_length = 4;
	}
	else
	{
		true_false_string        = "false";
		true_false_string_length = 5;
	}
	if( libtableau_values_table_set_value(
	     values_table,
	     "drive_hpa_in_use",
	     16,
	     true_false_string,
	     true_false_string_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set drive hpa in use value.",
		 function );

		return( -1 );
	}
	/* DCO support
	 */
	if( security_values->dco_support != 0 )
	{
		true_false_string        = "true";
		true_false_string_length = 4;
	}
	else
	{
		true_false_string        = "false";
		true_false_string_length = 5;
	}
	if( libtableau_values_table_set_value(
	     values_table,
	     "drive_dco_support",
	     17,
	     true_false_string,
	     true_false_string_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set drive dco support value.",
		 function );

		return( -1 );
	}
	/* DCO in use
	 */
	if( security_values->dco_in_use != 0 )
	{
		true_false_string        = "true";
		true_false_string_length = 4;
	}
	else
	{
		true_false_string        = "false";
		true_false_string_length = 5;
	}
	if( libtableau_values_table_set_value(
	     values_table,
	     "drive_dco_in_use",
	     16,
	     true_false_string,
	     true_false_string_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set drive dco in use value.",
		 function );

		return( -1 );
	}
	/* Security support
	 */
	if( security_values->security_support != 0 )
	{
		true_false_string        = "true";
		true_false_string_length = 4;
	}
	else
	{
		true_false_string        = "false";
		true_false_string_length = 5;
	}
	if( libtableau_values_table_set_value(
	     values_table,
	     "drive_security_support",
	     22,
	     true_false_string,
	     true_false_string_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set drive security support value.",
		 function );

		return( -1 );
	}
	/* Security in use
	 */
	if( security_values->security_in_use != 0 )
	{
		true_false_string        = "true";
		true_false_string_length = 4;
	}
	else
	{
		true_false_string        = "false";
		true_false_string_length = 5;
	}
	if( libtableau_values_table_set_value(
	     values_table,
	     "drive_security_in_use",
	     21,
	     true_false_string,
	     true_false_string_length,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set drive security in use value.",
		 function );

		return( -1 );
	}
	return( 1 );
}

