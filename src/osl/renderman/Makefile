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
SRC_DIR ?= ../../..
SCRIPT_DIR ?= $(SRC_DIR)/script
BIN_DIR ?= $(SRC_DIR)/bin

INSTALL_DIR := $(BIN_DIR)/Renderman-${RMAN_VERSION}

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

install : $(INSTALL_DIR)
$(INSTALL_DIR) :
	@ mkdir -p $(INSTALL_DIR)

# Compiler settings
CC = "${RMANTREE}/bin/oslc.exe" # "" & .exe used for wsl implementation

%.oso : %.osl
	$(CC) -o $@ $<
	env python3 $(SCRIPT_DIR)/install_shaders.py --copy $(INSTALL_DIR) $@

#-------------------------------------------------------------------------------
# CLEAN TARGET
#-------------------------------------------------------------------------------
clean_local:
	@ echo "osl directory clean."
	@ -rm -f $(shell find -L . -name "*.oso" -print)

clean: clean_local
	@ -rm -f $(shell find -L $(INSTALL_DIR) -name "*.oso" -print)

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
	@ echo "SCRIPT_DIR:  $(SCRIPT_DIR)"
	@ echo "BIN_DIR:     $(BIN_DIR)"
	@ echo "INSTALL_DIR:  $(INSTALL_DIR)"
	@ echo "------------------------------------------------------------------------"