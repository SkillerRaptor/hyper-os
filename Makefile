include ./Makefile.common

SOURCES = $(shell find . -name "*.cpp")
OBJS = $(addsuffix .o, $(basename $(SOURCES)))

LDFLAGS = -T linker.ld -ffreestanding -static -nostdlib -no-pie -nodefaultlibs -nostartfiles -z max-page-size=0x1000

APP = HyperOS

all: $(APP)

$(APP): $(OBJS)
	@echo "LD $@"; $(LD) $(LDFLAGS) -o ./HyperOS.elf $(LINK_FLAGS) $(OBJS)

-include $(OBJS:%.o=%.d)