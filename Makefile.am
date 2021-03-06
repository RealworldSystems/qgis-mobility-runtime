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

COPY_V = $(COPY_V_$(V))
COPY_V_ = $(COPY_V_$(AM_DEFAULT_VERBOSITY))
COPY_V_0 = @echo "  COPY   $@";

RM_V = $(RM_V_$(V))
RM_V_ = $(RM_V_$(AM_DEFAULT_VERBOSITY))
RM_V_0 = @echo "  REMOVE $@";


lib_LTLIBRARIES += libqgismobility.la
libqgismobility_la_SOURCES = \
	@top_builddir@/main/generated/moc_QgsMobilityQMLMap.cpp \
	@top_builddir@/main/generated/moc_QgsMobilityConfigure.cpp \
	@top_builddir@/main/generated/moc_QgsMobility.cpp \
	@top_builddir@/main/generated/moc_QgsMobilityWorker.cpp \
	main/QgsMobilityQMLMap.cpp \
        main/entrypoint.cpp \
	main/QgsMobilityConfigure.cpp \
	main/QgsMobility.cpp \
	main/QgsMobilityWorker.cpp \
	main/QgsMobilityPainter.cpp \
	@top_builddir@/sip/generated/almagation.cpp


libqgismobility_la_CPPFLAGS = $(DEPS_CFLAGS) -I$(top_srcdir)/include $(SIP_CPPFLAGS)
libqgismobility_la_CXXFLAGS = $(DEPS_CFLAGS) -I$(top_srcdir)/include $(SIP_CPPFLAGS)
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

if ANDROID_WRAPPER

# Made for wrapping the runtime function to read parameters and set 
# the system environment through an XML configuration file.

#lib_LTLIBRARIES += libqgismobility_android_wrap.la

libqgismobility_la_SOURCES = \
	android/qgismobility.cpp
#libqgismobility_android_wrap_la_CPPFLAGS = $(DEPS_CFLAGS) -I$(top_srcdir)/include $(SIP_CPPFLAGS)
#libqgismobility_android_wrap_la_CXXFLAGS = $(DEPS_CFLAGS) -I$(top_srcdir)/include $(SIP_CPPFLAGS)
#libqgismobility_android_wrap_la_LIBADD = $(DEPS_LIBS) $(top_builddir)/libqgismobility.la

endif


@top_builddir@/main/generated/moc_%.cpp: @top_srcdir@/include/%.h @top_srcdir@/main/%.cpp
	$(MOC_V) @QT_BINARY_PATH@/moc $< -o $@

#
# If any of the sip files is newer than the almagation, the almagation should be
# generated, otherwise, leave it alone.
#
sip: $(top_srcdir)/sip/*.sip $(top_builddir)/Makefile
	@echo -n ;( should_sip="" ; \
	  if test -f $(SIPTEMP_DIR)/almagation.cpp ; then \
	    for file_name in `ls $(top_srcdir)/sip/*.sip` ; do \
	      if test `stat -c %Y $$file_name` -gt `stat -c %Y $(SIPTEMP_DIR)/almagation.cpp`; then \
	        echo "  SIP    $$file_name has changed" ; \
	        should_sip="t" ; \
	      fi \
	    done ; \
	  else \
	    echo "  SIP    No almagation file found" ; \
	    should_sip="t" ; \
	  fi ; \
	  if test x$$should_sip != x ; then \
	    mkdir -p $(SIPTEMP_DIR) ; \
	    rm -rf $(SIPTEMP_DIR)/*.cpp ; \
	    rm -rf $(SIPTEMP_DIR)/*.h ; \
	    echo "  SIP    $< > $@" ; \
	    if test "x$(ECHO_V)" == x ; then \
	        echo @SIP_RUN@ ; \
	    fi ; \
	    @SIP_RUN@ ; \
	    cat $(SIPTEMP_DIR)/*.cpp > $(SIPTEMP_DIR)/almagation.cpp ; \
	  fi )

@top_builddir@/sip/generated/almagation.cpp: sip

clean-local:
	@echo "  RM      $(QTEMP_DIR)/*" ; rm -rf $(top_srcdir)/main/generated/*
	@echo "  RM      $(SIPTEMP_DIR)/*.cpp"; rm -rf $(SIPTEMP_DIR)/*.cpp
	@echo "  RM      $(SIPTEMP_DIR)/*.h"; rm -rf $(SIPTEMP_DIR)/*.h


install-exec-hook: install-qgsmsystem
uninstall-hook: uninstall-qgsmsystem


install-qgsmsystem:
	$(ECHO_V) $(MAKE) uninstall-qgsmsystem
	$(ECHO_V) $(MKDIR_P) "$(DESTDIR)$(libdir)/qgis-mobility"
	$(COPY_V) cp -R "$(top_srcdir)/qgsmsystem" "$(DESTDIR)$(libdir)/qgis-mobility"

uninstall-qgsmsystem:
	$(RM_V) rm -rf "$(DESTDIR)$(libdir)/qgis-mobility"
