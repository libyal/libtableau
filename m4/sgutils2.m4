dnl Checks for sgutils2 or required headers and functions
dnl
dnl Version: 20170903

dnl Function to detect if sgutils2 is available
AC_DEFUN([AX_SGUTILS2_CHECK_LIB],
  [dnl Check if parameters were provided
  AS_IF(
    [test "x$ac_cv_with_sgutils2" != x && test "x$ac_cv_with_sgutils2" != xno && test "x$ac_cv_with_sgutils2" != xauto-detect],
    [AS_IF(
      [test -d "$ac_cv_with_sgutils2"],
      [CFLAGS="$CFLAGS -I${ac_cv_with_sgutils2}/include"
      LDFLAGS="$LDFLAGS -L${ac_cv_with_sgutils2}/lib"],
      [AC_MSG_WARN([no such directory: $ac_cv_with_sgutils2])
      ])
    ])

  AS_IF(
    [test "x$ac_cv_with_sgutils2" = xno],
    [ac_cv_sgutils2=no],
    [dnl Check for headers
    AC_CHECK_HEADERS([scsi/sg_lib.h scsi/sg_pt.h])

    AS_IF(
      [test "x$ac_cv_header_scsi_sg_lib_h" = xno || test "x$ac_cv_header_scsi_sg_pt_h" = xno],
      [ac_cv_sgutils2=no],
      [dnl Check for the individual functions
      ac_cv_sgutils2=sgutils2

      AC_CHECK_LIB(
        sgutils2,
        sg_lib_version,
        [],
        [ac_cv_sgutils2=no])

      AS_IF(
        [test "x$ac_cv_lib_sgutils2_sg_lib_version" = xno],
        [AC_MSG_FAILURE(
          [Missing function: sg_lib_version in library: sgutils2.],
          [1])
        ])

      AC_CHECK_LIB(
        sgutils2,
        scsi_pt_open_device,
        [],
        [ac_cv_sgutils2=no])

      AS_IF(
        [test "x$ac_cv_lib_sgutils2_scsi_pt_open_device" = xno],
        [AC_MSG_FAILURE(
          [Missing function: scsi_pt_open_device in library: sgutils2.],
          [1])
        ])

      AC_CHECK_LIB(
        sgutils2,
        scsi_pt_close_device,
        [],
        [ac_cv_sgutils2=no])

      AS_IF(
        [test "x$ac_cv_lib_sgutils2_scsi_pt_close_device" = xno],
        [AC_MSG_FAILURE(
          [Missing function: scsi_pt_close_device in library: sgutils2.],
          [1])
        ])

      AC_CHECK_LIB(
        sgutils2,
        construct_scsi_pt_obj,
        [],
        [ac_cv_sgutils2=no])

      AS_IF(
        [test "x$ac_cv_lib_sgutils2_construct_scsi_pt_obj" = xno],
        [AC_MSG_FAILURE(
          [Missing function: construct_scsi_pt_obj in library: sgutils2.],
          [1])
        ])

      AC_CHECK_LIB(
        sgutils2,
        set_scsi_pt_cdb,
        [],
        [ac_cv_sgutils2=no])

      AS_IF(
        [test "x$ac_cv_lib_sgutils2_set_scsi_pt_cdb" = xno],
        [AC_MSG_FAILURE(
          [Missing function: set_scsi_pt_cdb in library: sgutils2.],
          [1])
        ])

      AC_CHECK_LIB(
        sgutils2,
        set_scsi_pt_sense,
        [],
        [ac_cv_sgutils2=no])

      AS_IF(
        [test "x$ac_cv_lib_sgutils2_set_scsi_pt_sense" = xno],
        [AC_MSG_FAILURE(
          [Missing function: set_scsi_pt_sense in library: sgutils2.],
          [1])
        ])

      AC_CHECK_LIB(
        sgutils2,
        set_scsi_pt_data_in,
        [],
        [ac_cv_sgutils2=no])

      AS_IF(
        [test "x$ac_cv_lib_sgutils2_set_scsi_pt_data_in" = xno],
        [AC_MSG_FAILURE(
          [Missing function: set_scsi_pt_data_in in library: sgutils2.],
          [1])
        ])

      AC_CHECK_LIB(
        sgutils2,
        do_scsi_pt,
        [],
        [ac_cv_sgutils2=no])

      AS_IF(
        [test "x$ac_cv_lib_sgutils2_do_scsi_pt" = xno],
        [AC_MSG_FAILURE(
          [Missing function: do_scsi_pt in library: sgutils2.],
          [1])
        ])

      ac_cv_sgutils2_LIBADD="-lsgutils2";
      ])
    ])

  AS_IF(
    [test "x$ac_cv_sgutils2" = xsgutils2],
    [AC_DEFINE(
      [HAVE_SGUTILS2],
      [1],
      [Define to 1 if you have the 'sgutils2' library (-lsgutils2).])
    ])

  AS_IF(
    [test "x$ac_cv_sgutils2" != xno],
    [AC_SUBST(
      [HAVE_SGUTILS2],
      [1]) ],
    [AC_SUBST(
      [HAVE_SGUTILS2],
      [0])
    ])
  ])

dnl Function to detect how to enable sgutils2
AC_DEFUN([AX_SGUTILS2_CHECK_ENABLE],
  [AX_COMMON_ARG_WITH(
    [sgutils2],
    [sgutils2],
    [search for sgutils2 in includedir and libdir or in the specified DIR, or no if not to use sgutils2],
    [auto-detect],
    [DIR])

  dnl Check for a shared library version
  AX_SGUTILS2_CHECK_LIB

  AS_IF(
    [test "x$ac_cv_sgutils2_CPPFLAGS" != "x"],
    [AC_SUBST(
      [SGUTILS2_CPPFLAGS],
      [$ac_cv_sgutils2_CPPFLAGS])
    ])
  AS_IF(
    [test "x$ac_cv_sgutils2_LIBADD" != "x"],
    [AC_SUBST(
      [SGUTILS2_LIBADD],
      [$ac_cv_sgutils2_LIBADD])
    ])

  AS_IF(
    [test "x$ac_cv_sgutils2" = xsgutils2],
    [AC_SUBST(
      [ax_sgutils2_pc_libs_private],
      [-lsgutils2])
    ])

  AS_IF(
    [test "x$ac_cv_sgutils2" = xsgutils2],
    [AC_SUBST(
      [ax_sgutils2_spec_requires],
      [sgutils2])
    AC_SUBST(
      [ax_sgutils2_spec_build_requires],
      [sgutils2-devel])
    ])
  ])

