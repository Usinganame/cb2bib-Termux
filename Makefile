#############################################################################
# Makefile for building: cb2bib
# Generated by qmake (3.1) (Qt 5.15.5)
# Project:  cb2bib.pro
# Template: subdirs
# Command: /data/data/com.termux/files/usr/bin/qmake -o Makefile cb2bib.pro -config use_lz4
#############################################################################

MAKEFILE      = Makefile

EQ            = =

first: make_first
QMAKE         = /data/data/com.termux/files/usr/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = cp -f -R
QINSTALL      = /data/data/com.termux/files/usr/bin/qmake -install qinstall
QINSTALL_PROGRAM = /data/data/com.termux/files/usr/bin/qmake -install qinstall -exe
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f
DISTNAME      = cb2bib1.0.0
DISTDIR = /data/data/com.termux/files/home/cb2bib/.tmp/cb2bib1.0.0
SUBTARGETS    =  \
		sub-src-c2b-c2blib-pro \
		sub-src


sub-src-c2b-c2blib-pro-qmake_all:  FORCE
	@test -d src/c2b/ || mkdir -p src/c2b/
	cd src/c2b/ && $(QMAKE) -o Makefile.c2blib /data/data/com.termux/files/home/cb2bib/src/c2b/c2blib.pro -config use_lz4
	cd src/c2b/ && $(MAKE) -f Makefile.c2blib qmake_all
sub-src-c2b-c2blib-pro: FORCE
	@test -d src/c2b/ || mkdir -p src/c2b/
	cd src/c2b/ && ( test -e Makefile.c2blib || $(QMAKE) -o Makefile.c2blib /data/data/com.termux/files/home/cb2bib/src/c2b/c2blib.pro -config use_lz4 ) && $(MAKE) -f Makefile.c2blib
sub-src-c2b-c2blib-pro-make_first: FORCE
	@test -d src/c2b/ || mkdir -p src/c2b/
	cd src/c2b/ && ( test -e Makefile.c2blib || $(QMAKE) -o Makefile.c2blib /data/data/com.termux/files/home/cb2bib/src/c2b/c2blib.pro -config use_lz4 ) && $(MAKE) -f Makefile.c2blib 
sub-src-c2b-c2blib-pro-all: FORCE
	@test -d src/c2b/ || mkdir -p src/c2b/
	cd src/c2b/ && ( test -e Makefile.c2blib || $(QMAKE) -o Makefile.c2blib /data/data/com.termux/files/home/cb2bib/src/c2b/c2blib.pro -config use_lz4 ) && $(MAKE) -f Makefile.c2blib all
sub-src-c2b-c2blib-pro-clean: FORCE
	@test -d src/c2b/ || mkdir -p src/c2b/
	cd src/c2b/ && ( test -e Makefile.c2blib || $(QMAKE) -o Makefile.c2blib /data/data/com.termux/files/home/cb2bib/src/c2b/c2blib.pro -config use_lz4 ) && $(MAKE) -f Makefile.c2blib clean
sub-src-c2b-c2blib-pro-distclean: FORCE
	@test -d src/c2b/ || mkdir -p src/c2b/
	cd src/c2b/ && ( test -e Makefile.c2blib || $(QMAKE) -o Makefile.c2blib /data/data/com.termux/files/home/cb2bib/src/c2b/c2blib.pro -config use_lz4 ) && $(MAKE) -f Makefile.c2blib distclean
sub-src-c2b-c2blib-pro-install_subtargets: FORCE
	@test -d src/c2b/ || mkdir -p src/c2b/
	cd src/c2b/ && ( test -e Makefile.c2blib || $(QMAKE) -o Makefile.c2blib /data/data/com.termux/files/home/cb2bib/src/c2b/c2blib.pro -config use_lz4 ) && $(MAKE) -f Makefile.c2blib install
sub-src-c2b-c2blib-pro-uninstall_subtargets: FORCE
	@test -d src/c2b/ || mkdir -p src/c2b/
	cd src/c2b/ && ( test -e Makefile.c2blib || $(QMAKE) -o Makefile.c2blib /data/data/com.termux/files/home/cb2bib/src/c2b/c2blib.pro -config use_lz4 ) && $(MAKE) -f Makefile.c2blib uninstall
sub-src-qmake_all:  FORCE
	@test -d src/ || mkdir -p src/
	cd src/ && $(QMAKE) -o Makefile /data/data/com.termux/files/home/cb2bib/src/src.pro -config use_lz4
	cd src/ && $(MAKE) -f Makefile qmake_all
sub-src: FORCE
	@test -d src/ || mkdir -p src/
	cd src/ && ( test -e Makefile || $(QMAKE) -o Makefile /data/data/com.termux/files/home/cb2bib/src/src.pro -config use_lz4 ) && $(MAKE) -f Makefile
sub-src-make_first: FORCE
	@test -d src/ || mkdir -p src/
	cd src/ && ( test -e Makefile || $(QMAKE) -o Makefile /data/data/com.termux/files/home/cb2bib/src/src.pro -config use_lz4 ) && $(MAKE) -f Makefile 
sub-src-all: FORCE
	@test -d src/ || mkdir -p src/
	cd src/ && ( test -e Makefile || $(QMAKE) -o Makefile /data/data/com.termux/files/home/cb2bib/src/src.pro -config use_lz4 ) && $(MAKE) -f Makefile all
sub-src-clean: FORCE
	@test -d src/ || mkdir -p src/
	cd src/ && ( test -e Makefile || $(QMAKE) -o Makefile /data/data/com.termux/files/home/cb2bib/src/src.pro -config use_lz4 ) && $(MAKE) -f Makefile clean
sub-src-distclean: FORCE
	@test -d src/ || mkdir -p src/
	cd src/ && ( test -e Makefile || $(QMAKE) -o Makefile /data/data/com.termux/files/home/cb2bib/src/src.pro -config use_lz4 ) && $(MAKE) -f Makefile distclean
sub-src-install_subtargets: FORCE
	@test -d src/ || mkdir -p src/
	cd src/ && ( test -e Makefile || $(QMAKE) -o Makefile /data/data/com.termux/files/home/cb2bib/src/src.pro -config use_lz4 ) && $(MAKE) -f Makefile install
sub-src-uninstall_subtargets: FORCE
	@test -d src/ || mkdir -p src/
	cd src/ && ( test -e Makefile || $(QMAKE) -o Makefile /data/data/com.termux/files/home/cb2bib/src/src.pro -config use_lz4 ) && $(MAKE) -f Makefile uninstall

Makefile: cb2bib.pro ../../usr/lib/qt/mkspecs/termux/qmake.conf ../../usr/lib/qt/mkspecs/features/spec_pre.prf \
		../../usr/lib/qt/mkspecs/common/unix.conf \
		../../usr/lib/qt/mkspecs/common/linux.conf \
		../../usr/lib/qt/mkspecs/common/sanitize.conf \
		../../usr/lib/qt/mkspecs/common/gcc-base.conf \
		../../usr/lib/qt/mkspecs/common/gcc-base-unix.conf \
		../../usr/lib/qt/mkspecs/common/clang.conf \
		../../usr/lib/qt/mkspecs/qconfig.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_bootstrap_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_concurrent.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_concurrent_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_core.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_core_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_dbus.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_dbus_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_designer.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_designer_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_designercomponents_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_devicediscovery_support_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_edid_support_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_fb_support_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_fontdatabase_support_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_gui.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_gui_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_help.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_help_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_input_support_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_location.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_location_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_multimedia.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_multimedia_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_multimediagsttools_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_multimediawidgets.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_multimediawidgets_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_network.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_network_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_packetprotocol_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_pdf.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_pdf_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_pdfwidgets.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_pdfwidgets_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_positioning.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_positioning_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_positioningquick.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_positioningquick_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_printsupport.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_printsupport_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_qml.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_qml_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_qmldebug_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_qmldevtools_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_qmlmodels.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_qmlmodels_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_qmltest.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_qmltest_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_qmlworkerscript.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_qmlworkerscript_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_quick.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_quick_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_quickcontrols2.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_quickcontrols2_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_quickshapes_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_quicktemplates2.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_quicktemplates2_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_quickwidgets.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_quickwidgets_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_script.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_script_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_scripttools.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_scripttools_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_sensors.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_sensors_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_serialport.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_serialport_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_service_support_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_sql.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_sql_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_svg.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_svg_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_testlib.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_testlib_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_theme_support_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_uiplugin.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_uitools.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_uitools_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_webchannel.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_webchannel_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_webengine.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_webengine_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_webenginecore.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_webenginecore_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_webenginecoreheaders_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_webenginewidgets.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_webenginewidgets_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_webkit.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_webkit_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_webkitwidgets.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_webkitwidgets_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_websockets.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_websockets_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_widgets.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_widgets_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_x11extras.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_x11extras_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_xkbcommon_support_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_xml.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_xml_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_xmlpatterns.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_xmlpatterns_private.pri \
		../../usr/lib/qt/mkspecs/modules/qt_lib_zlib_private.pri \
		../../usr/lib/qt/mkspecs/features/qt_functions.prf \
		../../usr/lib/qt/mkspecs/features/qt_config.prf \
		../../usr/lib/qt/mkspecs/termux/qmake.conf \
		../../usr/lib/qt/mkspecs/features/spec_post.prf \
		../../usr/lib/qt/mkspecs/features/exclusive_builds.prf \
		../../usr/lib/qt/mkspecs/features/toolchain.prf \
		../../usr/lib/qt/mkspecs/features/default_pre.prf \
		../../usr/lib/qt/mkspecs/features/resolve_config.prf \
		../../usr/lib/qt/mkspecs/features/default_post.prf \
		../../usr/lib/qt/mkspecs/features/warn_on.prf \
		../../usr/lib/qt/mkspecs/features/qmake_use.prf \
		../../usr/lib/qt/mkspecs/features/file_copies.prf \
		../../usr/lib/qt/mkspecs/features/testcase_targets.prf \
		../../usr/lib/qt/mkspecs/features/exceptions.prf \
		../../usr/lib/qt/mkspecs/features/yacc.prf \
		../../usr/lib/qt/mkspecs/features/lex.prf \
		cb2bib.pro
	$(QMAKE) -o Makefile cb2bib.pro -config use_lz4
../../usr/lib/qt/mkspecs/features/spec_pre.prf:
../../usr/lib/qt/mkspecs/common/unix.conf:
../../usr/lib/qt/mkspecs/common/linux.conf:
../../usr/lib/qt/mkspecs/common/sanitize.conf:
../../usr/lib/qt/mkspecs/common/gcc-base.conf:
../../usr/lib/qt/mkspecs/common/gcc-base-unix.conf:
../../usr/lib/qt/mkspecs/common/clang.conf:
../../usr/lib/qt/mkspecs/qconfig.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_bootstrap_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_concurrent.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_concurrent_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_core.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_core_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_dbus.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_dbus_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_designer.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_designer_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_designercomponents_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_devicediscovery_support_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_edid_support_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_fb_support_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_fontdatabase_support_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_gui.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_gui_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_help.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_help_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_input_support_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_location.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_location_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_multimedia.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_multimedia_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_multimediagsttools_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_multimediawidgets.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_multimediawidgets_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_network.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_network_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_packetprotocol_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_pdf.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_pdf_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_pdfwidgets.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_pdfwidgets_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_positioning.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_positioning_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_positioningquick.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_positioningquick_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_printsupport.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_printsupport_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_qml.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_qml_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_qmldebug_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_qmldevtools_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_qmlmodels.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_qmlmodels_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_qmltest.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_qmltest_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_qmlworkerscript.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_qmlworkerscript_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_quick.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_quick_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_quickcontrols2.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_quickcontrols2_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_quickshapes_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_quicktemplates2.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_quicktemplates2_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_quickwidgets.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_quickwidgets_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_script.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_script_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_scripttools.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_scripttools_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_sensors.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_sensors_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_serialport.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_serialport_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_service_support_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_sql.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_sql_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_svg.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_svg_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_testlib.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_testlib_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_theme_support_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_uiplugin.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_uitools.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_uitools_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_webchannel.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_webchannel_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_webengine.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_webengine_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_webenginecore.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_webenginecore_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_webenginecoreheaders_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_webenginewidgets.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_webenginewidgets_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_webkit.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_webkit_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_webkitwidgets.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_webkitwidgets_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_websockets.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_websockets_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_widgets.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_widgets_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_x11extras.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_x11extras_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_xkbcommon_support_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_xml.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_xml_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_xmlpatterns.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_xmlpatterns_private.pri:
../../usr/lib/qt/mkspecs/modules/qt_lib_zlib_private.pri:
../../usr/lib/qt/mkspecs/features/qt_functions.prf:
../../usr/lib/qt/mkspecs/features/qt_config.prf:
../../usr/lib/qt/mkspecs/termux/qmake.conf:
../../usr/lib/qt/mkspecs/features/spec_post.prf:
../../usr/lib/qt/mkspecs/features/exclusive_builds.prf:
../../usr/lib/qt/mkspecs/features/toolchain.prf:
../../usr/lib/qt/mkspecs/features/default_pre.prf:
../../usr/lib/qt/mkspecs/features/resolve_config.prf:
../../usr/lib/qt/mkspecs/features/default_post.prf:
../../usr/lib/qt/mkspecs/features/warn_on.prf:
../../usr/lib/qt/mkspecs/features/qmake_use.prf:
../../usr/lib/qt/mkspecs/features/file_copies.prf:
../../usr/lib/qt/mkspecs/features/testcase_targets.prf:
../../usr/lib/qt/mkspecs/features/exceptions.prf:
../../usr/lib/qt/mkspecs/features/yacc.prf:
../../usr/lib/qt/mkspecs/features/lex.prf:
cb2bib.pro:
qmake: FORCE
	@$(QMAKE) -o Makefile cb2bib.pro -config use_lz4

qmake_all: sub-src-c2b-c2blib-pro-qmake_all sub-src-qmake_all FORCE

make_first: sub-src-c2b-c2blib-pro-make_first sub-src-make_first  FORCE
all: sub-src-c2b-c2blib-pro-all sub-src-all  FORCE
clean: sub-src-c2b-c2blib-pro-clean sub-src-clean  FORCE
distclean: sub-src-c2b-c2blib-pro-distclean sub-src-distclean  FORCE
	-$(DEL_FILE) Makefile
	-$(DEL_FILE) .qmake.stash
install_subtargets: sub-src-c2b-c2blib-pro-install_subtargets sub-src-install_subtargets FORCE
uninstall_subtargets: sub-src-c2b-c2blib-pro-uninstall_subtargets sub-src-uninstall_subtargets FORCE

sub-src-c2b-c2blib-pro-check:
	@test -d src/c2b/ || mkdir -p src/c2b/
	cd src/c2b/ && ( test -e Makefile.c2blib || $(QMAKE) -o Makefile.c2blib /data/data/com.termux/files/home/cb2bib/src/c2b/c2blib.pro -config use_lz4 ) && $(MAKE) -f Makefile.c2blib check
sub-src-check:
	@test -d src/ || mkdir -p src/
	cd src/ && ( test -e Makefile || $(QMAKE) -o Makefile /data/data/com.termux/files/home/cb2bib/src/src.pro -config use_lz4 ) && $(MAKE) -f Makefile check
check: sub-src-c2b-c2blib-pro-check sub-src-check

sub-src-c2b-c2blib-pro-benchmark:
	@test -d src/c2b/ || mkdir -p src/c2b/
	cd src/c2b/ && ( test -e Makefile.c2blib || $(QMAKE) -o Makefile.c2blib /data/data/com.termux/files/home/cb2bib/src/c2b/c2blib.pro -config use_lz4 ) && $(MAKE) -f Makefile.c2blib benchmark
sub-src-benchmark:
	@test -d src/ || mkdir -p src/
	cd src/ && ( test -e Makefile || $(QMAKE) -o Makefile /data/data/com.termux/files/home/cb2bib/src/src.pro -config use_lz4 ) && $(MAKE) -f Makefile benchmark
benchmark: sub-src-c2b-c2blib-pro-benchmark sub-src-benchmark
install:install_subtargets  FORCE

uninstall: uninstall_subtargets FORCE

FORCE:

dist: distdir FORCE
	(cd `dirname $(DISTDIR)` && $(TAR) $(DISTNAME).tar $(DISTNAME) && $(COMPRESS) $(DISTNAME).tar) && $(MOVE) `dirname $(DISTDIR)`/$(DISTNAME).tar.gz . && $(DEL_FILE) -r $(DISTDIR)

distdir: sub-src-c2b-c2blib-pro-distdir sub-src-distdir FORCE
	@test -d $(DISTDIR) || mkdir -p $(DISTDIR)
	$(COPY_FILE) --parents ../../usr/lib/qt/mkspecs/features/spec_pre.prf ../../usr/lib/qt/mkspecs/common/unix.conf ../../usr/lib/qt/mkspecs/common/linux.conf ../../usr/lib/qt/mkspecs/common/sanitize.conf ../../usr/lib/qt/mkspecs/common/gcc-base.conf ../../usr/lib/qt/mkspecs/common/gcc-base-unix.conf ../../usr/lib/qt/mkspecs/common/clang.conf ../../usr/lib/qt/mkspecs/qconfig.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_bootstrap_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_concurrent.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_concurrent_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_core.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_core_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_dbus.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_dbus_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_designer.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_designer_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_designercomponents_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_devicediscovery_support_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_edid_support_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_eventdispatcher_support_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_fb_support_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_fontdatabase_support_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_gui.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_gui_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_help.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_help_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_input_support_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_location.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_location_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_multimedia.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_multimedia_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_multimediagsttools_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_multimediawidgets.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_multimediawidgets_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_network.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_network_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_packetprotocol_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_pdf.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_pdf_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_pdfwidgets.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_pdfwidgets_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_positioning.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_positioning_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_positioningquick.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_positioningquick_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_printsupport.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_printsupport_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_qml.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_qml_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_qmldebug_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_qmldevtools_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_qmlmodels.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_qmlmodels_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_qmltest.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_qmltest_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_qmlworkerscript.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_qmlworkerscript_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_qtmultimediaquicktools_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_quick.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_quick_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_quickcontrols2.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_quickcontrols2_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_quickshapes_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_quicktemplates2.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_quicktemplates2_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_quickwidgets.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_quickwidgets_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_script.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_script_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_scripttools.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_scripttools_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_sensors.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_sensors_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_serialport.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_serialport_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_service_support_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_sql.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_sql_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_svg.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_svg_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_testlib.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_testlib_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_theme_support_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_uiplugin.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_uitools.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_uitools_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_webchannel.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_webchannel_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_webengine.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_webengine_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_webenginecore.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_webenginecore_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_webenginecoreheaders_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_webenginewidgets.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_webenginewidgets_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_webkit.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_webkit_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_webkitwidgets.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_webkitwidgets_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_websockets.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_websockets_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_widgets.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_widgets_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_x11extras.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_x11extras_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_xcb_qpa_lib_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_xkbcommon_support_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_xml.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_xml_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_xmlpatterns.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_xmlpatterns_private.pri ../../usr/lib/qt/mkspecs/modules/qt_lib_zlib_private.pri ../../usr/lib/qt/mkspecs/features/qt_functions.prf ../../usr/lib/qt/mkspecs/features/qt_config.prf ../../usr/lib/qt/mkspecs/termux/qmake.conf ../../usr/lib/qt/mkspecs/features/spec_post.prf ../../usr/lib/qt/mkspecs/features/exclusive_builds.prf ../../usr/lib/qt/mkspecs/features/toolchain.prf ../../usr/lib/qt/mkspecs/features/default_pre.prf ../../usr/lib/qt/mkspecs/features/resolve_config.prf ../../usr/lib/qt/mkspecs/features/default_post.prf ../../usr/lib/qt/mkspecs/features/warn_on.prf ../../usr/lib/qt/mkspecs/features/qmake_use.prf ../../usr/lib/qt/mkspecs/features/file_copies.prf ../../usr/lib/qt/mkspecs/features/testcase_targets.prf ../../usr/lib/qt/mkspecs/features/exceptions.prf ../../usr/lib/qt/mkspecs/features/yacc.prf ../../usr/lib/qt/mkspecs/features/lex.prf cb2bib.pro $(DISTDIR)/

sub-src-c2b-c2blib-pro-distdir: FORCE
	@test -d src/c2b/ || mkdir -p src/c2b/
	cd src/c2b/ && ( test -e Makefile.c2blib || $(QMAKE) -o Makefile.c2blib /data/data/com.termux/files/home/cb2bib/src/c2b/c2blib.pro -config use_lz4 ) && $(MAKE) -e -f Makefile.c2blib distdir DISTDIR=$(DISTDIR)/src/c2b

sub-src-distdir: FORCE
	@test -d src/ || mkdir -p src/
	cd src/ && ( test -e Makefile || $(QMAKE) -o Makefile /data/data/com.termux/files/home/cb2bib/src/src.pro -config use_lz4 ) && $(MAKE) -e -f Makefile distdir DISTDIR=$(DISTDIR)/src

