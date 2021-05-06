ASM_FILES := $(shell find . -type f -name '*.asm')
C_FILES := $(shell find . -type f -name '*.c')
OBJS := $(C_FILES:.c=.o) $(ASM_FILES:.asm=.o)

BUILD_PATH = $(ABSOLUTE_PATH)/build/$(shell realpath --relative-to $(ABSOLUTE_PATH) ./)
OBJS := $(patsubst ./%,$(BUILD_PATH)/%,$(OBJS))

KERNEL_ELF = $(ABSOLUTE_PATH)/kernel.elf

CC = x86_64-elf-gcc
LD = x86_64-elf-gcc
AS = nasm

STANDARD_FLAGS := -nostdlib
FILE_FLAGS := -ffreestanding -fno-stack-protector -fno-ident
WARNING_FLAGS := -Wall -Werror -Wextra -Wundef -Wcast-qual -Wwrite-strings -Wno-atomic-implicit-seq-cst -Wno-unused-macros -Wno-unused-function -Wno-missing-prototypes
FLAVOR_FLAGS := -fomit-frame-pointer -mno-red-zone -mno-sse -mno-sse2 -mno-80387 -mno-mmx -mcmodel=kernel -m64 -ffunction-sections -fdata-sections -fmerge-all-constants -fno-unroll-loops -fno-pie -fno-pic
OPTIMIZATION_FLAGS := -Os -fno-asynchronous-unwind-tables
INCLUDE_FLAGS := -I.

C_FLAGS := $(STANDARD_FLAGS) $(FILE_FLAGS) $(WARNING_FLAGS) $(FLAVOR_FLAGS) $(OPTIMIZATION_FLAGS) $(INCLUDE_FLAGS)
NASM_FLAGS := -felf64

LINKER_FLAGS := -T linker.ld -ffreestanding -static -nostdlib -fno-pie -fno-pic -nodefaultlibs -nostartfiles -z max-page-size=0x1000

.PHONY: all
all: $(OBJS) $(KERNEL_ELF)

$(KERNEL_ELF): $(OBJS)
	@echo -e LD $(ECHO) $(KERNEL_ELF)
	@$(LD) $(LINKER_FLAGS) -o $(KERNEL_ELF) $(OBJS)

$(BUILD_PATH)/%.o: %.c
	@echo -e CC $(ECHO) $<
	@mkdir -p $(dir $@)
	@$(CC) $(C_FLAGS) -c $< -o $@

$(BUILD_PATH)/%.o: %.asm
	@echo -e AS $(ECHO) $<
	@mkdir -p $(dir $@)
	@$(AS) $(NASM_FLAGS) $< -o $@

-include $(OBJS:.o=.d)
