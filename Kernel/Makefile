include ../Makefile.common

LIB_OBJS = \
	$(HYPEROS_BASE_DIR)/Libraries/LibC/string.o \
	$(HYPEROS_BASE_DIR)/Libraries/LibC/stdio.o \
	$(HYPEROS_BASE_DIR)/Libraries/LibC/stdlib.o

OBJS = \
	Kernel.o \
	Core/Terminal.o

APP = Kernel

BOOTLOADER = Boot/boot.bin

DEFINES += \

all: $(BOOTLOADER) $(APP)

$(APP): $(OBJS)
	@echo "LD $@"; $(LD) $(LDFLAGS) -o $(HYPEROS_BASE_DIR)/HyperOS.bin Boot/boot.bin $(LINK_FLAGS) $(OBJS) $(LIB_OBJS)

$(BOOTLOADER): Boot/boot.s
	@echo "AS $<"; $(AS) -o $@ $<

.cpp.o:
	@echo "CXX $<"; $(CXX) $(CXXFLAGS) $(LINK_FLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS) *.d

-include $(OBJS:%.o=%.d)