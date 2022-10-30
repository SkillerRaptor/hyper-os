set -e

qemu-system-x86_64 -cdrom boot/hyper_os.iso --no-reboot --no-shutdown -d int -D qemulog.log
