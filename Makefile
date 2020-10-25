include ./Makefile.common

OBJS = \
	./Kernel/Kernel.o \
	./Kernel/Core/Terminal.o \
	./Libraries/LibC/string.o \
	./Libraries/LibC/stdio.o \
	./Libraries/LibC/stdlib.o

LD = i686-elf-gcc
LDFLAGS = -T linker.ld -ffreestanding -O2 -lgcc -nostdlib -nodefaultlibs -nostartfiles

CRTI_OBJ = ./Kernel/Boot/crti.o
CRTBEGIN_OBJ := $(shell $(LD) $(LDFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(LD) $(LDFLAGS) -print-file-name=crtend.o)
CRTN_OBJ = ./Kernel/Boot/crtn.o

APP = HyperOS

all: $(BOOTLOADER) $(APP)

$(APP): $(OBJS)
	@echo "LD $@"; $(LD) $(LDFLAGS) -o ./HyperOS.bin ./Kernel/Boot/boot.o $(LINK_FLAGS) $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)

-include $(OBJS:%.o=%.d)