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

SRC_DIR ?= $(CURDIR)
export SRC_DIR

SCRIPT_DIR ?= $(SRC_DIR)/script
export SCRIPT_DIR

BIN_DIR ?= $(SRC_DIR)/bin
export BIN_DIR

# Subdirectories to search
SUB_DIR := ./src/osl/renderman ./src/osl/general #./src/c++/arnold

# Set default target
.DEFAULT_GOAL = all

# Target time stamps to ignore
.PHONY : SUB_DIR $(SUB_DIR) clean $(CLEAN_SUB_DIR)

#-------------------------------------------------------------------------------
# ALL TARGET
#-------------------------------------------------------------------------------
all : $(BIN_DIR) SUB_DIR
SUB_DIR : $(BIN_DIR)

# Check for bin directory
$(BIN_DIR) :
	mkdir -p $(BIN_DIR)

SUB_DIR: $(SUB_DIR)
$(SUB_DIR) : 
	$(MAKE) -C $@

#-------------------------------------------------------------------------------
# CLEAN TARGET
#-------------------------------------------------------------------------------
# Cleans the subdirectories
CLEAN_SUB_DIR = $(addprefix clean_, $(SUB_DIR))

clean_SUB_DIR : $(CLEAN_SUB_DIR)
$(CLEAN_SUB_DIR):
	$(MAKE) -C $(subst clean_,,$@) clean_local

# Clean the bin directory
clean : clean_SUB_DIR
	@ echo "make clean."
	@ -rm -rf $(SRC_DIR)/bin

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
	@ echo "SRC_DIR:     $(SRC_DIR)"
	@ echo "SCRIPT_DIR:  $(SCRIPT_DIR)"
	@ echo "BIN_DIR:     $(BIN_DIR)"
	@ echo "SUB_DIR:    $(SUB_DIR)"
	@ echo "------------------------------------------------------------------------"
