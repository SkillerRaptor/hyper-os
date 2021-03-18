include ../../../Makefile.common

SOURCES = $(shell find . -name "*.c")
OBJS = $(addsuffix .o, $(basename $(SOURCES)))

APP = libgui.a

all: $(APP)

$(APP): $(OBJS)
	@echo "LIB $@"; $(AR) rcs $@ $(OBJS)

.c.o:
	@echo "C $<"; $(C) $(CFLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS)

-include $(OBJS:%.o=%.d)