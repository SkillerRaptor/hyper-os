include ../../Makefile.common

OBJS = \
    stdio.o \
    stdlib.o \
    string.o

APP = libc.a

all: $(APP)

$(APP): $(OBJS)
	@echo "LIB $@"; $(AR) rcs $@ $(OBJS)

.cpp.o:
	@echo "CXX $<"; $(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS)

-include $(OBJS:%.o=%.d)