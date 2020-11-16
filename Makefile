include ./Makefile.common

OBJS = \
	./AK/Bitmap.o \
	./AK/IO.o \
	./Kernel/Kernel.o \
	./Kernel/Core/GDT.o \
	./Kernel/Core/IDT.o \
	./Kernel/Core/Interrupts.o \
	./Kernel/Core/IRQManager.o \
	./Kernel/Core/PIC.o \
	./Kernel/Core/Terminal.o \
	./Kernel/Memory/PhysicalAllocator.o \
	./Libraries/LibC/ctype.o \
	./Libraries/LibC/string.o \
	./Libraries/LibC/stdio.o \
	./Libraries/LibC/stdlib.o

LDFLAGS = -T linker.ld -ffreestanding -static -nostdlib -no-pie -nodefaultlibs -nostartfiles -z max-page-size=0x1000

APP = HyperOS

all: $(APP)

$(APP): $(OBJS)
	@echo "LD $@"; $(LD) $(LDFLAGS) -o ./HyperOS.elf $(LINK_FLAGS) $(OBJS)

-include $(OBJS:%.o=%.d)