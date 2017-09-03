dnl Checks for required headers and functions
dnl
dnl Version: 20170903

dnl Function to detect if libtableau dependencies are available
AC_DEFUN([AX_LIBTABLEAU_CHECK_LOCAL],
  [dnl No additional checks.
  ])

dnl Function to detect if tableautools dependencies are available
AC_DEFUN([AX_TABLEAUTOOLS_CHECK_LOCAL],
  [dnl Check if tools should be build as static executables
  AX_COMMON_CHECK_ENABLE_STATIC_EXECUTABLES

  dnl Check if DLL support is needed
  AS_IF(
    [test "x$enable_shared" = xyes && test "x$ac_cv_enable_static_executables" = xno],
    [AS_CASE(
      [$host],
      [*cygwin* | *mingw*],
      [AC_SUBST(
        [LIBTABLEAU_DLL_IMPORT],
        ["-DLIBTABLEAU_DLL_IMPORT"])
    ])
  ])
])

