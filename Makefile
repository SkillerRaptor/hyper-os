include ./Makefile.common

SOURCES = $(shell find . -name "ThirdParty" -prune -o -name "Userland" -prune -o -name ".git" -prune -o -name "*.c" -o -name '*.s')
TMP_SOURCES := $(SOURCES)
SOURCES = $(filter-out ./.git ./ThirdParty ./Userland, $(TMP_SOURCES))
OBJS = $(addsuffix .o, $(basename $(SOURCES)))

LDFLAGS = -T linker.ld -ffreestanding -static -nostdlib -no-pie -nodefaultlibs -nostartfiles -z max-page-size=0x1000

APP = HyperOS

all: $(APP)

$(APP): $(OBJS)
	@echo "LD $@"; $(LD) $(LDFLAGS) -o ./HyperOS.elf $(LINK_FLAGS) $(OBJS)

build:
	@sh ./Scripts/Build.sh

clean:
	@sh ./Scripts/Clean.sh

debug:
	@sh ./Scripts/Debug.sh

run:
	@sh ./Scripts/Run.sh

configure:
	@sh ./Scripts/Configure.sh

-include $(OBJS:%.o=%.d)