
########################
## CONFIG FILE FOR AC ##
########################

########### INIT #######################################
AC_INIT([ccStickers],[1.0],[andrea.rigoni@pd.infn.it])

AC_CONFIG_MACRO_DIR([conf/m4])
AC_CONFIG_AUX_DIR([conf])
AM_INIT_AUTOMAKE([subdir-objects])

AC_CONFIG_SRCDIR([Common.am])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
CFLAGS=""
CXXFLAGS=""
AC_PROG_CC
AC_PROG_CXX



AM_PROG_CC_C_O

AC_PROG_LIBTOOL

LIBADD_DL="-ldl"
AC_SUBST(LIBADD_DL)

AC_SEARCH_LIBS([strerror],[cposix])
LT_INIT()
AC_SUBST([LIBTOOL_DEPS])


######### CHECKS ########################################
# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h assert.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([fesetround floor pow sqrt strdup strstr])

AC_SEARCH_LIBS([strerror],[cposix])




######### MAKEFILES #########################################


AC_CONFIG_FILES([
        Makefile
        src/Makefile
        src/testing/Makefile
        src/Core/Makefile
        src/Core/testing/Makefile
        src/Math/Makefile
        src/Math/testing/Makefile
        src/Graphic2D/Makefile
        src/Graphic2D/testing/Makefile
        src/IO/Makefile
        src/IO/testing/Makefile
        recipes/Makefile
	])
AC_OUTPUT

		 
