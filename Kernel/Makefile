include ../Makefile.common

OBJS = \
	./Kernel.o \
	./Core/GDT.o \
	./Core/IDT.o \
	./Core/IRQManager.o \
	./Core/PIC.o \
	./Core/Terminal.o

APP = Kernel

BOOTLOADER_OBJS = \
	./Boot/boot.o \
	./Boot/crti.o \
	./Boot/crtn.o \
	./Boot/Interrupts.o

all: $(BOOTLOADER_OBJS) $(APP)

$(APP): $(OBJS)
	@echo "BUILD $@ CXX";

.s.o:
	@echo "AS $<"; $(AS) -o $@ $<

.cpp.o:
	@echo "CXX $<"; $(CXX) $(CXXFLAGS) $(LINK_FLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS) $(BOOTLOADER_OBJS) *.d

-include $(OBJS:%.o=%.d)