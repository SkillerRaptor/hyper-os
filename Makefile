include ./Makefile.common

SOURCES = $(shell find . -name "*.c" -o -name '*.s')
OBJS = $(addsuffix .o, $(basename $(SOURCES)))

LDFLAGS = -T linker.ld -ffreestanding -static -nostdlib -no-pie -nodefaultlibs -nostartfiles -z max-page-size=0x1000

APP = HyperOS

all: $(APP)

$(APP): $(OBJS)
	@echo "LD $@"; $(LD) $(LDFLAGS) -o ./HyperOS.elf $(LINK_FLAGS) $(OBJS)

build:
	@printf "\e[93m === Starting Building === \e[39m\n"

	@find */ -name "Makefile" -execdir make -C . \;
	@make -C .

	@printf "\e[92m === Finished Building === \e[39m\n"

	@printf "\n\e[93m === Starting Building HDD === \e[39m\n"

	@mkdir ./build
	@rm -f ./build/HyperOS.hdd

	@dd if=/dev/zero bs=1M count=0 seek=64 of=./build/HyperOS.hdd

	@parted -s ./build/HyperOS.hdd mklabel msdos
	@parted -s ./build/HyperOS.hdd mkpart primary 1 100%
	@parted -s ./build/HyperOS.hdd set 1 boot on

	@echfs-utils -m -p0 ./build/HyperOS.hdd quick-format 32768
	@echfs-utils -m -p0 ./build/HyperOS.hdd import ./HyperOS.elf HyperOS.elf
	@echfs-utils -m -p0 ./build/HyperOS.hdd import ./limine.cfg limine.cfg

	@limine-install ./limine.bin ./build/HyperOS.hdd

	@printf "\e[92m === Finished Building HDD === \e[39m\n"

clean:
	@printf "\e[93m === Starting Cleaning === \e[39m\n"

	@make -C ./Userland/Libraries/LibGUI clean
	@make -C ./Userland/Libraries/LibC clean
	@make -C ./Kernel clean
	@make -C ./AK clean

	@rm -f HyperOS.elf
	@rm -r ./build

	@printf "\e[92m === Finished Cleaning === \e[39m\n"



debug:
	@qemu-system-x86_64 -vga std -drive format=raw,media=disk,index=0,file=./build/HyperOS.hdd -d int,cpu_reset,guest_errors -serial stdio -no-reboot -no-shutdown -m 256

run:
	@qemu-system-x86_64 -vga std -drive format=raw,media=disk,index=0,file=./build/HyperOS.hdd -serial stdio -m 256

-include $(OBJS:%.o=%.d)