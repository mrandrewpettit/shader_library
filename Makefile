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

SRCDIR ?= $(CURDIR)
export SRCDIR

SCRIPTDIR ?= $(SRCDIR)/script
export SCRIPTDIR

BINDIR ?= $(SRCDIR)/bin
export BINDIR

# Subdirectories to search
SUBDIRS := ./src/osl

# Set default target
.DEFAULT_GOAL = all

# Target time stamps to ignore
.PHONY : subdirs $(SUBDIRS) clean $(CLEAN_SUBDIRS)

#-------------------------------------------------------------------------------
# ALL TARGET
#-------------------------------------------------------------------------------
all : $(BINDIR) subdirs
subdirs : $(BINDIR)

# Check for bin directory
$(BINDIR) :
	mkdir -p $(BINDIR)

subdirs: $(SUBDIRS)
$(SUBDIRS) : 
	$(MAKE) -C $@

#-------------------------------------------------------------------------------
# CLEAN TARGET
#-------------------------------------------------------------------------------
# Cleans the subdirectories
CLEAN_SUBDIRS = $(addprefix clean_, $(SUBDIRS))

clean_subdirs : $(CLEAN_SUBDIRS)
$(CLEAN_SUBDIRS):
	$(MAKE) -C $(subst clean_,,$@) clean_local

# Clean the bin directory
clean : clean_subdirs
	@ echo "make clean."
	@ -rm -rf $(SRCDIR)/bin

#-------------------------------------------------------------------------------
# HELP TARGET
#-------------------------------------------------------------------------------

help :
	@ echo "------------------------------------------------------------------------"
	@ echo "PIXAR_ROOT must be set to the location of the RenderMan installation:"
	@ echo "e.g. /opt/pixar"
	@ echo "RMAN_VERSION can also be set to the RenderMan version you wish to make:"
	@ echo "e.g. 25.0"
	@ echo ""
	@ echo "Current settings:"
	@ echo "PIXAR_ROOT: $(PIXAR_ROOT)"
	@ echo "RMAN_VERSION:  $(RMAN_VERSION)"
	@ echo "SRCDIR:     $(SRCDIR)"
	@ echo "SCRIPTDIR:  $(SCRIPTDIR)"
	@ echo "BINDIR:     $(BINDIR)"
	@ echo "SUBDIRS:    $(SUBDIRS)"
	@ echo "------------------------------------------------------------------------"
