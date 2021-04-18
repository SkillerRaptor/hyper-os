@echo off

set KERNEL_HDD=../cmake-build-debug/Kernel/build/Kernel.hdd

qemu-system-x86_64 -vga std -drive format=raw,media=disk,index=0,file=%KERNEL_HDD% -d int,cpu_reset -serial stdio -no-reboot -no-shutdown -m 256