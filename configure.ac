#
#  This file is part of QGis Mobility
#
#  QGis Mobility is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  QGis Mobility is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with QGis Mobility. If not, see 
#  <http://www.gnu.org/licenses/>.
#

AC_INIT([QGis Mobility], 
        [0.1],
        [svanleent@gmail.com],
        [qgis-mobility])

AC_PREREQ([2.59])

AC_CONFIG_HEADERS([main/config.h])
AC_CANONICAL_HOST

AC_SUBST(SOURCE_DIR, src)
AC_SUBST(HEADER_DIR, include)

AC_PROG_CXX
LT_INIT
AM_INIT_AUTOMAKE([1.10 no-define subdir-objects])
AM_SILENT_RULES([yes])
AC_CONFIG_MACRO_DIR([m4])

dnl ==== BASE PATH ====
dnl
dnl The base path indicates where ordinarily libraries, headers, etc. should
dnl be found. The base path can be modified so that it points to a different
dnl stack.

BASE_PATH=/usr

AC_ARG_WITH(
	[base-path],
	AS_HELP_STRING(
		[--with-base-path=[BASE_PATH]],
		[to specify the base path, default: /lib]),
	[BASE_PATH="$withval"],
	[])

dnl ==== QT Framework ====
dnl
dnl We need to determine where QT is hanging out. Sometimes, the headers
dnl are installed in a subdirectory, other times not.
dnl
dnl ---- QT Base directory ----
dnl
dnl QT is normally installed there where the BASE_PATH points. It can
dnl be overridden to use another QT infrastructure

QT_BASE_PATH=$BASE_PATH

AC_ARG_WITH(
	[qt-base-path],
	AS_HELP_STRING(
		[--with-qt-base-path=[QT_BASE_PATH]],
		[to specify the base path, default: BASE_PATH]),
	[QT_BASE_PATH="$withval"],
	[])

dnl
dnl ---- QT library path ----
dnl
dnl The QT libraries normally hang out in BASE_PATH/lib

QT_LIBRARY_PATH=$QT_BASE_PATH/lib

AC_ARG_WITH(
	[qt-library-path],
	AS_HELP_STRING(
		[--with-qt-library-path=[QT_LIBRARY_PATH]],
		[to specify the library path, default: $QT_BASE_PATH/lib]),
	[QT_LIBRARY_PATH="$withval"],
	[])

dnl
dnl ---- QT include path ----
dnl
dnl The QT headers normally hang out in BASE_PATH/include/qt4

QT_INCLUDE_PATH=$QT_BASE_PATH/include/qt4

AC_ARG_WITH(
	[qt-include-path],
	AS_HELP_STRING(
		[--with-qt-include-path=[QT_INCLUDE_PATH]],
		[to specify the include path, default: $QT_BASE_PATH/include/qt4]),
	[QT_INCLUDE_PATH="$withval"],
	[])

dnl
dnl ---- QT binary path ----
dnl
dnl The QT binaries normally hang out in BASE_PATH/bin


QT_BINARY_PATH=$QT_BASE_PATH/bin

AC_ARG_WITH(
	[qt-binary-path],
	AS_HELP_STRING(
		[--with-qt-binary-path=[QT_BINARY_PATH]],
		[to specify the include path, default: $QT_BASE_PATH/bin]),
	[QT_BINARY_PATH="$withval"],
	[])


dnl ==== QGIS ====
dnl
dnl We need to determine where QT is hanging out.
dnl
dnl ---- QGIS Base directory ----
dnl
dnl QT is normally installed there where the BASE_PATH points. It can
dnl be overridden to use another QT infrastructure

QGIS_BASE_PATH=$BASE_PATH

AC_ARG_WITH(
	[qgis-base-path],
	AS_HELP_STRING(
		[--with-qgis-base-path=[QGIS_BASE_PATH]],
		[to specify the base path, default: BASE_PATH]),
	[QGIS_BASE_PATH="$withval"],
	[])

dnl
dnl ---- QGIS library path ----
dnl
dnl The QGIS libraries normally hang out in BASE_PATH/lib

QGIS_LIBRARY_PATH=$QGIS_BASE_PATH/lib

AC_ARG_WITH(
	[qgis-library-path],
	AS_HELP_STRING(
		[--with-qgis-library-path=[QGIS_LIBRARY_PATH]],
		[to specify the library path, default: $QGIS_BASE_PATH/lib]),
	[QGIS_LIBRARY_PATH="$withval"],
	[])

dnl
dnl ---- QGIS include path ----
dnl
dnl The QGIS headers normally hang out in BASE_PATH/include/qgis

QGIS_INCLUDE_PATH=$QGIS_BASE_PATH/include/qgis

AC_ARG_WITH(
	[qgis-include-path],
	AS_HELP_STRING(
		[--with-qgis-include-path=[QGIS_INCLUDE_PATH]],
		[to specify the include path, default: $QGIS_BASE_PATH/include/qgis]),
	[QGIS_INCLUDE_PATH="$withval"],
	[])


dnl ==== PYTHON ====
dnl
dnl Python's folder structure is different from normal folder structures.
dnl it has it's header installed one entry further than the normal headers.
dnl
dnl ---- Base directory ----
dnl
dnl The base directory of python is normally
dnl set the base directory of python

PYTHON_BASE_PATH=$BASE_PATH

AC_ARG_WITH(
	[python-base-path],
	AS_HELP_STRING(
		[--with-python-base-path=[PYTHON_BASE_PATH]],
		[to specify the python base path, default: BASE_PATH]),
	[PYTHON_BASE_PATH="$withval"],
	[])

dnl
dnl ---- Python binary path ----
dnl
dnl We need the binary path to be able to get configuration items from SIP

AC_ARG_WITH(
	[python-binary-path],
	AS_HELP_STRING(
		[--with-python-binary-path=[PYTHON_BINARY_PATH]],
		[to specify the python base path, default: PYTHON_BASE_PATH/bin]),
	[PYTHON_BASE_PATH=${withval}],
	[PYTHON_BINARY_PATH=${PYTHON_BASE_PATH}/bin])

dnl
dnl ---- Python library path ----
dnl
dnl Set the library directory of python
PYTHON_LIBRARY_PATH=$PYTHON_BASE_PATH/lib

AC_ARG_WITH(
	[python-library-path],
	AS_HELP_STRING(
		[--with-python-library-path=[PYTHON_LIBRARY_PATH]],
		[to specify the path to the python library directory, default: $PYTHON_BASE_PATH/lib]),
	[PYTHON_LIBRARY_PATH="$withval"],
	[])

dnl
dnl ---- Python library name ----
dnl
dnl Set the library name of the python library to use in -l notation
PYTHON_LIBRARY=python2.7

AC_ARG_WITH(
	[python-library],
	AS_HELP_STRING(
		[--with-python-library=[PYTHON_LIBRARY]],
		[to specify the name of the library, default: python2.7]),
	[PYTHON_LIBRARY="$withval"],
	[])


dnl
dnl ---- Python include path ----
dnl
dnl Set the include directory of python, normally in PYTHON_BASE_PATH/include/python
PYTHON_INCLUDE_PATH=$PYTHON_BASE_PATH/include/python2.7

AC_ARG_WITH(
	[python-include-path],
	AS_HELP_STRING(
		[--with-python-include-path=[PYTHON_INCLUDE_PATH]],
		[to specify where the python libraries are, default: PYTHON_BASE_PATH/include/python2.7]),
	[PYTHON_INCLUDE_PATH="$withval"],
	[])

dnl
dnl ---- Option to enable whether or not to build an executable
dnl
dnl Devices don't always support directly invoking executables. This might be
dnl accomplished through an additional layer. By using this option, an
dnl executable binary is compiled to load the library.
AC_ARG_ENABLE(
	[executable],
	AS_HELP_STRING(
		[--enable-executable],
		[If you want to compile an aiding executable to the library]),
		[executable=${enableval}],
		[executable=no])

dnl Inform Automake that we want an executable
AM_CONDITIONAL(EXECUTABLE, test x$executable = xyes)

dnl
dnl ==== QGis Mobility ====
dnl
dnl ---- Overrides the Runtime QGis prefix path
dnl
dnl Ordinarily, on Unix systems, QGis lives at /usr, and is set to QGis Base 
dnl Path. QGis mobility uses this information to determine where to set
dnl the prefix path and the plugin path.

AC_ARG_WITH(
	[runtime-prefix-path],
	AS_HELP_STRING(
		[--with-runtime-prefix-path=QGIS_PREFIX_PATH],
		[to specify where the runtime should find the]
		[QGis 3rd party libraries.]
		[(Default: QGIS_BASE_PATH)]),
	[RUNTIME_PREFIX_PATH=${withval}],
	[RUNTIME_PREFIX_PATH=${QGIS_BASE_PATH}])

AC_DEFINE_UNQUOTED(
	[PREFIX_PATH],
	["$RUNTIME_PREFIX_PATH"],
	[Define the runtime prefix path])

dnl
dnl ---- Overrides the Runtime QGis plugin path
dnl
dnl Ordinarily, on Unix systems, the plugins of QGis live at 
dnl /usr/lib/qgis/plugins. This is used for both plugins as well as providers.

AC_ARG_WITH(
	[runtime-plugin-path],
	AS_HELP_STRING(
		[--with-runtime-plugin-path=QGIS_PLUGIN_PATH],
		[to speficy where the runtime should find the]
		[QGis plugins.]
		[(Default: RUNTIME_PREFIX_PATH/lib/qgis/plugins)]),
	[RUNTIME_PLUGIN_PATH=${withval}],
	[RUNTIME_PLUGIN_PATH=${RUNTIME_PREFIX_PATH}/lib/qgis/plugins])

AC_DEFINE_UNQUOTED(
	[PLUGIN_PATH],
	["$RUNTIME_PLUGIN_PATH"],
	[Define the runtime plugin path])

dnl
dnl ---- The path where the project code lives
dnl
dnl This should be set to be the project code directory. This could be different
dnl on the build host versus the target. This needs to have the explicit code
dnl for the target, rather than the build machine.

AC_ARG_WITH(
	[project-code-path],
	[AS_HELP_STRING(
		[--with-project-code-path=PROJECT_CODE_PATH],
		[to specify where the project code lives. The default points]
		[to the example path in the source folder])],
	[PROJECT_CODE_PATH=${withval}],
	[PROJECT_CODE_PATH=$srcdir/samples/centercontrol])

AC_DEFINE_UNQUOTED(
	[PROJECT_CODE_PATH],
	["$PROJECT_CODE_PATH"],
	[Define the project code path])


dnl
dnl ---- The path where the preconfiguration code lives
dnl
dnl This should be set to be the preconfiguration directory. It defaults to
dnl preconfig

AC_ARG_WITH(
	[preconfig-path],
	[AS_HELP_STRING(
		[--with-preconfig-path=PRECONFIG_PATH],
		[to specify where preconfiguration lives])],
	[PRECONFIG_PATH=${withval}],
	[PRECONFIG_PATH=$srcdir/qgsmsystem])

AC_DEFINE_UNQUOTED(
	[PRECONFIG_PATH],
	["$PRECONFIG_PATH"],
	[Define the preconfiguration path])


dnl
dnl ---- This is a modified version of AX_SIP_DEVEL, look in m4/
dnl
AX_SIP_DEVEL

dnl
dnl ---- Doing the SIP matter with Autoconf
dnl
dnl SIP has rich documentation, however, there appears to be little about
dnl how to integrate it in autoconf. It is clear that it depends on a valid
dnl python installation.
dnl
	 
AC_CHECK_PROG(
	[PYTHON], [python], [$(which python)],
	[AC_MSG_ERROR([python required for generating SIP files])],
	[${PYTHON_BINARY_PATH}])

SIP_PATH=$srcdir/sip
SIP_GENERATED=`pwd`/sip/generated

mkdir -p $SIP_GENERATED

ac_sip_build_file="$SIP_GENERATED/qgsmobility.sbf"
ac_py_import="from PyQt4 import pyqtconfig"
ac_py_pyqt_sip_flags="pyqtconfig.Configuration().pyqt_sip_flags"
ac_py_pyqt_sip_dir="pyqtconfig.Configuration().pyqt_sip_dir"


dnl
dnl ---- Override options for PyQt4 flags
dnl
dnl The normal python routine returns the sip flags from the PyQt4 package,
dnl however, if these need to be adapted to fit a certain configuration, this
dnl can be done by setting the proper flags
dnl
AC_ARG_WITH(
	[pyqt4-flags],
	[AS_HELP_STRING(
		[--with-pyqt4-flags=PYQT4_FLAGS],
		[to specify what flags SIP should be using for PyQt4])],
	[PYQT4_FLAGS=${withval}],
	[PYQT4_FLAGS=`$PYTHON -c "$ac_py_import; print $ac_py_pyqt_sip_flags"`])

dnl
dnl ---- Override options for PyQt4 SIP directory
dnl
dnl The normal python routine returns the directory where the PyQt4 SIP files
dnl are. If for some reason these are not correct, it should be possible to
dnl override this behavior.

AC_ARG_WITH(
	[pyqt4-dir],
	[AS_HELP_STRING(
		[--with-pyqt4-dir=PYQT4_DIR],
		[to specify in which directory PyQt4's SIP module files]
		[are installed])],
	[PYQT4_DIR=${withval}],
	[PYQT4_DIR=`$PYTHON -c "$ac_py_import; print $ac_py_pyqt_sip_dir"`])

SIP_RUN="$SIP -c $SIP_GENERATED -b $ac_sip_build_file \
	      -I $PYQT4_DIR $PYQT4_FLAGS $SIP_PATH/QgsMobilitymod.sip"

AC_SUBST(SIP_RUN, $SIP_RUN)

AC_PATH_XTRA

LIB_DIRS="-L$PYTHON_LIBRARY_PATH -L$QT_LIBRARY_PATH -L$QGIS_LIBRARY_PATH"

QT_INCLUDES="\
	-I$QT_INCLUDE_PATH \
	-I$QT_INCLUDE_PATH/Qt \
	-I$QT_INCLUDE_PATH/QtCore \
	-I$QT_INCLUDE_PATH/QtXml \
	-I$QT_INCLUDE_PATH/QtGui \
	-I$QT_INCLUDE_PATH/QtDeclarative"

dnl TODO Need to find ways to do autoconf checks on these
QT_LIBS="-lQtGui -lQtCore -lQtXml -lQtDeclarative"

dnl TODO Need to find wais to do autoconf checks on -lz and -lm

EXT_LIBS="$LIB_DIRS $QT_LIBS -lz -lm $X_LIBS $X_EXTRA_LIBS"
EXT_INCLUDES="$QT_INCLUDES -I$QGIS_INCLUDE_PATH -I$PYTHON_INCLUDE_PATH"
EXT_FLAGS="$X_CFLAGS -DQT_CORE_LIB -DQT_SHARED -DCORE_EXPORT= -DGUI_EXPORT="

AC_SUBST(QT_BINARY_PATH, $QT_BINARY_PATH)
AC_SUBST(EXT_LIBS, $EXT_LIBS)
AC_SUBST(PLUGIN_DIR, $PLUGIN_DIR)
AC_SUBST(PYTHON_INCLUDE, $PYTHON_INCLUDE)

export INCLUDES="$INCLUDES $EXT_INCLUDES"
export PATH="$PATH:$QT_BINARY_PATH"
export CXXFLAGS="$CXXFLAGS $EXT_INCLUDES $EXT_LIBS $EXT_FLAGS"
export LIBS="$LIBS $EXT_LIBS"
export LDFLAGS="$LDFLAGS $EXT_LIBS"


AC_CHECK_LIB(
	[qgis_core], [GEOPROJ4], ,
	AC_MSG_ERROR([QGis core library not found]))

AC_CHECK_LIB(
	[$PYTHON_LIBRARY], [Py_Initialize], ,
	AC_MSG_ERROR([Python library not found]))
	
AC_CHECK_HEADER(
	[$PYTHON_INCLUDE_PATH/Python.h], ,
	AC_MSG_ERROR([Python header not found]),
	AC_INCLUDES_DEFAULT)




# Now we check whether we can actually build a Qt app.
cat > myqt.h << EOF
#include <QtCore/QObject>
class Test : public QObject
{
Q_OBJECT
public:
  Test() {}
  ~Test() {}
public slots:
  void receive() {}
signals:
  void send();
};
EOF

cat > myqt.cpp << EOF
#include "myqt.h"
#include <QtGui/QApplication>
int main( int argc, char **argv )
{
  QApplication app( argc, argv );
  Test t;
  QObject::connect( &t, SIGNAL(send()), &t, SLOT(receive()) );
}
EOF

AC_MSG_CHECKING(does moc work?)
bnv_try_1="$QT_BINARY_PATH/moc myqt.h -o moc_myqt.cpp"
AC_TRY_EVAL(bnv_try_1)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(moc doesn't work)
fi
AC_MSG_RESULT(yes)
AC_MSG_CHECKING(can I compile moc_myqt.cpp?)
bnv_try_2="$CXX -c $CXXFLAGS -o moc_myqt.o moc_myqt.cpp"
AC_TRY_EVAL(bnv_try_2)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(couldn't compile moc_myqt.cpp)
fi
AC_MSG_RESULT(yes)
AC_MSG_CHECKING(can I compile myqt.cpp?)
bnv_try_3="$CXX $QTINC -c $CXXFLAGS -o myqt.o myqt.cpp"
AC_TRY_EVAL(bnv_try_3)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(couldn't compile myqt.cpp)
fi
AC_MSG_RESULT(yes)
AC_MSG_CHECKING(can I link against QT?)
nv_try_4="$CXX $LIBS -o myqt myqt.o moc_myqt.o"
AC_TRY_EVAL(bnv_try_4)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(couldn't link)
fi
AC_MSG_RESULT(yes)

AC_MSG_CHECKING(for mkoctfile)
AC_TRY_EVAL(mkoctfile)
if test x"$ac_status" != x0; then
   AC_MSG_ERROR(mkoctfile is not in the path)
fi
AC_MSG_RESULT(yes)
rm -f moc_myqt.cpp myqt.h myqt.cpp myqt.o myqt moc_myqt.o

if echo "$host" | grep android >/dev/null ; then
   AC_DEFINE([ANDROID], [1], [We are targetting an ANDROID device])
fi

if echo "$host_alias" | grep android >/dev/null ; then
   AC_DEFINE([ANDROID], [1], [We are targetting an ANDROID device])
fi

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
