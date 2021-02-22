include ../Makefile.common

SOURCES = $(shell find . -name "*.c" -o -name '*.s')
OBJS = $(addsuffix .o, $(basename $(SOURCES)))

APP = Kernel

all: $(APP)

$(APP): $(OBJS)
	@echo "BUILD $@ C";

.s.o:
	@echo "AS $<"; $(AS) -o $@ $<

.c.o:
	@echo "C $<"; $(C) $(CFLAGS) $(LINK_FLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS) *.d

-include $(OBJS:%.o=%.d)