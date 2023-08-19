# visit https://makefiletutorial.com/ for great Makefile explanations
#-------------------------------------------------------------------------------
# PRE PROCESS
#-------------------------------------------------------------------------------
# Windows: e.g. C:\Program Files\Pixar
# Linux: e.g. /opt/pixar
ifndef PIXAR_ROOT
	$(error PIXAR_ROOT needs to be set.)
endif
ifndef RMAN_VERSION
	$(error RMAN_VERSION needs to be set.)
endif
ifndef RMANTREE
	$(error RMANTREE needs to be set.)
endif

# Define variables if Makefile was not called recursively
SRCDIR ?= ../..
SCRIPTDIR ?= $(SRCDIR)/script
BINDIR ?= $(SRCDIR)/bin

INSTALLDIR := $(BINDIR)/Renderman-${RMAN_VERSION}

# Subdirectories to search
SUBDIRS := utility

# Set default target
.DEFAULT_GOAL = all

# Target time stamps to ignore
.PHONY : all install # clean 

src := $(foreach dir, $(SUBDIRS), $(wildcard $(dir)/*.osl))
oso := $(src:%.osl=%.oso)

#-------------------------------------------------------------------------------
# ALL TARGET
#-------------------------------------------------------------------------------
all : install $(oso)

install : $(INSTALLDIR)
$(INSTALLDIR) :
	@ mkdir -p $(INSTALLDIR)

# Compiler settings
CC = "${RMANTREE}/bin/oslc.exe" # "" & .exe used for wsl implementation

%.oso : %.osl
	$(CC) -o $@ $<
	env python3 $(SCRIPTDIR)/install_shaders.py --copy $(INSTALLDIR) $@

#-------------------------------------------------------------------------------
# CLEAN TARGET
#-------------------------------------------------------------------------------
clean_local:
	@ echo "osl directory clean."
	@ -rm -f $(shell find -L . -name "*.oso" -print)

clean: clean_local
	@ -rm -f $(shell find -L $(INSTALLDIR) -name "*.oso" -print)

#-------------------------------------------------------------------------------
# HELP TARGET
#-------------------------------------------------------------------------------

help:
	@ echo "------------------------------------------------------------------------"
	@ echo "PIXAR_ROOT must be set: e.g. /opt/pixar"
	@ echo "RMAN_VERSION must be set: e.g. 25.0"
	@ echo ""
	@ echo "Current settings:"
	@ echo "PIXAR_ROOT: $(PIXAR_ROOT)"
	@ echo "RMAN_VERSION: $(RMAN_VERSION)"
	@ echo "RMANTREE:   $(RMANTREE)"
	@ echo "CURDIR:     $(CURDIR)"
	@ echo "SCRIPTDIR:  $(SCRIPTDIR)"
	@ echo "BINDIR:     $(BINDIR)"
	@ echo "INSTALLDIR:  $(INSTALLDIR)"
	@ echo "------------------------------------------------------------------------"