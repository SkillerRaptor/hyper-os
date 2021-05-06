SUB_DIRECTORIES := kernel/.
ABSOLUTE_PATH = $(realpath .)

KERNEL_HDD = kernel.hdd

.PHONY: all
all: $(SUB_DIRECTORIES)

.PHONY: $(SUB_DIRECTORIES)
$(SUB_DIRECTORIES):
	$(MAKE) -C $@ ABSOLUTE_PATH=$(ABSOLUTE_PATH)

.PHONY: clean
clean:
	$(MAKE) -C thirdparty clean
	@rm -rf build
	@rm -f kernel.elf
	@rm -f kernel.hdd

.PHONY: run
run: $(KERNEL_HDD)
	@qemu-system-x86_64 -vga std -drive format=raw,media=disk,index=0,file=kernel.hdd -serial stdio -m 256 -soundhw pcspk

.PHONY: debug
debug: $(KERNEL_HDD)
	@qemu-system-x86_64 -vga std -drive format=raw,media=disk,index=0,file=kernel.hdd -d int,cpu_reset -serial stdio -no-reboot -no-shutdown -m 256

.PHONY: deps
deps: dependencies

.PHONY: dependencies
dependencies:
	$(MAKE) -C ./thirdparty

.PHONY: $(KERNEL_HDD)
$(KERNEL_HDD):
	@rm -f kernel.hdd
	@dd if=/dev/zero bs=1M count=0 seek=64 of=$(KERNEL_HDD)
	@parted -s $(KERNEL_HDD) mklabel msdos
	@parted -s $(KERNEL_HDD) mkpart primary 1 100%
	@thirdparty/echfs/echfs-utils -m -p0 $(KERNEL_HDD) quick-format 32768
	@thirdparty/echfs/echfs-utils -m -p0 $(KERNEL_HDD) import kernel.elf kernel.elf
	@thirdparty/echfs/echfs-utils -m -p0 $(KERNEL_HDD) import limine.cfg limine.cfg
	@thirdparty/echfs/echfs-utils -m -p0 $(KERNEL_HDD) import thirdparty/limine/bin/limine.sys limine.sys
	@thirdparty/limine/bin/limine-install $(KERNEL_HDD);