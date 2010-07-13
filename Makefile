#############################################################################
# Makefile for building: shashki
# Generated by qmake (2.01a) (Qt 4.6.2) on: Tue Jul 13 16:07:18 2010
# Project:  shashki.pro
# Template: subdirs
# Command: /usr/bin/qmake -unix -o Makefile shashki.pro
#############################################################################

first: make_default
MAKEFILE      = Makefile
QMAKE         = /usr/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
SUBTARGETS    =  \
		sub-src

src/$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) src/ || $(MKDIR) src/ 
	cd src/ && $(QMAKE) /home/imperator/shashki/shashki-0.1/src/src.pro -unix -o $(MAKEFILE)
sub-src-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) src/ || $(MKDIR) src/ 
	cd src/ && $(QMAKE) /home/imperator/shashki/shashki-0.1/src/src.pro -unix -o $(MAKEFILE)
sub-src: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE)
sub-src-make_default: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE) 
sub-src-make_first: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE) first
sub-src-all: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE) all
sub-src-clean: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE) clean
sub-src-distclean: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE) distclean
sub-src-install_subtargets: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE) install
sub-src-uninstall_subtargets: src/$(MAKEFILE) FORCE
	cd src/ && $(MAKE) -f $(MAKEFILE) uninstall

Makefile: shashki.pro  /targets/FREMANTLE_X86/usr/share/qt4/mkspecs/linux-g++/qmake.conf /targets/FREMANTLE_X86/usr/share/qt4/mkspecs/common/g++.conf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/common/unix.conf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/common/linux.conf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/qconfig.pri \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/qt_config.prf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/default_pre.prf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/release.prf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/default_post.prf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/warn_on.prf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/qt.prf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/moc.prf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/resources.prf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/uic.prf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/yacc.prf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/lex.prf \
		/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/include_source_dir.prf
	$(QMAKE) -unix -o Makefile shashki.pro
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/common/g++.conf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/common/unix.conf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/common/linux.conf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/qconfig.pri:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/qt_functions.prf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/qt_config.prf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/default_pre.prf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/release.prf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/default_post.prf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/warn_on.prf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/qt.prf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/unix/thread.prf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/moc.prf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/resources.prf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/uic.prf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/yacc.prf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/lex.prf:
/targets/FREMANTLE_X86/usr/share/qt4/mkspecs/features/include_source_dir.prf:
qmake: qmake_all FORCE
	@$(QMAKE) -unix -o Makefile shashki.pro

qmake_all: sub-src-qmake_all FORCE

make_default: sub-src-make_default FORCE
make_first: sub-src-make_first FORCE
all: sub-src-all FORCE
clean: sub-src-clean FORCE
distclean: sub-src-distclean FORCE
	-$(DEL_FILE) Makefile
install_subtargets: sub-src-install_subtargets FORCE
uninstall_subtargets: sub-src-uninstall_subtargets FORCE

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all
install: install_subtargets  FORCE

uninstall:  uninstall_subtargets FORCE

FORCE:

