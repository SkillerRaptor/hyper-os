include ../Makefile.common

OBJS = \
	Kernel.o \
	Core/Terminal.o

APP = Kernel

all: $(APP)

$(APP): $(OBJS)
	@echo "BUILD $@";

.cpp.o:
	@echo "CXX $<"; $(CXX) $(CXXFLAGS) $(LINK_FLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS) *.d

-include $(OBJS:%.o=%.d)