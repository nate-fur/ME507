#--------------------------------------------------------------------------------------
# File:    Makefile for an AVR project
#          The makefile is the standard way to control the compilation and linking of 
#          C/C++ files into an executable file. This makefile is also used to control
#          the downloading of the executable file to the target processor and the 
#          generation of documentation for the project. 
#
# Version:  4-11-2004 JRR Original file
#           6-19-2006 JRR Modified to use AVR-JTAG-ICE for debugging
#          11-21-2008 JRR Added memory locations and removed extras for bootloader
#          11-26-2008 JRR Cleaned up; changed method of choosing programming method
#          11-14-2009 JRR Added make support to put library files into subdirectory
#           9-28-2012 JRR Restructured to work with FreeRTOS subdirectory
#
# Relies   The avr-gcc compiler and avr-libc library
# on:      The avrdude downloader, if downloading through an ISP port
#          AVR-Insight or DDD and avarice, if debugging with the JTAG port
#          Doxygen, for automatic documentation generation
#
# Copyright 2006-2015 by JR Ridgely.  This makefile is intended for use in educational 
# courses only, but its use is not restricted thereto. It is released under the terms 
# of the Lesser GNU Public License with no warranty whatsoever, not even an implied
# warranty of merchantability or fitness for any particular purpose. Anyone who uses 
# this file agrees to take all responsibility for any and all consequences of that use. 
#--------------------------------------------------------------------------------------

# The name of the program you're building, without its extension. The name is used for
# the downloadable and map files, which are mostly worked with automatically
PROJECT_NAME = lab1

# A list of the source (.c, .cc, .cpp) files in the project. Files in library 
# subdirectories do not go in this list; they're included automatically
SOURCES = main.cpp task_user.cpp task_brightness.cpp adc.cpp

# Clock frequency of the CPU, in Hz. This number should be an unsigned long integer.
# For example, 16 MHz would be represented as 16000000UL. 
F_CPU = 16000000UL

# These codes are used to switch on debugging modes if they're being used. Several can
# be placed on the same line together to activate multiple debugging tricks at once.
# -DSERIAL_DEBUG       For general debugging through a serial device
# -DTRANSITION_TRACE   For printing state transition traces on a serial device
# -DTASK_PROFILE       For doing profiling, measurement of how long tasks take to run
# -DUSE_HEX_DUMPS      Include functions for printing hex-formatted memory dumps
OTHERS = -DSERIAL_DEBUG

# If the code -DTASK_SETUP_AND_LOOP is specified, ME405/FreeRTOS tasks classes will be
# required to provide methods setup() and loop(). Otherwise, they must only provide a
# a method called run() which is called just once by the scheduler.
OTHERS += 

# Other codes, used for turning on special features in a given project, can be put here
# -DSWOOP_BOARD        Tells the nRF24L01 radio driver to set up for the Swoop 1 board
# -DME405_BOARD_V05    Sets up radio driver for old ME405 board with 1 motor driver
# -DME405_BOARD_V06    Sets up radio driver for new ME405 board with 2 motor drivers
# -DME405_BREADBOARD   Sets up radio driver for ATmegaXX 40-pin on breadboard
# -DPOLYDAQ_BOARD      Sets up radio and other stuff for a PolyDAQ board
OTHERS += -DME405_BOARD_V06

# This define is used to choose the type of programmer from the following options: 
# bsd        - Parallel port in-system (ISP) programmer using SPI interface on AVR
# jtagice    - Serial or USB interface JTAG-ICE mk I clone from ETT or Olimex
# bootloader - Resident program in the AVR which downloads through USB/serial port
# PROG = bsd
# PROG = jtagice
# PROG = bootloader
PROG = usbtiny

# This section specifies the type of CPU; uncomment one line for your processor. To add
# a new chip to the file, put its designation here and make a fuse bytes section below
# MCU = atmega128
MCU = atmega1281
# MCU = atmega32
# MCU = atmega324p
# MCU = atmega328p
# MCU = atmega644
# MCU = atmega644p
# MCU = atmega1284p

# These defines specify the ports to which the downloader device is connected. 
# PPORT is for "bsd" on a parallel port, lpt1 on Windows or /dev/parport0 on Linux.
# JPORT is for "jtagice" on a serial port such as com1 or /dev/ttyS0, or usb-serial 
#       such as com4 or /dev/ttyUSB1, or aliased serial port such as /dev/avrjtag
# BPORT is for "bootloader", the USB/serial port program downloader on the AVR
# The usbtiny programmer doesn't need a port specification; it has a USB identifier
PPORT = /dev/parport0
JPORT = /dev/ttyUSB1
BPORT = /dev/ttyUSB0

#######################################################################################
################ End of the stuff the user is expected to need to change ##############

# In this section, default settings for fuse bytes are given for each processor which 
# this makefile supports. New chip specifications can be added to this file as needed. 

# ATmega128 set up for ME405 board with JTAG enabled
ifeq ($(MCU), atmega128)
  EFUSE = 0xFF
  HFUSE = 0x11
  LFUSE = 0xEF
# ATmega1281 set up for ME405 board with JTAG disabled
else ifeq ($(MCU), atmega1281)
  EFUSE = 0xFF
  HFUSE = 0xD1
  LFUSE = 0xEF
# ATmega32 configured for Swoop sensor board with JTAG disabled to save power
else ifeq ($(MCU), atmega32)
  EFUSE = 
  HFUSE = 0x99
  LFUSE = 0xEF
# ATmega324P configured for Swoop sensor board with JTAG disabled
# Standard fuses FF19EF, bootloader fuses FFC8EF, low power fuses FF11EF
else ifeq ($(MCU), atmega324p)
  EFUSE = 0xFF
  HFUSE = 0x11
  LFUSE = 0xEF
# ATmega328P configured for Super Ministrone board
# Standard fuses FF19EF, bootloader fuses FFC8EF, low power fuses FF11EF
else ifeq ($(MCU), atmega328p)
  EFUSE = 0x07
  HFUSE = 0xD1
  LFUSE = 0xEF
# ATmega644 (note: the 644P needs a different MCU)
else ifeq ($(MCU), atmega644)
  EFUSE = 0xFF
  HFUSE = 0x11
  LFUSE = 0xEF
# ATmega644P configured for Swoop-2 sensor board
# Standard fuses FF19EF, bootloader fuses FFC8EF, low power fuses FF11EF, JTAG OFF!
else ifeq ($(MCU), atmega644p)
  EFUSE = 0xFF
  HFUSE = 0xD1
  LFUSE = 0xEF
# ATmega1284P configured for Swoop sensor board
# Standard fuses FF19EF, bootloader fuses FFC8EF, low power fuses FF11EF
else ifeq ($(MCU), atmega1284p)
  EFUSE = 0xFF
  HFUSE = 0xD1
  LFUSE = 0xEF
endif

# We need a name for the root directory under which all our project files are found
PROJROOT = ..

# Location of the root of the library part of the directory tree
LIBROOT = lib

# An automatically created and maintained subdirectory in which compiled files will go
BUILDDIR = build

# This is the name of the library file which will hold object code which has been
# compiled from all the source files in the library subdirectories
LIB_FILE = $(BUILDDIR)/lib_me405.a

# A list of directories in which source files (*.cpp, *.c) and headers (.h) for the
# library are kept
LIB_DIRS = freertos frtcpp misc serial

# Create a list of relative path names by which the library directories can be found
LIB_FULL = $(addprefix $(PROJROOT)/$(LIBROOT)/, $(LIB_DIRS))

# Make a list of include directories, putting -I in front of each for the compiler
LIB_INC  = $(addprefix "-I", $(LIB_FULL))

# Make a list of source files from the source files in subdirectories in LIB_DIRS
LIB_SRC  = $(foreach A_DIR, $(LIB_FULL), \
             $(wildcard $(A_DIR)/*.cpp $(A_DIR)/*.c $(A_DIR)/*.S))

# The bare file names are needed by the compiler to find files in the virtual path
LIB_BARE = $(notdir $(LIB_SRC))

# Make a list of the object files which need to be compiled from the source files. The
# compiled files will go into a mirror image of the library tree which is under the
# build directory
LIB_TEMP = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(LIB_BARE))))
LIB_OBJS = $(subst $(PROJROOT), $(BUILDDIR), $(LIB_TEMP))

# Specify virtual paths in which the source files can be found
vpath %.cpp $(LIB_FULL)
vpath %.c $(LIB_FULL)
vpath %.S $(LIB_FULL)

#--------------------------------------------------------------------------------------
# Give some short names to the ELF, HEX, and BIN format output files
ELF = $(BUILDDIR)/$(PROJECT_NAME).elf
HEX = $(BUILDDIR)/$(PROJECT_NAME).hex
BIN = $(BUILDDIR)/$(PROJECT_NAME).bin

#--------------------------------------------------------------------------------------
# List the various programs which are used to compile, link, archive, etc. 
ARCHIE  = avr
CC      = $(ARCHIE)-gcc
CXX     = $(ARCHIE)-g++
LD      = $(ARCHIE)-g++
AR      = $(ARCHIE)-ar
OBJCOPY = $(ARCHIE)-objcopy
GDB     = $(ARCHIE)-gdb
SIZER   = $(ARCHIE)-size
DUDE    = avrdude
ICE     = avarice

#--------------------------------------------------------------------------------------
# Tell the compiler how hard to try to optimize the code. Optimization levels are:
# -O0  Don't try to optimize anything (even leaves empty delay loops in)
# -O1  Some optimizations; code usually smaller and faster than O0
# -O2  Pretty high level of optimization; often good compromise of speed and size
# -O3  Tries really hard to make code run fast, even if code size gets pretty big
# -Os  Tries to make code size small. Sometimes -O1 makes it smaller, though(?!)
OPTIM = -O2

# Warnings which need to be given
C_WARNINGS = -Wall -Wextra -Wshadow -Wpointer-arith -Wbad-function-cast -Wcast-align \
             -Wsign-compare -Wstrict-prototypes -Wmissing-prototypes -Wunused \
             -Wmissing-declarations -Waggregate-return 

CPP_WARNINGS = -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-align -Wsign-compare \
               -Wmissing-declarations -Wunused

# Various compiler options which are common to both the C and C++ compilers
BASE_FLAGS = -mmcu=$(MCU) -D GCC_MEGA_AVR -D F_CPU=$(F_CPU) -D _GNU_SOURCE \
             -fsigned-char -funsigned-bitfields -fshort-enums \
             -g $(OPTIM) $(OTHERS) $(LIB_INC) -lm

# All the options used when compiling C code
C_FLAGS = $(BASE_FLAGS) -fpack-struct -std=gnu99 $(C_WARNINGS)

# All the options used when compiling C++ code
CPP_FLAGS = $(BASE_FLAGS) $(CPP_WARNINGS)

# Make a list of the object files which need to be compiled from the source files
OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

# Specify virtual paths in which the source files can be found
vpath %.cpp $(LIB_FULL)
vpath %.c $(LIB_FULL)

#=================================== THE RULES ========================================
# Inference rules show how to process each kind of file. 

# Rules to make downloadable binary files in ELF (which contains debugging 
# information), BIN (pure binary machine code), and HEX (text binary) formats
$(BIN): $(ELF)
	@$(OBJCOPY) -O binary $< $@

$(HEX): $(ELF)
	@$(OBJCOPY) -j .text -j .data -O ihex $< $@

$(ELF): $(LIB_FILE) $(OBJECTS)
	@echo "Linking:     " $(OBJECTS) $(LIB_FILE) " --> " $@
	@$(LD) $(BASE_FLAGS) $(OBJECTS) $(LIB_FILE) -o $@
	@$(SIZER) $@

# Auto-generate dependency info for existing .o files
-include $(OBJECTS:.o=.d)

# Rules to compile and assemble source code into object code. An image of each source
# directory is created under the build directory and object files are put there
$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling:   " $< " --> " $@
	@$(CC) -c $(C_FLAGS) -MMD -MP -MF $(BUILDDIR)/$(*F).d $< -o $@

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling:   " $< " --> " $@
	@$(CXX) -c $(CPP_FLAGS) -MMD -MP -MF $(BUILDDIR)/$(*F).d $< -o $@

$(BUILDDIR)/%.o: %.S
	@mkdir -p $(dir $@)
	@echo "Assembling:  " $< " --> " $@
	@$(CC) -c $(C_FLAGS) -MMD -MP -MF $(BUILDDIR)/$(*F).d $< -o $@

# This rule will build the library file from all the .o files in the library folders
$(LIB_FILE): $(LIB_OBJS)
	@echo "Library-ing:  (*.o) --> " $@
	@$(AR) -c -r $@ $(LIB_OBJS)

#==================================== TARGETS =========================================

# Make the main target of this project.  This target is invoked when the user types 
# 'make' as opposed to 'make <target>.'  This must be the first target in Makefile.

all: $(HEX) $(BIN)

#--------------------------------------------------------------------------------------
# 'make install' will make the project, then download the program using whichever 
# method has been selected -- ISP cable, JTAG-ICE module, or USB/serial bootloader

install:  $(ELF) $(BIN) $(HEX)
  ifeq ($(PROG), bsd)
	$(DUDE) -p $(MCU) -P $(PPORT) -c bsd -V -E noreset -Uflash:w:$(HEX)
  else ifeq ($(PROG), jtagice)
	$(ICE) -e -p -f $(ELF) -j $(JPORT)
  else ifeq ($(PROG), bootloader)
	@echo "ERROR: No bootloader set up for this Makefile"
  else ifeq ($(PROG), usbtiny)
	$(DUDE) -p $(MCU) -c usbtiny -V -B 1 -Uflash:w:$(HEX)
  else
	@echo "ERROR: No programmer" $(PROG) "in the Makefile"
  endif

#--------------------------------------------------------------------------------------
# 'make fuses' will set up the processor's fuse bits in a "standard" mode. Standard is
# a setup in which there is no bootloader but the ISP and JTAG interfaces are enabled. 

fuses: nothing
  ifeq ($(PROG), bsd)
	$(DUDE) -p $(MCU) -P $(PPORT) -c $(PROG) -V -E noreset -Ulfuse:w:$(LFUSE):m 
	$(DUDE) -p $(MCU) -P $(PPORT) -c $(PROG) -V -E noreset -Uhfuse:w:$(HFUSE):m 
	$(DUDE) -p $(MCU) -P $(PPORT) -c $(PROG) -V -E noreset -Uefuse:w:$(EFUSE):m
  else ifeq ($(PROG), jtagice)
	@echo "ERROR: Fuse byte programming not set up for JTAG in this Makefile"
  else ifeq ($(PROG), usbtiny)
	$(DUDE) -p $(MCU) -c usbtiny -q -V -Ulfuse:w:$(LFUSE):m
	$(DUDE) -p $(MCU) -c usbtiny -q -V -Uhfuse:w:$(HFUSE):m
	$(DUDE) -p $(MCU) -c usbtiny -q -V -Uefuse:w:$(EFUSE):m
  else
	@echo "ERROR: Only bsd or USBtiny set to program fuse bytes in this Makefile"
  endif

#--------------------------------------------------------------------------------------
# 'make readfuses' will see what the fuses currently hold

readfuses: nothing
  ifeq ($(PROG), bsd)
	@echo "ERROR: Not yet programmed to read fuses with bsd/ISP cable"
  else ifeq ($(PROG), jtagice)
	@$(ICE) -e -j $(JPORT) --read-fuses
  else ifeq ($(PROG), bootloader)
	@echo "ERROR: Not yet programmed to read fuses via bootloader"
  else
	@echo "ERROR: No known device specified to read fuses"
  endif

#-----------------------------------------------------------------------------
# 'make reset' will read a byte of lock bits, ignore it, and reset the chip

reset:
  ifeq ($(PROG), bsd)
	$(DUDE) -c bsd -p $(MCU) -P $(PPORT) -c $(PROG) -V -E noreset \
		-Ulfuse:r:/dev/null:r
  else ifeq ($(PROG), usbtiny)
	$(DUDE) -p $(MCU) -c usbtiny -q -V -Ulfuse:r:/dev/null:r
  else
	@echo "ERROR: make reset only works with parallel ISP cable"
  endif

#--------------------------------------------------------------------------------------
# 'make doc' will use Doxygen to create documentation for the project. 'make libdoc'
# will do the same for the subdirectories which include ME405 library files.

.PHONY: doc libdoc
doc:
	@doxygen doxygen.conf

libdoc:
	@doxygen doxy_lib.conf

#--------------------------------------------------------------------------------------
# 'make clean' will erase the compiled files, listing files, etc. so you can restart
# the building process from a clean slate. It's also useful before committing files to
# a CVS or SVN or Git repository. 

clean:
	@echo -n Cleaning compiled files and documentation...
	@rm -rf $(BUILDDIR)
	@echo done.

#--------------------------------------------------------------------------------------
# 'make library' will build the library file, using an automatically generated list of
# all the C, C++, and assembly source files in the library directories in LIB_DIRS

library: $(LIB_OBJS)
	@avr-ar -r $(LIB_NAME) $(LIB_OBJS)

#------------------------------------------------------------------------------
# This target produces a (large) list of all the predefined macros which are
# available with the compiler version that's being used for this program. Such
# macros can be handy for automatically compiling different code for different
# processors, checking the largest and smallest numbers for different data
# types, and so on
.PHONY: defines
defines:
	$(CC) -mmcu=$(MCU) -dM -E - < /dev/null

#--------------------------------------------------------------------------------------
# 'make term' will run a PuTTY terminal using the settings that are most commonly used
# to talk to an AVR microcontroller connected through a USB-serial port. One must have
# installed PuTTY on the local computer and configured the default settings, of course

term:
	@putty -load "Default Settings" &

#--------------------------------------------------------------------------------------
# 'make help' will show a list of things this makefile can do

help:
	@echo 'make          - Build program file ready to download'
	@echo 'make install  - Build program and download with parallel ISP cable'
	@echo 'make reset    - Reset processor with parallel cable RESET line'
	@echo 'make doc      - Generate documentation with Doxygen'
	@echo 'make clean    - Remove compiled files from all directories'
	@echo ' '
	@echo 'Notes: 1. Other less commonly used targets are in the Makefile'
	@echo '       2. You can combine targets, as in "make clean all"'
