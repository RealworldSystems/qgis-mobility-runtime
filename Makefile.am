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

ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES=
bin_PROGRAMS=

QTEMP_DIR = $(top_srcdir)/src/generated
QITEMP_DIR = $(top_srcdir)/include/generated

MOC_V = $(MOC_V_$(V))
MOC_V_ = $(MOC_V_$(AM_DEFAULT_VERBOSITY))
MOC_V_0 = @echo "  MOC    $< > $@";

lib_LTLIBRARIES += libqgismobility.la
libqgismobility_la_SOURCES = \
        main/entrypoint.cpp

libqgismobility_la_CPPFLAGS = $(DEPS_CFLAGS) -I$(top_srcdir)/include -I$(top_srcdir)/include/generated
libqgismobility_la_CXXFLAGS = $(DEPS_CFLAGS) -I$(top_srcdir)/include -I$(top_srcdir)/include/generated
libqgismobility_la_LIBADD = $(DEPS_LIBS)

# Made this for temporary test purposes

#in_PROGRAMS += qgismobility
#gismobility_SOURCES = \
#       main/entrypoint.cpp
#gismobility_CPPFLAGS = $(DEPS_CFLAGS) $(AM_CFLAGS)
#gismobility_CFLAGS = $(DEPS_CFLAGS) $(AM_CFLAGS)
#gismobility_LDADD = $(DEPS_LIBS) $(top_builddir)/libqgismobility.la


clean:
	@echo "  RM      $(QTEMP_DIR)/*" ; rm -rf $(top_srcdir)/src/generated/*
	@echo "  RM      $(QITEMP_DIR)/*" ; rm -rf $(top_srcdir)/include/generated/*
