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

FORCE_USE_PIC=1

QTEMP_DIR = $(top_srcdir)/src/generated
QITEMP_DIR = $(top_srcdir)/include/generated
SIPTEMP_DIR = sip/generated

MOC_V = $(MOC_V_$(V))
MOC_V_ = $(MOC_V_$(AM_DEFAULT_VERBOSITY))
MOC_V_0 = @echo "  MOC    $< > $@";

SIP_V = $(SIP_V_$(V))
SIP_V_ = $(SIP_V_$(AM_DEFAULT_VERBOSITY))
SIP_V_0 = @echo "  SIP    $< > $@";

SIPCAT_V = $(SIPCAT_V_$(V))
SIPCAT_V_ = $(SIPCAT_V_$(AM_DEFAULT_VERBOSITY))
SIPCAT_V_0 = @echo "  SIPCAT $< > $@";

ECHO_V = $(ECHO_V_$(V))
ECHO_V_ = $(ECHO_V_$(AM_DEFAULT_VERBOSITY))
ECHO_V_0 = @echo $(ECHO_N);

lib_LTLIBRARIES += libqgismobility.la
libqgismobility_la_SOURCES = \
	@abs_top_builddir@/main/generated/moc_QgsMobilityApplicationFrame.cpp \
	@abs_top_builddir@/main/generated/moc_QgsMobilityConfigure.cpp \
	@abs_top_builddir@/main/generated/moc_QgsMobility.cpp \
	@abs_top_builddir@/main/generated/moc_QgsMobilityWorker.cpp \
	main/QgsMobilityApplicationFrame.cpp \
        main/entrypoint.cpp \
	main/QgsMobilityConfigure.cpp \
	main/QgsMobility.cpp \
	main/QgsMobilityWorker.cpp \
	main/QgsMobilityPainter.cpp \
	@abs_top_builddir@/sip/generated/almagation.cpp


libqgismobility_la_CPPFLAGS = $(DEPS_CFLAGS) -I$(top_srcdir)/include -I$(top_srcdir)/include/generated \
	$(SIP_CPPFLAGS)
libqgismobility_la_CXXFLAGS = $(DEPS_CFLAGS) -I$(top_srcdir)/include -I$(top_srcdir)/include/generated \
	$(SIP_CPPFLAGS)
libqgismobility_la_LIBADD = $(DEPS_LIBS)

# Only build executables if we enabled the option during configuration

if EXECUTABLE

# Made this for temporary test purposes

bin_PROGRAMS += qgismobility
qgismobility_SOURCES = \
	programs/qgismobility.cpp
qgismobility_CPPFLAGS = $(DEPS_CFLAGS) $(AM_CFLAGS)
qgismobility_CFLAGS = $(DEPS_CFLAGS) $(AM_CFLAGS)
qgismobility_LDADD = $(DEPS_LIBS) $(top_builddir)/libqgismobility.la

endif

@abs_top_builddir@/main/generated/moc_%.cpp: @abs_top_srcdir@/include/%.h @abs_top_srcdir@/main/%.cpp
	$(MOC_V) @QT_BINARY_PATH@/moc $< -o $@

sip: $(top_srcdir)/sip/*.sip Makefile
	$(ECHO_V) mkdir -p $(SIPTEMP_DIR)
	$(ECHO_V) rm -rf $(SIPTEMP_DIR)/*.cpp
	$(ECHO_V) rm -rf $(SIPTEMP_DIR)/*.h
	$(SIP_V) @SIP_RUN@
	$(SIPCAT_V) cat $(SIPTEMP_DIR)/*.cpp > $(SIPTEMP_DIR)/almagation.cpp

@abs_top_builddir@/sip/generated/almagation.cpp: sip

clean-local:
	@echo "  RM      $(QTEMP_DIR)/*" ; rm -rf $(top_srcdir)/main/generated/*
	@echo "  RM      $(QITEMP_DIR)/*" ; rm -rf $(top_srcdir)/include/generated/*
	@echo "  RM      $(SIPTEMP_DIR)/*.cpp"; rm -rf $(SIPTEMP_DIR)/*.cpp
	@echo "  RM      $(SIPTEMP_DIR)/*.h"; rm -rf $(SIPTEMP_DIR)/*.h
