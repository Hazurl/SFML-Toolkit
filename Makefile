# Structure of the project: 
#
# /
#     build/  
#         shared/
#             libproject-name.so
#             src/
#                 object files...
#         static/
#             libproject-name.a
#             src/
#                 object files...
#         executable/
#             project-name
#             src/
#                 object files
#     src/
#         sources files...
#     inc/
#         header files...

# Note: inc and src can be the same folder

#####
##### FOLDER SETTINGS
#####

SRC_FOLDER := src
INC_FOLDER := include

BUILD_FOLDER := build

BUILD_SHARED_FOLDER := $(BUILD_FOLDER)/shared
BUILD_STATIC_FOLDER := $(BUILD_FOLDER)/static
BUILD_EXE_FOLDER := $(BUILD_FOLDER)/executable

#####
##### GENERAL SETTINGS
#####

PROJECT_NAME := sfmltk
CXX := g++
SXX := ar

# Targets
TARGET_SHARED := $(BUILD_SHARED_FOLDER)/lib$(PROJECT_NAME).so
TARGET_STATIC := $(BUILD_STATIC_FOLDER)/lib$(PROJECT_NAME).a
TARGET_EXE := $(BUILD_EXE_FOLDER)/$(PROJECT_NAME)

# Target to build when `make` or `make all` is typed
TARGET_ALL := $(TARGET_STATIC) $(TARGET_SHARED)

#####
##### FILES SETTINGS
#####

# Extension
EXT_SRC_FILE = .cpp
EXT_INC_FILE = .hpp

# Get header from source file
# This function is only used to checks if the header has bee modified and the object file must be rebuild
# So if the header doesn't exist it's ok

# The first argument is the source file relative to $(SRC_FOLDER)
# The header must be relative to $(INC_FOLDER)

# EX: $(1:%$(EXT_SRC_FILE)=%$(EXT_INC_FILE)) 
# will take the file "folder/sub_folder_file.cpp"
# and transform it into "folder/sub_folder_file.hpp"
header-of = $(1:%$(EXT_SRC_FILE)=%$(EXT_INC_FILE))

# Relative to $(SRC_FOLDER)
SRC_EXCLUDE_FILE := 
# All files that are not use for libraries, don't add src/
EXAMPLES := $(shell find $(SRC_FOLDER)/example -name '*$(EXT_SRC_FILE)')
SRC_MAINS := main.cpp $(EXAMPLES:$(SRC_FOLDER)/%=%)
# The main file to use (must be in $(SRC_MAINS))
SRC_MAIN := main.cpp

#####
##### MODULES
#####

#
# [Event]
#

EVENT_SRC := 
EVENT_MAIN := example/eventListener.cpp

TARGET_EVENT_EXE :=$(BUILD_EXE_FOLDER)/eventListener_example
TARGET_EVENT_SHARED :=$(BUILD_SHARED_FOLDER)/libsftkeventListener.so
TARGET_EVENT_STATIC :=$(BUILD_STATIC_FOLDER)/libsftkeventListener.a

EVENT_OBJ_MAIN := $(EVENT_MAIN:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o)
EVENT_OBJ_EXE := $(EVENT_OBJ_MAIN) $(EVENT_SRC:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o) 
EVENT_OBJ_SHARED := $(EVENT_SRC:%$(EXT_SRC_FILE)=$(BUILD_SHARED_FOLDER)/$(SRC_FOLDER)/%.o)
EVENT_OBJ_STATIC := $(EVENT_SRC:%$(EXT_SRC_FILE)=$(BUILD_STATIC_FOLDER)/$(SRC_FOLDER)/%.o)

#
# [Ressource]
#

RESSOURCE_SRC := 
RESSOURCE_MAIN := example/ressource.cpp

TARGET_RESSOURCE_EXE :=$(BUILD_EXE_FOLDER)/ressource_example
TARGET_RESSOURCE_SHARED :=$(BUILD_SHARED_FOLDER)/libsftkressource.so
TARGET_RESSOURCE_STATIC :=$(BUILD_STATIC_FOLDER)/libsftkressource.a

RESSOURCE_OBJ_MAIN := $(RESSOURCE_MAIN:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o)
RESSOURCE_OBJ_EXE := $(RESSOURCE_OBJ_MAIN) $(RESSOURCE_SRC:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o) 
RESSOURCE_OBJ_SHARED := $(RESSOURCE_SRC:%$(EXT_SRC_FILE)=$(BUILD_SHARED_FOLDER)/$(SRC_FOLDER)/%.o)
RESSOURCE_OBJ_STATIC := $(RESSOURCE_SRC:%$(EXT_SRC_FILE)=$(BUILD_STATIC_FOLDER)/$(SRC_FOLDER)/%.o)

#
# [Fancy Text]
#

FANCY_TEXT_SRC := sftk/fancyText/FancyText.cpp
FANCY_TEXT_MAIN := example/fancyText.cpp

TARGET_FANCY_TEXT_EXE :=$(BUILD_EXE_FOLDER)/fancyText_example
TARGET_FANCY_TEXT_SHARED :=$(BUILD_SHARED_FOLDER)/libsftkfancyText.so
TARGET_FANCY_TEXT_STATIC :=$(BUILD_STATIC_FOLDER)/libsftkfancyText.a

FANCY_TEXT_OBJ_MAIN := $(FANCY_TEXT_MAIN:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o)
FANCY_TEXT_OBJ_EXE := $(FANCY_TEXT_OBJ_MAIN) $(FANCY_TEXT_SRC:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o) 
FANCY_TEXT_OBJ_SHARED := $(FANCY_TEXT_SRC:%$(EXT_SRC_FILE)=$(BUILD_SHARED_FOLDER)/$(SRC_FOLDER)/%.o)
FANCY_TEXT_OBJ_STATIC := $(FANCY_TEXT_SRC:%$(EXT_SRC_FILE)=$(BUILD_STATIC_FOLDER)/$(SRC_FOLDER)/%.o)

#
# [Clipper]
#

CLIPPER_SRC := sftk/clipper/Clipper.cpp
CLIPPER_MAIN := example/clipper.cpp

TARGET_CLIPPER_EXE :=$(BUILD_EXE_FOLDER)/clipper_example
TARGET_CLIPPER_SHARED :=$(BUILD_SHARED_FOLDER)/libsftkclipper.so
TARGET_CLIPPER_STATIC :=$(BUILD_STATIC_FOLDER)/libsftkclipper.a

CLIPPER_OBJ_MAIN := $(CLIPPER_MAIN:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o)
CLIPPER_OBJ_EXE := $(CLIPPER_OBJ_MAIN) $(CLIPPER_SRC:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o) 
CLIPPER_OBJ_SHARED := $(CLIPPER_SRC:%$(EXT_SRC_FILE)=$(BUILD_SHARED_FOLDER)/$(SRC_FOLDER)/%.o)
CLIPPER_OBJ_STATIC := $(CLIPPER_SRC:%$(EXT_SRC_FILE)=$(BUILD_STATIC_FOLDER)/$(SRC_FOLDER)/%.o)

#
# [Animated]
#

ANIMATED_SRC := 
ANIMATED_MAIN := example/animated.cpp

TARGET_ANIMATED_EXE :=$(BUILD_EXE_FOLDER)/animated_example
TARGET_ANIMATED_SHARED :=$(BUILD_SHARED_FOLDER)/libsftkanimated.so
TARGET_ANIMATED_STATIC :=$(BUILD_STATIC_FOLDER)/libsftkanimated.a

ANIMATED_OBJ_MAIN := $(ANIMATED_MAIN:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o)
ANIMATED_OBJ_EXE := $(ANIMATED_OBJ_MAIN) $(ANIMATED_SRC:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o) 
ANIMATED_OBJ_SHARED := $(ANIMATED_SRC:%$(EXT_SRC_FILE)=$(BUILD_SHARED_FOLDER)/$(SRC_FOLDER)/%.o)
ANIMATED_OBJ_STATIC := $(ANIMATED_SRC:%$(EXT_SRC_FILE)=$(BUILD_STATIC_FOLDER)/$(SRC_FOLDER)/%.o)

#
# [Gizmo]
#

GIZMO_SRC := 
GIZMO_MAIN := example/gizmo.cpp

TARGET_GIZMO_EXE :=$(BUILD_EXE_FOLDER)/gizmo_example
TARGET_GIZMO_SHARED :=$(BUILD_SHARED_FOLDER)/libsftkgizmo.so
TARGET_GIZMO_STATIC :=$(BUILD_STATIC_FOLDER)/libsftkgizmo.a

GIZMO_OBJ_MAIN := $(GIZMO_MAIN:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o)
GIZMO_OBJ_EXE := $(GIZMO_OBJ_MAIN) $(GIZMO_SRC:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o) 
GIZMO_OBJ_SHARED := $(GIZMO_SRC:%$(EXT_SRC_FILE)=$(BUILD_SHARED_FOLDER)/$(SRC_FOLDER)/%.o)
GIZMO_OBJ_STATIC := $(GIZMO_SRC:%$(EXT_SRC_FILE)=$(BUILD_STATIC_FOLDER)/$(SRC_FOLDER)/%.o)

#
# [QoL]
#

QOL_SRC := 
QOL_MAIN := example/qol.cpp

TARGET_QOL_EXE :=$(BUILD_EXE_FOLDER)/qol_example.cpp
TARGET_QOL_SHARED :=$(BUILD_SHARED_FOLDER)/libsftkqol.so
TARGET_QOL_STATIC :=$(BUILD_STATIC_FOLDER)/libsftkqol.a

QOL_OBJ_MAIN := $(QOL_MAIN:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o)
QOL_OBJ_EXE := $(QOL_OBJ_MAIN) $(QOL_SRC:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o) 
QOL_OBJ_SHARED := $(QOL_SRC:%$(EXT_SRC_FILE)=$(BUILD_SHARED_FOLDER)/$(SRC_FOLDER)/%.o)
QOL_OBJ_STATIC := $(QOL_SRC:%$(EXT_SRC_FILE)=$(BUILD_STATIC_FOLDER)/$(SRC_FOLDER)/%.o)

#
# [HSL Color]
#

HSL_COLOR_SRC := sftk/hslcolor/HSLColor.cpp
HSL_COLOR_MAIN := example/hslcolor.cpp
HSL_COLOR_EXAMPLE_ADDITIONAL_SRC := sftk/print/Printer.cpp

TARGET_HSL_COLOR_EXE :=$(BUILD_EXE_FOLDER)/hslcolor_example
TARGET_HSL_COLOR_SHARED :=$(BUILD_SHARED_FOLDER)/libsftkhslcolor.so
TARGET_HSL_COLOR_STATIC :=$(BUILD_STATIC_FOLDER)/libsftkhslcolor.a

HSL_COLOR_OBJ_MAIN := $(HSL_COLOR_MAIN:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o)
HSL_COLOR_OBJ_EXE := $(HSL_COLOR_OBJ_MAIN) $(HSL_COLOR_EXAMPLE_ADDITIONAL_SRC:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o) $(HSL_COLOR_SRC:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o) 
HSL_COLOR_OBJ_SHARED := $(HSL_COLOR_SRC:%$(EXT_SRC_FILE)=$(BUILD_SHARED_FOLDER)/$(SRC_FOLDER)/%.o)
HSL_COLOR_OBJ_STATIC := $(HSL_COLOR_SRC:%$(EXT_SRC_FILE)=$(BUILD_STATIC_FOLDER)/$(SRC_FOLDER)/%.o)

#
# [Printer]
#

PRINTER_SRC := sftk/print/Printer.cpp
# PRINTER_MAIN := example/Printer.cpp

# TARGET_PRINTER_EXE :=$(BUILD_EXE_FOLDER)/printer_example
TARGET_PRINTER_SHARED :=$(BUILD_SHARED_FOLDER)/libsftkprinter.so
TARGET_PRINTER_STATIC :=$(BUILD_STATIC_FOLDER)/libsftkprinter.a

# PRINTER_OBJ_MAIN := $(PRINTER_MAIN:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o)
# PRINTER_OBJ_EXE := $(PRINTER_OBJ_MAIN) $(PRINTER_SRC:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o) 
PRINTER_OBJ_SHARED := $(PRINTER_SRC:%$(EXT_SRC_FILE)=$(BUILD_SHARED_FOLDER)/$(SRC_FOLDER)/%.o)
PRINTER_OBJ_STATIC := $(PRINTER_SRC:%$(EXT_SRC_FILE)=$(BUILD_STATIC_FOLDER)/$(SRC_FOLDER)/%.o)

#####
##### FLAGS
#####

OPTI := -O2
FLAGS := -std=c++2a  $(OPTI) -pthread
FLAGS += -Wall -Wextra -Wno-pmf-conversions -Wshadow -Wpedantic -Wduplicated-cond -Wduplicated-branches -Wlogical-op 
FLAGS += -Wnull-dereference -Wuseless-cast -Wold-style-cast -Wcast-align -Wcast-qual -Wno-missing-field-initializers 
STATIC_LINK_FLAG := rcs

# Include path
# Must be use with -I
INC_FLAG := -I $(INC_FOLDER)

#####
##### LIBRARY
#####

# Path to libaries if not in $PATH, for example (relative to the project folder): lib/
# Must be use with -L
LIBS_PATH := 

# For example: -lsfml-graphics
LIBS := -lsfml-graphics -lsfml-window -lsfml-system

# Library that require to be build
LIB_TO_BUILD := 

# Create rules to build the libraries


###############################################
#                   PRIVATE                   #
###############################################

#####
##### OTHER
#####

_RESET := \033[0m
_BOLD := \033[1m

_COLOR_RED := \033[31m
_COLOR_GREEN := \033[32m
_COLOR_YELLOW := \033[33m
_COLOR_BLUE := \033[34m
_COLOR_MAGENTA := \033[35m
_COLOR_CYAN := \033[36m
_COLOR_WHITE := \033[37m

SHARED_FLAGS := -fPIC

MAKEFLAGS += --no-print-directory

#####
##### FUNCTIONS
#####

_void =
_space = $(_void) $(_void)
_comma = ,

# join <between> <list>
_join = $(subst $(_space),$(1),$(2))

# _header <message>
_header = echo -e "$(_COLOR_CYAN)$(_BOLD)>>> $(1)$(_RESET)"
# _sub-header <message>
_sub-header = echo -e "$(_COLOR_GREEN)>>> $(1)$(_RESET)"
# _build-msg <target> <from>
_build-msg = echo -e "$(_COLOR_WHITE):: Building $(_BOLD)$(1)$(_RESET)$(_COLOR_WHITE) from $(_BOLD)$(2)$(_RESET)"
# _special <message>
_special = echo -e "$(_COLOR_MAGENTA)$(_BOLD)\# $(1)$(_RESET)"

# not <value>
# return an empty string if value is not
not = $(if $(1),,not-empty-string)

# _remove-folder <folder>
define _remove-folder
	rm -rf $(1)
endef

# _is-empty <value> [<message>]
# example: $(call check-not-empty,FOLDER,The folder must be specified)
_is-empty = $(call not,$(1))
define _is-empty-er
	$(if $(call _is-empty,$(1)),$(error Value is empty $(if $(2),($(2)) )))
endef

# _exists <file> [<message>]
_exists = $(wildcard $(1))
define _exists-er
	$(if $(call _exists,$(1)),,$(error File '$(1)' doesn't exists $(if $(2),($(2)) )))
endef

#####
##### SOURCES
#####

_SRC_MAINS := $(addprefix $(SRC_FOLDER)/,$(SRC_MAINS))
# All sources files not main
_ALL_SRC_FILES := $(shell find $(SRC_FOLDER) -name '*$(EXT_SRC_FILE)')
_SRC_FILES := $(filter-out $(_SRC_MAINS),$(_ALL_SRC_FILES))

#####
##### DIRECTORIES
#####

# All sources file directories
_SRC_DIR := $(sort $(dir $(_ALL_SRC_FILES)))

_EXE_DIR := $(addprefix $(BUILD_EXE_FOLDER)/,$(_SRC_DIR)) 
_SHARED_DIR := $(addprefix $(BUILD_SHARED_FOLDER)/,$(_SRC_DIR))
_STATIC_DIR := $(addprefix $(BUILD_STATIC_FOLDER)/,$(_SRC_DIR))

_BUILD_DIR := $(_EXE_DIR) $(BUILD_EXE_FOLDER) 
_BUILD_DIR += $(BUILD_SHARED_FOLDER) $(_SHARED_DIR) 
_BUILD_DIR += $(BUILD_STATIC_FOLDER) $(_STATIC_DIR)

#####
##### OBJECT FILES
##### 

_OBJ_MAIN := $(SRC_MAIN:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o)
_OBJ_SRC_EXE := $(_OBJ_MAIN) $(_SRC_FILES:%$(EXT_SRC_FILE)=$(BUILD_EXE_FOLDER)/%.o) 

_OBJ_SRC_SHARED := $(_SRC_FILES:%$(EXT_SRC_FILE)=$(BUILD_SHARED_FOLDER)/%.o)

_OBJ_SRC_STATIC := $(_SRC_FILES:%$(EXT_SRC_FILE)=$(BUILD_STATIC_FOLDER)/%.o)

_LIB_PATH_LD := $(call _join,:,$(strip $(filter-out -L,$(LIBS_PATH))))
export LD_LIBRARY_PATH += $(_LIB_PATH_LD)

#####
##### RULES
#####

.PHONY: all executable shared static 
.PHONY: clean clean-executable clean-shared clean-static
.PHONY: re re-executable re-shared re-static
.PHONY: re-run run

.DEFAULT_GOAL := all

all:
ifneq ($(findstring $(TARGET_EXE),$(TARGET_ALL)),)
	@make executable
endif
ifneq ($(findstring $(TARGET_SHARED),$(TARGET_ALL)),)
	@make shared
endif
ifneq ($(findstring $(TARGET_STATIC),$(TARGET_ALL)),)
	@make static
endif

executable: 
	@$(call _header,BUILDING EXECUTABLE...)
	@make $(TARGET_EXE)

shared:
	@$(call _header,BUILDING SHARED LIBRARY...)
	@make $(TARGET_SHARED)

static:
	@$(call _header,BUILDING STATIC LIBRARY...)
	@make $(TARGET_STATIC)

clean:
	@$(call _header,REMOVING $(BUILD_FOLDER))
	@$(call _remove-folder,$(BUILD_FOLDER))

clean-executable:
	@$(call _header,REMOVING $(BUILD_EXE_FOLDER))
	@$(call _remove-folder,$(BUILD_EXE_FOLDER))

clean-shared:
	@$(call _header,REMOVING $(BUILD_SHARED_FOLDER))
	@$(call _remove-folder,$(BUILD_SHARED_FOLDER))

clean-static:
	@$(call _header,REMOVING $(BUILD_STATIC_FOLDER))
	@$(call _remove-folder,$(BUILD_STATIC_FOLDER))

where-executable:
	@echo $(TARGET_EXE)

where-shared:
	@echo $(TARGET_SHARED)

where-static:
	@echo $(TARGET_STATIC)

re:
	@make clean
	@make

re-executable:
	@make clean-executable
	@make executable

re-shared:
	@make clean-shared
	@make shared

re-static:
	@make clean-static
	@make static

run:
	@make executable
	@echo
	@$(call _special,EXECUTING $(TARGET_EXE)...)
	@$(TARGET_EXE) $(args); ERR=$$?; $(call _special,PROGRAM HALT WITH CODE $$ERR); exit $$ERR;

re-run:
	@make re-executable
	@make run

valgrind:
	@make executable
	@echo
	@$(call _special,EXECUTING $(TARGET_EXE) WITH VALGRIND...)
	@valgrind $(TARGET_EXE) $(args); ERR=$$?; $(call _special,PROGRAM HALT WITH CODE $$ERR); exit $$ERR;

re-valgrind:
	@make re-executable
	@make valgrind

eventlistener:
	@$(call _header,BUILDING EVENT LISTENER EXAMPLE...)
	@make $(TARGET_EVENT_EXE)

eventlistener-shared:
	@$(call _header,BUILDING SHARED EVENT LISTENER...)
	@make $(TARGET_EVENT_SHARED)

eventlistener-static:
	@$(call _header,BUILDING STATIC EVENT LISTENER...)
	@make $(TARGET_EVENT_STATIC)

run-eventlistener: 
	@make eventlistener
	@echo
	@$(call _special,EXECUTING $(TARGET_EVENT_EXE)...)
	@$(TARGET_EVENT_EXE) $(args); ERR=$$?; $(call _special,PROGRAM HALT WITH CODE $$ERR); exit $$ERR;

animated:
	@$(call _header,BUILDING ANIMATED LISTENER EXAMPLE...)
	@make $(TARGET_ANIMATED_EXE)

animated-shared:
	@$(call _header,BUILDING SHARED ANIMATED LISTENER...)
	@make $(TARGET_ANIMATED_SHARED)

animated-static:
	@$(call _header,BUILDING STATIC ANIMATED LISTENER...)
	@make $(TARGET_ANIMATED_STATIC)

run-animated: 
	@make animated
	@echo
	@$(call _special,EXECUTING $(TARGET_ANIMATED_EXE)...)
	@$(TARGET_ANIMATED_EXE) $(args); ERR=$$?; $(call _special,PROGRAM HALT WITH CODE $$ERR); exit $$ERR;

gizmo:
	@$(call _header,BUILDING GIZMO LISTENER EXAMPLE...)
	@make $(TARGET_GIZMO_EXE)

gizmo-shared:
	@$(call _header,BUILDING SHARED GIZMO LISTENER...)
	@make $(TARGET_GIZMO_SHARED)

gizmo-static:
	@$(call _header,BUILDING STATIC GIZMO LISTENER...)
	@make $(TARGET_GIZMO_STATIC)

run-gizmo: 
	@make gizmo
	@echo
	@$(call _special,EXECUTING $(TARGET_GIZMO_EXE)...)
	@$(TARGET_GIZMO_EXE) $(args); ERR=$$?; $(call _special,PROGRAM HALT WITH CODE $$ERR); exit $$ERR;

qol:
	@$(call _header,BUILDING QOL LISTENER EXAMPLE...)
	@make $(TARGET_QOL_EXE)

qol-shared:
	@$(call _header,BUILDING SHARED QOL LISTENER...)
	@make $(TARGET_QOL_SHARED)

qol-static:
	@$(call _header,BUILDING STATIC QOL LISTENER...)
	@make $(TARGET_QOL_STATIC)

run-qol: 
	@make qol
	@echo
	@$(call _special,EXECUTING $(TARGET_QOL_EXE)...)
	@$(TARGET_QOL_EXE) $(args); ERR=$$?; $(call _special,PROGRAM HALT WITH CODE $$ERR); exit $$ERR;

ressource:
	@$(call _header,BUILDING RESSOURCE LISTENER EXAMPLE...)
	@make $(TARGET_RESSOURCE_EXE)

ressource-shared:
	@$(call _header,BUILDING SHARED RESSOURCE LISTENER...)
	@make $(TARGET_RESSOURCE_SHARED)

ressource-static:
	@$(call _header,BUILDING STATIC RESSOURCE LISTENER...)
	@make $(TARGET_RESSOURCE_STATIC)

run-ressource: 
	@make ressource
	@echo
	@$(call _special,EXECUTING $(TARGET_RESSOURCE_EXE)...)
	@$(TARGET_RESSOURCE_EXE) $(args); ERR=$$?; $(call _special,PROGRAM HALT WITH CODE $$ERR); exit $$ERR;

fancytext:
	@$(call _header,BUILDING FANCY TEXT EXAMPLE...)
	@make $(TARGET_FANCY_TEXT_EXE)

fancytext-shared:
	@$(call _header,BUILDING SHARED FANCY TEXT...)
	@make $(TARGET_FANCY_TEXT_SHARED)

fancytext-static:
	@$(call _header,BUILDING STATIC FANCY TEXT...)
	@make $(TARGET_FANCY_TEXT_STATIC)

run-fancytext: 
	@make fancytext
	@echo
	@$(call _special,EXECUTING $(TARGET_FANCY_TEXT_EXE)...)
	@$(TARGET_FANCY_TEXT_EXE) $(args); ERR=$$?; $(call _special,PROGRAM HALT WITH CODE $$ERR); exit $$ERR;

clipper:
	@$(call _header,BUILDING CLIPPER EXAMPLE...)
	@make $(TARGET_CLIPPER_EXE)

clipper-shared:
	@$(call _header,BUILDING SHARED CLIPPER...)
	@make $(TARGET_CLIPPER_SHARED)

clipper-static:
	@$(call _header,BUILDING STATIC CLIPPER...)
	@make $(TARGET_CLIPPER_STATIC)

run-clipper: 
	@make clipper
	@echo
	@$(call _special,EXECUTING $(TARGET_CLIPPER_EXE)...)
	@$(TARGET_CLIPPER_EXE) $(args); ERR=$$?; $(call _special,PROGRAM HALT WITH CODE $$ERR); exit $$ERR;

hslcolor:
	@$(call _header,BUILDING HSL COLOR EXAMPLE...)
	@make $(TARGET_HSL_COLOR_EXE)

hslcolor-shared:
	@$(call _header,BUILDING SHARED HSL COLOR...)
	@make $(TARGET_HSL_COLOR_SHARED)

hslcolor-static:
	@$(call _header,BUILDING STATIC HSL COLOR...)
	@make $(TARGET_HSL_COLOR_STATIC)

run-hslcolor: 
	@make hslcolor
	@echo
	@$(call _special,EXECUTING $(TARGET_HSL_COLOR_EXE)...)
	@$(TARGET_HSL_COLOR_EXE) $(args); ERR=$$?; $(call _special,PROGRAM HALT WITH CODE $$ERR); exit $$ERR;

# printer:
# 	@$(call _header,BUILDING PRINTER EXAMPLE...)
# 	@make $(TARGET_PRINTER_EXE)

printer-shared:
	@$(call _header,BUILDING SHARED PRINTER...)
	@make $(TARGET_PRINTER_SHARED)

printer-static:
	@$(call _header,BUILDING STATIC PRINTER...)
	@make $(TARGET_PRINTER_STATIC)

# run-printer: 
# 	@make printer
# 	@echo
# 	@$(call _special,EXECUTING $(TARGET_PRINTER_EXE)...)
# 	@$(TARGET_PRINTER_EXE) $(args); ERR=$$?; $(call _special,PROGRAM HALT WITH CODE $$ERR); exit $$ERR;

$(_BUILD_DIR):
	@mkdir -p $(_BUILD_DIR)

###


$(TARGET_STATIC): $(_BUILD_DIR) $(LIB_TO_BUILD) $(_OBJ_SRC_STATIC)
	@$(call _sub-header,Archiving...)
	@$(SXX) $(STATIC_LINK_FLAG) $(TARGET_STATIC) $(_OBJ_SRC_STATIC)
	@$(call _header,Static library done ($(TARGET_STATIC)))

$(BUILD_STATIC_FOLDER)/$(SRC_FOLDER)/%.o: $(SRC_FOLDER)/%$(EXT_SRC_FILE) $(INC_FOLDER)/$(call header-of,%$(EXT_SRC_FILE))
	@$(call _build-msg,$(notdir $@),$(call _join,$(_comma)$(_space),$(strip $(notdir $< $(wildcard $(word 2,$^))))))
	@$(CXX) -c $(INC_FLAG) $(FLAGS) -o "$@" "$<"


###


$(TARGET_SHARED): $(_BUILD_DIR) $(LIB_TO_BUILD) $(_OBJ_SRC_SHARED)
	@$(call _sub-header,Shared library creation...)
	@$(CXX) $(INC_FLAG) $(FLAGS) -shared -o $(TARGET_SHARED) $(_OBJ_SRC_SHARED) $(LIBS_PATH) $(LIBS)
	@$(call _header,Shared library done ($(TARGET_SHARED)))

$(BUILD_SHARED_FOLDER)/$(SRC_FOLDER)/%.o: $(SRC_FOLDER)/%$(EXT_SRC_FILE) $(INC_FOLDER)/$(call header-of,%$(EXT_SRC_FILE))
	@$(call _build-msg,$(notdir $@),$(call _join,$(_comma)$(_space),$(strip $(notdir $< $(wildcard $(word 2,$^))))))
	@$(CXX) -c $(INC_FLAG) $(FLAGS) $(SHARED_FLAGS) -o "$@" "$<"


###


$(TARGET_EXE): $(_BUILD_DIR) $(LIB_TO_BUILD) $(_OBJ_SRC_EXE)
	@$(call _sub-header,Linking...)
	@$(CXX) $(INC_FLAG) $(FLAGS) $(_OBJ_SRC_EXE) -o "$@" $(LIBS_PATH) $(LIBS)
	@$(call _header,Executable done ($(TARGET_EXE)))

$(BUILD_EXE_FOLDER)/$(SRC_FOLDER)/%.o: $(SRC_FOLDER)/%$(EXT_SRC_FILE) $(INC_FOLDER)/$(call header-of,%$(EXT_SRC_FILE))
	@$(call _build-msg,$(notdir $@),$(call _join,$(_comma)$(_space),$(strip $(notdir $< $(wildcard $(word 2,$^))))))
	@$(CXX) -c $(INC_FLAG) $(FLAGS) -o "$@" "$<"


###


$(TARGET_EVENT_EXE): $(_BUILD_DIR) $(LIB_TO_BUILD) $(EVENT_OBJ_EXE)
	@$(call _sub-header,Linking...)
	@$(CXX) $(INC_FLAG) $(FLAGS) $(EVENT_OBJ_EXE) -o "$@" $(LIBS_PATH) $(LIBS)
	@$(call _header,Executable done ($(EVENT_OBJ_EXE)))

$(TARGET_EVENT_STATIC): $(_BUILD_DIR) $(LIB_TO_BUILD) $(EVENT_OBJ_STATIC)
	@$(call _sub-header,Archiving...)
	@$(SXX) $(STATIC_LINK_FLAG) $(TARGET_EVENT_STATIC) $(EVENT_OBJ_STATIC)
	@$(call _header,Static library done ($(TARGET_EVENT_STATIC)))

$(TARGET_EVENT_SHARED): $(_BUILD_DIR) $(LIB_TO_BUILD) $(EVENT_OBJ_SHARED)
	@$(call _sub-header,Shared library creation...)
	@$(CXX) $(INC_FLAG) $(FLAGS) -shared -o $(TARGET_EVENT_SHARED) $(EVENT_OBJ_SRC_SHARED) $(LIBS_PATH) $(LIBS)
	@$(call _header,Shared library done ($(TARGET_EVENT_SHARED)))



$(TARGET_ANIMATED_EXE): $(_BUILD_DIR) $(LIB_TO_BUILD) $(ANIMATED_OBJ_EXE)
	@$(call _sub-header,Linking...)
	@$(CXX) $(INC_FLAG) $(FLAGS) $(ANIMATED_OBJ_EXE) -o "$@" $(LIBS_PATH) $(LIBS)
	@$(call _header,Executable done ($(ANIMATED_OBJ_EXE)))

$(TARGET_ANIMATED_STATIC): $(_BUILD_DIR) $(LIB_TO_BUILD) $(ANIMATED_OBJ_STATIC)
	@$(call _sub-header,Archiving...)
	@$(SXX) $(STATIC_LINK_FLAG) $(TARGET_ANIMATED_STATIC) $(ANIMATED_OBJ_STATIC)
	@$(call _header,Static library done ($(TARGET_ANIMATED_STATIC)))

$(TARGET_ANIMATED_SHARED): $(_BUILD_DIR) $(LIB_TO_BUILD) $(ANIMATED_OBJ_SHARED)
	@$(call _sub-header,Shared library creation...)
	@$(CXX) $(INC_FLAG) $(FLAGS) -shared -o $(TARGET_ANIMATED_SHARED) $(ANIMATED_OBJ_SRC_SHARED) $(LIBS_PATH) $(LIBS)
	@$(call _header,Shared library done ($(TARGET_ANIMATED_SHARED)))

$(TARGET_GIZMO_EXE): $(_BUILD_DIR) $(LIB_TO_BUILD) $(GIZMO_OBJ_EXE)
	@$(call _sub-header,Linking...)
	@$(CXX) $(INC_FLAG) $(FLAGS) $(GIZMO_OBJ_EXE) -o "$@" $(LIBS_PATH) $(LIBS)
	@$(call _header,Executable done ($(GIZMO_OBJ_EXE)))

$(TARGET_GIZMO_STATIC): $(_BUILD_DIR) $(LIB_TO_BUILD) $(GIZMO_OBJ_STATIC)
	@$(call _sub-header,Archiving...)
	@$(SXX) $(STATIC_LINK_FLAG) $(TARGET_GIZMO_STATIC) $(GIZMO_OBJ_STATIC)
	@$(call _header,Static library done ($(TARGET_GIZMO_STATIC)))

$(TARGET_GIZMO_SHARED): $(_BUILD_DIR) $(LIB_TO_BUILD) $(GIZMO_OBJ_SHARED)
	@$(call _sub-header,Shared library creation...)
	@$(CXX) $(INC_FLAG) $(FLAGS) -shared -o $(TARGET_GIZMO_SHARED) $(GIZMO_OBJ_SRC_SHARED) $(LIBS_PATH) $(LIBS)
	@$(call _header,Shared library done ($(TARGET_GIZMO_SHARED)))



$(TARGET_QOL_EXE): $(_BUILD_DIR) $(LIB_TO_BUILD) $(QOL_OBJ_EXE)
	@$(call _sub-header,Linking...)
	@$(CXX) $(INC_FLAG) $(FLAGS) $(QOL_OBJ_EXE) -o "$@" $(LIBS_PATH) $(LIBS)
	@$(call _header,Executable done ($(QOL_OBJ_EXE)))

$(TARGET_QOL_STATIC): $(_BUILD_DIR) $(LIB_TO_BUILD) $(QOL_OBJ_STATIC)
	@$(call _sub-header,Archiving...)
	@$(SXX) $(STATIC_LINK_FLAG) $(TARGET_QOL_STATIC) $(QOL_OBJ_STATIC)
	@$(call _header,Static library done ($(TARGET_QOL_STATIC)))

$(TARGET_QOL_SHARED): $(_BUILD_DIR) $(LIB_TO_BUILD) $(QOL_OBJ_SHARED)
	@$(call _sub-header,Shared library creation...)
	@$(CXX) $(INC_FLAG) $(FLAGS) -shared -o $(TARGET_QOL_SHARED) $(QOL_OBJ_SRC_SHARED) $(LIBS_PATH) $(LIBS)
	@$(call _header,Shared library done ($(TARGET_QOL_SHARED)))



$(TARGET_RESSOURCE_EXE): $(_BUILD_DIR) $(LIB_TO_BUILD) $(RESSOURCE_OBJ_EXE)
	@$(call _sub-header,Linking...)
	@$(CXX) $(INC_FLAG) $(FLAGS) $(RESSOURCE_OBJ_EXE) -o "$@" $(LIBS_PATH) $(LIBS)
	@$(call _header,Executable done ($(RESSOURCE_OBJ_EXE)))

$(TARGET_RESSOURCE_STATIC): $(_BUILD_DIR) $(LIB_TO_BUILD) $(RESSOURCE_OBJ_STATIC)
	@$(call _sub-header,Archiving...)
	@$(SXX) $(STATIC_LINK_FLAG) $(TARGET_RESSOURCE_STATIC) $(RESSOURCE_OBJ_STATIC)
	@$(call _header,Static library done ($(TARGET_RESSOURCE_STATIC)))

$(TARGET_RESSOURCE_SHARED): $(_BUILD_DIR) $(LIB_TO_BUILD) $(RESSOURCE_OBJ_SHARED)
	@$(call _sub-header,Shared library creation...)
	@$(CXX) $(INC_FLAG) $(FLAGS) -shared -o $(TARGET_RESSOURCE_SHARED) $(RESSOURCE_OBJ_SRC_SHARED) $(LIBS_PATH) $(LIBS)
	@$(call _header,Shared library done ($(TARGET_RESSOURCE_SHARED)))



$(TARGET_FANCY_TEXT_EXE): $(_BUILD_DIR) $(LIB_TO_BUILD) $(FANCY_TEXT_OBJ_EXE)
	@$(call _sub-header,Linking...)
	@$(CXX) $(INC_FLAG) $(FLAGS) $(FANCY_TEXT_OBJ_EXE) -o "$@" $(LIBS_PATH) $(LIBS)
	@$(call _header,Executable done ($(FANCY_TEXT_OBJ_EXE)))

$(TARGET_FANCY_TEXT_STATIC): $(_BUILD_DIR) $(LIB_TO_BUILD) $(FANCY_TEXT_OBJ_STATIC)
	@$(call _sub-header,Archiving...)
	@$(SXX) $(STATIC_LINK_FLAG) $(TARGET_FANCY_TEXT_STATIC) $(FANCY_TEXT_OBJ_STATIC)
	@$(call _header,Static library done ($(TARGET_FANCY_TEXT_STATIC)))

$(TARGET_FANCY_TEXT_SHARED): $(_BUILD_DIR) $(LIB_TO_BUILD) $(FANCY_TEXT_OBJ_SHARED)
	@$(call _sub-header,Shared library creation...)
	@$(CXX) $(INC_FLAG) $(FLAGS) -shared -o $(TARGET_FANCY_TEXT_SHARED) $(FANCY_TEXT_OBJ_SRC_SHARED) $(LIBS_PATH) $(LIBS)
	@$(call _header,Shared library done ($(TARGET_FANCY_TEXT_SHARED)))



$(TARGET_CLIPPER_EXE): $(_BUILD_DIR) $(LIB_TO_BUILD) $(CLIPPER_OBJ_EXE)
	@$(call _sub-header,Linking...)
	@$(CXX) $(INC_FLAG) $(FLAGS) $(CLIPPER_OBJ_EXE) -o "$@" $(LIBS_PATH) $(LIBS)
	@$(call _header,Executable done ($(CLIPPER_OBJ_EXE)))

$(TARGET_CLIPPER_STATIC): $(_BUILD_DIR) $(LIB_TO_BUILD) $(CLIPPER_OBJ_STATIC)
	@$(call _sub-header,Archiving...)
	@$(SXX) $(STATIC_LINK_FLAG) $(TARGET_CLIPPER_STATIC) $(CLIPPER_OBJ_STATIC)
	@$(call _header,Static library done ($(TARGET_CLIPPER_STATIC)))

$(TARGET_CLIPPER_SHARED): $(_BUILD_DIR) $(LIB_TO_BUILD) $(CLIPPER_OBJ_SHARED)
	@$(call _sub-header,Shared library creation...)
	@$(CXX) $(INC_FLAG) $(FLAGS) -shared -o $(TARGET_CLIPPER_SHARED) $(CLIPPER_OBJ_SRC_SHARED) $(LIBS_PATH) $(LIBS)
	@$(call _header,Shared library done ($(TARGET_CLIPPER_SHARED)))



$(TARGET_HSL_COLOR_EXE): $(_BUILD_DIR) $(LIB_TO_BUILD) $(HSL_COLOR_OBJ_EXE)
	@$(call _sub-header,Linking...)
	@$(CXX) $(INC_FLAG) $(FLAGS) $(HSL_COLOR_OBJ_EXE) -o "$@" $(LIBS_PATH) $(LIBS)
	@$(call _header,Executable done ($(HSL_COLOR_OBJ_EXE)))

$(TARGET_HSL_COLOR_STATIC): $(_BUILD_DIR) $(LIB_TO_BUILD) $(HSL_COLOR_OBJ_STATIC)
	@$(call _sub-header,Archiving...)
	@$(SXX) $(STATIC_LINK_FLAG) $(TARGET_HSL_COLOR_STATIC) $(HSL_COLOR_OBJ_STATIC)
	@$(call _header,Static library done ($(TARGET_HSL_COLOR_STATIC)))

$(TARGET_HSL_COLOR_SHARED): $(_BUILD_DIR) $(LIB_TO_BUILD) $(HSL_COLOR_OBJ_SHARED)
	@$(call _sub-header,Shared library creation...)
	@$(CXX) $(INC_FLAG) $(FLAGS) -shared -o $(TARGET_HSL_COLOR_SHARED) $(HSL_COLOR_OBJ_SRC_SHARED) $(LIBS_PATH) $(LIBS)
	@$(call _header,Shared library done ($(TARGET_HSL_COLOR_SHARED)))



$(TARGET_PRINTER_EXE): $(_BUILD_DIR) $(LIB_TO_BUILD) $(PRINTER_OBJ_EXE)
	@$(call _sub-header,Linking...)
	@$(CXX) $(INC_FLAG) $(FLAGS) $(PRINTER_OBJ_EXE) -o "$@" $(LIBS_PATH) $(LIBS)
	@$(call _header,Executable done ($(PRINTER_OBJ_EXE)))

$(TARGET_PRINTER_STATIC): $(_BUILD_DIR) $(LIB_TO_BUILD) $(PRINTER_OBJ_STATIC)
	@$(call _sub-header,Archiving...)
	@$(SXX) $(STATIC_LINK_FLAG) $(TARGET_PRINTER_STATIC) $(PRINTER_OBJ_STATIC)
	@$(call _header,Static library done ($(TARGET_PRINTER_STATIC)))

$(TARGET_PRINTER_SHARED): $(_BUILD_DIR) $(LIB_TO_BUILD) $(PRINTER_OBJ_SHARED)
	@$(call _sub-header,Shared library creation...)
	@$(CXX) $(INC_FLAG) $(FLAGS) -shared -o $(TARGET_PRINTER_SHARED) $(PRINTER_OBJ_SRC_SHARED) $(LIBS_PATH) $(LIBS)
	@$(call _header,Shared library done ($(TARGET_PRINTER_SHARED)))



# Just to avoid file without headers
%$(EXT_INC_FILE):
	
