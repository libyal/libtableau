/*
 * Library security_values type test program
 *
 * Copyright (C) 2008-2022, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libtableau/libtableau_security_values.h"

#if defined( __GNUC__ ) && !defined( LIBTABLEAU_DLL_IMPORT )

/* Tests the libtableau_security_values_initialize function
 * Returns 1 if successful or 0 if not
 */
int tableau_test_security_values_initialize(
     void )
{
	libcerror_error_t *error                      = NULL;
	libtableau_security_values_t *security_values = NULL;
	int result                                    = 0;

#if defined( HAVE_TABLEAU_TEST_MEMORY )
	int number_of_malloc_fail_tests               = 1;
	int number_of_memset_fail_tests               = 1;
	int test_number                               = 0;
#endif

	/* Test regular cases
	 */
	result = libtableau_security_values_initialize(
	          &security_values,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NOT_NULL(
	 "security_values",
	 security_values );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libtableau_security_values_free(
	          &security_values,
	          &error );

	TABLEAU_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "security_values",
	 security_values );

	TABLEAU_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libtableau_security_values_initialize(
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

	security_values = (libtableau_security_values_t *) 0x12345678UL;

	result = libtableau_security_values_initialize(
	          &security_values,
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

	security_values = NULL;

#if defined( HAVE_TABLEAU_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libtableau_security_values_initialize with malloc failing
		 */
		tableau_test_malloc_attempts_before_fail = test_number;

		result = libtableau_security_values_initialize(
		          &security_values,
		          &error );

		if( tableau_test_malloc_attempts_before_fail != -1 )
		{
			tableau_test_malloc_attempts_before_fail = -1;

			if( security_values != NULL )
			{
				libtableau_security_values_free(
				 &security_values,
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
			 "security_values",
			 security_values );

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
		/* Test libtableau_security_values_initialize with memset failing
		 */
		tableau_test_memset_attempts_before_fail = test_number;

		result = libtableau_security_values_initialize(
		          &security_values,
		          &error );

		if( tableau_test_memset_attempts_before_fail != -1 )
		{
			tableau_test_memset_attempts_before_fail = -1;

			if( security_values != NULL )
			{
				libtableau_security_values_free(
				 &security_values,
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
			 "security_values",
			 security_values );

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
	if( security_values != NULL )
	{
		libtableau_security_values_free(
		 &security_values,
		 NULL );
	}
	return( 0 );
}

/* Tests the libtableau_security_values_free function
 * Returns 1 if successful or 0 if not
 */
int tableau_test_security_values_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libtableau_security_values_free(
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

#endif /* defined( __GNUC__ ) && !defined( LIBTABLEAU_DLL_IMPORT ) */

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

#if defined( __GNUC__ ) && !defined( LIBTABLEAU_DLL_IMPORT )

	TABLEAU_TEST_RUN(
	 "libtableau_security_values_initialize",
	 tableau_test_security_values_initialize );

	TABLEAU_TEST_RUN(
	 "libtableau_security_values_free",
	 tableau_test_security_values_free );

#endif /* defined( __GNUC__ ) && !defined( LIBTABLEAU_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

