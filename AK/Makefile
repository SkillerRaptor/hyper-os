include ../Makefile.common

SOURCES = $(shell find . -name "*.c")
OBJS = $(addsuffix .o, $(basename $(SOURCES)))

APP = AK

all: $(APP)

$(APP): $(OBJS)
	@echo "BUILD $@ C";

.c.o:
	@echo "C $<"; $(C) $(CFLAGS) $(LINK_FLAGS) -o $@ -c $<

clean:
	@echo "CLEAN"; rm -f $(APP) $(OBJS) *.d

-include $(OBJS:%.o=%.d)