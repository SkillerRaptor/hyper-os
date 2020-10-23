include ../Makefile.common

include ../Makefile.files

OBJS = \
	Kernel.o \
	Core/Terminal.o

APP = Kernel

BOOTLOADER = Boot/boot.bin

DEFINES += \

all: $(BOOTLOADER) $(APP)

$(APP): $(OBJS)
	@echo "LD $@"; $(LD) $(LDFLAGS) -o $(HYPEROS_BASE_DIR)/HyperOS.bin Boot/boot.bin $(LINK_FLAGS) $(GLOBAL_OBJS)

$(BOOTLOADER): Boot/boot.s
	@echo "AS $<"; $(AS) -o $@ $<

.cpp.o:
	@echo "CXX $<"; $(CXX) $(CXXFLAGS) $(LINK_FLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS) *.d

-include $(OBJS:%.o=%.d)