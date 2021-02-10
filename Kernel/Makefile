include ../Makefile.common

SOURCES = $(shell find . -name "*.cpp")
OBJS = $(addsuffix .o, $(basename $(SOURCES)))

APP = Kernel

all: $(ASM_OBJS) $(APP)

$(APP): $(OBJS)
	@echo "BUILD $@ CXX";

.cpp.o:
	@echo "CXX $<"; $(CXX) $(CXXFLAGS) $(LINK_FLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS) $(ASM_OBJS) *.d

-include $(OBJS:%.o=%.d)