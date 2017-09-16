/*
 * Library handle type test program
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

#include <common.h>
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "tableau_test_libcerror.h"
#include "tableau_test_libtableau.h"
#include "tableau_test_macros.h"
#include "tableau_test_memory.h"
#include "tableau_test_unused.h"

#include "../libtableau/libtableau_handle.h"

/* Tests the libtableau_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int tableau_test_handle_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libtableau_handle_t *handle     = NULL;
	int result                      = 0;

#if defined( HAVE_TABLEAU_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libtableau_handle_initialize(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libtableau_handle_free(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libtableau_handle_initialize(
	          NULL,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	handle = (libtableau_handle_t *) 0x12345678UL;

	result = libtableau_handle_initialize(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	handle = NULL;

#if defined( HAVE_TABLEAU_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libtableau_handle_initialize with malloc failing
		 */
		tableau_test_malloc_attempts_before_fail = test_number;

		result = libtableau_handle_initialize(
		          &handle,
		          &error );

		if( tableau_test_malloc_attempts_before_fail != -1 )
		{
			tableau_test_malloc_attempts_before_fail = -1;

			if( handle != NULL )
			{
				libtableau_handle_free(
				 &handle,
				 NULL );
			}
		}
		else
		{
			TABLEAU_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			TABLEAU_TEST_ASSERT_IS_NULL(
			 "handle",
			 handle );

			TABLEAU_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libtableau_handle_initialize with memset failing
		 */
		tableau_test_memset_attempts_before_fail = test_number;

		result = libtableau_handle_initialize(
		          &handle,
		          &error );

		if( tableau_test_memset_attempts_before_fail != -1 )
		{
			tableau_test_memset_attempts_before_fail = -1;

			if( handle != NULL )
			{
				libtableau_handle_free(
				 &handle,
				 NULL );
			}
		}
		else
		{
			TABLEAU_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			TABLEAU_TEST_ASSERT_IS_NULL(
			 "handle",
			 handle );

			TABLEAU_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_TABLEAU_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libtableau_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libtableau_handle_free function
 * Returns 1 if successful or 0 if not
 */
int tableau_test_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libtableau_handle_free(
	          NULL,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libtableau_handle_open function
 * Returns 1 if successful or 0 if not
 */
int tableau_test_handle_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error    = NULL;
	libtableau_handle_t *handle = NULL;
	int result                  = 0;

	/* Initialize test
	 */
	result = tableau_test_handle_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libtableau_handle_initialize(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libtableau_handle_open(
	          handle,
	          narrow_source,
	          LIBTABLEAU_OPEN_READ,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libtableau_handle_open(
	          handle,
	          narrow_source,
	          LIBTABLEAU_OPEN_READ,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libtableau_handle_free(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libtableau_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libtableau_handle_open_wide function
 * Returns 1 if successful or 0 if not
 */
int tableau_test_handle_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error    = NULL;
	libtableau_handle_t *handle = NULL;
	int result                  = 0;

	/* Initialize test
	 */
	result = tableau_test_handle_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libtableau_handle_initialize(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libtableau_handle_open_wide(
	          handle,
	          wide_source,
	          LIBTABLEAU_OPEN_READ,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libtableau_handle_open_wide(
	          handle,
	          wide_source,
	          LIBTABLEAU_OPEN_READ,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libtableau_handle_free(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libtableau_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libtableau_handle_close function
 * Returns 1 if successful or 0 if not
 */
int tableau_test_handle_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libtableau_handle_close(
	          NULL,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libtableau_handle_get_drive_number_of_sectors function
 * Returns 1 if successful or 0 if not
 */
int tableau_test_handle_get_drive_number_of_sectors(
     void )
{
	libcerror_error_t *error           = NULL;
	libtableau_handle_t *handle        = NULL;
	uint32_t drive_number_of_sectors   = 0;
	int drive_number_of_sectors_is_set = 0;
	int result                         = 0;

	/* Initialize test
	 */
	result = libtableau_handle_initialize(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libtableau_handle_get_drive_number_of_sectors(
	          handle,
	          &drive_number_of_sectors,
	          &error );

	TABLEAU_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	drive_number_of_sectors_is_set = result;

	/* Test error cases
	 */
	result = libtableau_handle_get_drive_number_of_sectors(
	          NULL,
	          &drive_number_of_sectors,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( drive_number_of_sectors_is_set != 0 )
	{
		result = libtableau_handle_get_drive_number_of_sectors(
		          handle,
		          NULL,
		          &error );

		TABLEAU_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		TABLEAU_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libtableau_handle_free(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libtableau_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libtableau_handle_get_hpa_number_of_sectors function
 * Returns 1 if successful or 0 if not
 */
int tableau_test_handle_get_hpa_number_of_sectors(
     void )
{
	libcerror_error_t *error         = NULL;
	libtableau_handle_t *handle      = NULL;
	uint32_t hpa_number_of_sectors   = 0;
	int hpa_number_of_sectors_is_set = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libtableau_handle_initialize(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libtableau_handle_get_hpa_number_of_sectors(
	          handle,
	          &hpa_number_of_sectors,
	          &error );

	TABLEAU_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	hpa_number_of_sectors_is_set = result;

	/* Test error cases
	 */
	result = libtableau_handle_get_hpa_number_of_sectors(
	          NULL,
	          &hpa_number_of_sectors,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( hpa_number_of_sectors_is_set != 0 )
	{
		result = libtableau_handle_get_hpa_number_of_sectors(
		          handle,
		          NULL,
		          &error );

		TABLEAU_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		TABLEAU_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libtableau_handle_free(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libtableau_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libtableau_handle_get_dco_number_of_sectors function
 * Returns 1 if successful or 0 if not
 */
int tableau_test_handle_get_dco_number_of_sectors(
     void )
{
	libcerror_error_t *error         = NULL;
	libtableau_handle_t *handle      = NULL;
	uint32_t dco_number_of_sectors   = 0;
	int dco_number_of_sectors_is_set = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libtableau_handle_initialize(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libtableau_handle_get_dco_number_of_sectors(
	          handle,
	          &dco_number_of_sectors,
	          &error );

	TABLEAU_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	dco_number_of_sectors_is_set = result;

	/* Test error cases
	 */
	result = libtableau_handle_get_dco_number_of_sectors(
	          NULL,
	          &dco_number_of_sectors,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( dco_number_of_sectors_is_set != 0 )
	{
		result = libtableau_handle_get_dco_number_of_sectors(
		          handle,
		          NULL,
		          &error );

		TABLEAU_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		TABLEAU_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libtableau_handle_free(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libtableau_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libtableau_handle_get_number_of_tableau_values function
 * Returns 1 if successful or 0 if not
 */
int tableau_test_handle_get_number_of_tableau_values(
     void )
{
	libcerror_error_t *error            = NULL;
	libtableau_handle_t *handle         = NULL;
	uint32_t number_of_tableau_values   = 0;
	int number_of_tableau_values_is_set = 0;
	int result                          = 0;

	/* Initialize test
	 */
	result = libtableau_handle_initialize(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libtableau_handle_get_number_of_tableau_values(
	          handle,
	          &number_of_tableau_values,
	          &error );

	TABLEAU_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	number_of_tableau_values_is_set = result;

	/* Test error cases
	 */
	result = libtableau_handle_get_number_of_tableau_values(
	          NULL,
	          &number_of_tableau_values,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	if( number_of_tableau_values_is_set != 0 )
	{
		result = libtableau_handle_get_number_of_tableau_values(
		          handle,
		          NULL,
		          &error );

		TABLEAU_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		TABLEAU_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Clean up
	 */
	result = libtableau_handle_free(
	          &handle,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libtableau_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc TABLEAU_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] TABLEAU_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc TABLEAU_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] TABLEAU_TEST_ATTRIBUTE_UNUSED )
#endif
{
	TABLEAU_TEST_UNREFERENCED_PARAMETER( argc )
	TABLEAU_TEST_UNREFERENCED_PARAMETER( argv )

	TABLEAU_TEST_RUN(
	 "libtableau_handle_initialize",
	 tableau_test_handle_initialize );

	TABLEAU_TEST_RUN(
	 "libtableau_handle_free",
	 tableau_test_handle_free );

	/* TODO: add tests for libtableau_handle_query */

	TABLEAU_TEST_RUN(
	 "libtableau_handle_get_drive_number_of_sectors",
	 tableau_test_handle_get_drive_number_of_sectors );

	TABLEAU_TEST_RUN(
	 "libtableau_handle_get_hpa_number_of_sectors",
	 tableau_test_handle_get_hpa_number_of_sectors );

	TABLEAU_TEST_RUN(
	 "libtableau_handle_get_dco_number_of_sectors",
	 tableau_test_handle_get_dco_number_of_sectors );

	TABLEAU_TEST_RUN(
	 "libtableau_handle_get_number_of_tableau_values",
	 tableau_test_handle_get_number_of_tableau_values );

	/* TODO: add tests for libtableau_handle_get_tableau_value_identifier */

	/* TODO: add tests for libtableau_handle_get_tableau_value */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

