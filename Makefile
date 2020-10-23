include ./Makefile.common

OBJS = \
	./Kernel/Kernel.o \
	./Kernel/Core/Terminal.o \
	./Libraries/LibC/string.o \
	./Libraries/LibC/stdio.o \
	./Libraries/LibC/stdlib.o

APP = HyperOS

BOOTLOADER = ./Kernel/Boot/boot.bin

all: $(BOOTLOADER) $(APP)

$(APP): $(OBJS)
	@echo "LD $@"; $(LD) $(LDFLAGS) -o ./HyperOS.bin ./Kernel/Boot/boot.bin $(LINK_FLAGS) $(OBJS)

$(BOOTLOADER): ./Kernel/Boot/boot.s
	@echo "AS $<"; $(AS) -o $@ $<

-include $(OBJS:%.o=%.d)