#!/bin/bash

IMAGE_DIR="build/"
IMAGE_NAME="TuxerOS.hdd"

echo "HDD >>> Removing old files"
rm -f "${IMAGE_DIR}/${IMAGE_NAME}.hdd"

echo "HDD >>> Creating the HDD image"
dd if=/dev/zero bs=1M count=0 seek=64 of="${IMAGE_DIR}/${IMAGE_NAME}.hdd"

echo "HDD >>> Partitioning the HDD image"
sgdisk "${IMAGE_DIR}/${IMAGE_NAME}.hdd" -n 1:2048 -t 1:ef00

echo "HDD >>> Installing limine"
./limine/limine bios-install "${IMAGE_DIR}/${IMAGE_NAME}.hdd" > /dev/null 2>&1

echo "HDD >>> Formatting the HDD image"
mformat -i "${IMAGE_DIR}/${IMAGE_NAME}.hdd@@1M" > /dev/null 2>&1

echo "HDD >>> Copying files"

echo "HDD >>> Copying files"
mmd -i "${IMAGE_DIR}/${IMAGE_NAME}.hdd" ::/EFI ::/EFI/BOOT ::/boot ::/boot/limine > /dev/null 2>&1
mcopy -i "${IMAGE_DIR}/${IMAGE_NAME}.hdd" kernel/bin/tuxer.elf ::/boot > /dev/null 2>&1
mcopy -i "${IMAGE_DIR}/${IMAGE_NAME}.hdd" boot/limine.cfg limine/limine-bios.sys ::/boot/limine > /dev/null 2>&1
mcopy -i "${IMAGE_DIR}/${IMAGE_NAME}.hdd" boot/bootbg.jpg boot/FONT.F16 ::/ > /dev/null 2>&1
mcopy -i "${IMAGE_DIR}/${IMAGE_NAME}.hdd" limine/BOOTX64.EFI ::/EFI/BOOT > /dev/null 2>&1
mcopy -i "${IMAGE_DIR}/${IMAGE_NAME}.hdd" limine/BOOTIA32.EFI ::/EFI/BOOT > /dev/null 2>&1

echo "HDD >>> Finished"
