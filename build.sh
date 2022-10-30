set -e

cargo build

if [ ! -d "boot/limine/" ] ; then
    git clone https://github.com/limine-bootloader/limine.git --branch=v4.x-branch-binary --depth=1 boot/limine/
    make -C boot/limine/
fi

mkdir -p boot/
rm -rf boot/iso_root/
mkdir -p boot/iso_root/

cp target/x86_64-hyper_os/debug/hyper_kernel hyper_kernel/limine.cfg boot/limine/limine.sys boot/limine/limine-cd.bin boot/limine/limine-cd-efi.bin boot/iso_root/
xorriso -as mkisofs -b limine-cd.bin \
    -no-emul-boot -boot-load-size 4 -boot-info-table \
    --efi-boot limine-cd-efi.bin \
    -efi-boot-part --efi-boot-image --protective-msdos-label \
    boot/iso_root/ -o boot/hyper_os.iso
boot/limine/limine-deploy boot/hyper_os.iso

rm -rf boot/iso_root/

