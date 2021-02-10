include ../Makefile.common

SOURCES = $(shell find . -name "*.cpp")
OBJS = $(addsuffix .o, $(basename $(SOURCES)))

APP = AK

all: $(APP)

$(APP): $(OBJS)
	@echo "BUILD $@ CXX";

.cpp.o:
	@echo "CXX $<"; $(CXX) $(CXXFLAGS) $(LINK_FLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS) *.d

-include $(OBJS:%.o=%.d)