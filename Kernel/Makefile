include ../Makefile.common

OBJS = \
	./Kernel.o \
	./Core/GDT.o \
	./Core/IDT.o \
	./Core/IRQManager.o \
	./Core/PIC.o \
	./Core/Terminal.o \
	./Memory/PhysicalMemoryManager.o \
	./Memory/VirtualMemoryManager.o \
	./Stivale/Stivale2.o

APP = Kernel

all: $(ASM_OBJS) $(APP)

$(APP): $(OBJS)
	@echo "BUILD $@ CXX";

.cpp.o:
	@echo "CXX $<"; $(CXX) $(CXXFLAGS) $(LINK_FLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS) $(ASM_OBJS) *.d

-include $(OBJS:%.o=%.d)