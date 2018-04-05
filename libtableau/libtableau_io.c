/*
 * Input/Output (IO) functions
 *
 * Copyright (C) 2008-2018, Joachim Metz <joachim.metz@gmail.com>
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

#include <common.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_SYS_IOCTL_H )
#include <sys/ioctl.h>
#endif

#if defined( HAVE_SCSI_SG_PT_H )
#include <scsi/sg_pt.h>
#endif

#include "libtableau_io.h"
#include "libtableau_libcerror.h"
#include "libtableau_libcnotify.h"

#define LIBTABLEAU_IO_TIMEOUT_NUMBER_OF_SECONDS		5

/* Sends a Tableau IO command to the file descriptor
 * Returns 1 if successful or -1 on error
 */
int libtableau_io_send_command(
     int file_descriptor,
     uint8_t *command,
     size_t size_command,
     uint8_t *response,
     size_t size_response,
     uint8_t *sense,
     size_t size_sense,
     libcerror_error_t **error )
{
	static char *function = "libtableau_io_send_command";
	int result            = 0;

#if defined( HAVE_SCSI_SG_PT_H )
	void *sg_scsi_pt_obj  = NULL;
#endif

	if( file_descriptor == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file descriptor.",
		 function );

		return( -1 );
	}
	if( command == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid command.",
		 function );

		return( -1 );
	}
	if( size_command > (ssize_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid command size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( response == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid response.",
		 function );

		return( -1 );
	}
	if( size_response > (ssize_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid response size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( sense == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid sense.",
		 function );

		return( -1 );
	}
	if( size_sense > (ssize_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid sense size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( HAVE_SCSI_SG_PT_H )
	sg_scsi_pt_obj = construct_scsi_pt_obj();

	if( sg_scsi_pt_obj == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create libsgutils pt scsi object.",
		 function );

		return( -1 );
	}
	set_scsi_pt_cdb(
	 sg_scsi_pt_obj,
	 command,
	 size_command );

	set_scsi_pt_sense(
	 sg_scsi_pt_obj,
	 sense,
	 size_sense );

	set_scsi_pt_data_in(
	 sg_scsi_pt_obj,
	 response,
	 size_response );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: sending SCSI command.\n",
		 function );
	}
#endif
	result = do_scsi_pt(
	          sg_scsi_pt_obj,
	          file_descriptor,
	          LIBTABLEAU_IO_TIMEOUT_NUMBER_OF_SECONDS,
	          libcnotify_verbose );

	if( result == SCSI_PT_DO_BAD_PARAMS )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: invalid data send to device.",
		 function );

		goto on_error;
	}
	else if( result == SCSI_PT_DO_TIMEOUT )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: communication with device timed out.",
		 function );

		goto on_error;
	}
	else if( result != SCSI_PT_DO_START_OK )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to communicate with device.",
		 function );

		goto on_error;
	}
	destruct_scsi_pt_obj(
	 sg_scsi_pt_obj );

	return( 1 );

on_error:
	if( sg_scsi_pt_obj != NULL )
	{
		destruct_scsi_pt_obj(
		 sg_scsi_pt_obj );
	}
	return( -1 );

#else
	libcerror_error_set(
	 error,
	 LIBCERROR_ERROR_DOMAIN_RUNTIME,
	 LIBCERROR_RUNTIME_ERROR_GENERIC,
	 "%s: missing SCSI support.",
	 function );

	return( -1 );

#endif /* defined( HAVE_SCSI_SG_PT_H ) */
}

