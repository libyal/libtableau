/*
 * Library values_table type test program
 *
 * Copyright (C) 2008-2019, Joachim Metz <joachim.metz@gmail.com>
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

#include "../libtableau/libtableau_values_table.h"

#if defined( __GNUC__ ) && !defined( LIBTABLEAU_DLL_IMPORT )

/* Tests the libtableau_values_table_free function
 * Returns 1 if successful or 0 if not
 */
int tableau_test_values_table_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libtableau_values_table_free(
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

	/* TODO: add tests for libtableau_values_table_initialize */

	TABLEAU_TEST_RUN(
	 "libtableau_values_table_free",
	 tableau_test_values_table_free );

	/* TODO: add tests for libtableau_values_table_realloc */

	/* TODO: add tests for libtableau_values_table_get_index */

	/* TODO: add tests for libtableau_values_table_get_identifier */

	/* TODO: add tests for libtableau_values_table_get_value */

	/* TODO: add tests for libtableau_values_table_set_value */

#endif /* defined( __GNUC__ ) && !defined( LIBTABLEAU_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

