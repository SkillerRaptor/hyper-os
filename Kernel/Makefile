include ../Makefile.common

OBJS = \
	./Kernel.o \
	./Core/Terminal.o

APP = Kernel

BOOTLOADER_OBJS = \
	./Boot/boot.o \
	./Boot/crti.o \
	./Boot/crtn.o

all: $(BOOTLOADER_OBJS) $(APP)

$(APP): $(OBJS)
	@echo "BUILD $@ CXX";

.s.o:
	@echo "AS $<"; $(AS) -o $@ $<

.cpp.o:
	@echo "CXX $<"; $(CXX) $(CXXFLAGS) $(LINK_FLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS) *.d

-include $(OBJS:%.o=%.d)