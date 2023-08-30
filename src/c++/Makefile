#-------------------------------------------------------------------------------
# PRE PROCESS
#-------------------------------------------------------------------------------
ifndef ARNOLD_PATH
	$(error ARNOLD_PATH needs to be set.)
endif

# Define variables if Makefile was not called recursively
SRC_DIR ?= ../../..
BIN_DIR ?= $(SRC_DIR)/bin

INSTALL_DIR := $(BIN_DIR)/c++/arnold

# Subdirectories to search
SUBDIRS := arnold

# Set default target
.DEFAULT_GOAL = all

# Target time stamps to ignore
.PHONY : all install

src := $(foreach dir, $(SUBDIRS), $(wildcard $(dir)/*.cpp))

#-------------------------------------------------------------------------------
# ALL TARGET
#-------------------------------------------------------------------------------
all : install

install : $(INSTALL_DIR)
$(INSTALL_DIR) :
	@ mkdir -p $(INSTALL_DIR)

# Compiler settings
CC = "${RMANTREE}/bin/oslc.exe" # "" & .exe used for wsl implementation

# cl /LD simple_shader.cpp /I %ARNOLD_PATH%\include %ARNOLD_PATH%\lib\ai.lib /link /out:simple_shader.dll

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