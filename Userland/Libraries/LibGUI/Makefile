include ../../../Makefile.common

SOURCES = $(shell find . -name "*.cpp")
OBJS = $(addsuffix .o, $(basename $(SOURCES)))

APP = libgui.a

all: $(APP)

$(APP): $(OBJS)
	@echo "LIB $@"; $(AR) rcs $@ $(OBJS)

.cpp.o:
	@echo "CXX $<"; $(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS)

-include $(OBJS:%.o=%.d)