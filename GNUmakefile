#  File:         Main Makefile
#  Description:  This is the main makefile no explanation needed
#  Author:       RaphtikAtGHG
#  © 2024-present TuxerOS contributers

override IMAGE_NAME := TuxerOS

override IMAGE_DIR := build/

include kernel/config.mk


# Convenience macro to reliably declare user overridable variables.
define DEFAULT_VAR =
    ifeq ($(origin $1),default)
        override $(1) := $(2)
    endif
    ifeq ($(origin $1),undefined)
        override $(1) := $(2)
    endif
endef

.PHONY: all
all: $(IMAGE_DIR)/$(IMAGE_NAME).iso

.PHONY: all-hdd
all-hdd: $(IMAGE_NAME).hdd

.PHONY: run

.PHONY: run
run: $(IMAGE_DIR)/$(IMAGE_NAME).iso
	@echo "QEMU >>> Running $(IMAGE_DIR)$(IMAGE_NAME).iso"
	@qemu-system-x86_64 $(QEMUARGS) -cdrom $(IMAGE_DIR)$(IMAGE_NAME).iso

.PHONY: run-uefi
run-uefi: ovmf $(IMAGE_DIR)/$(IMAGE_NAME).iso
	@echo "QEMU >>> Running $(IMAGE_NAME).iso with UEFI firmware"
	@qemu-system-x86_64 $(QEMUARGS) -bios ovmf/OVMF.fd -cdrom $(IMAGE_DIR)$(IMAGE_NAME).iso

.PHONY: run-hdd
run-hdd: $(IMAGE_DIR)/$(IMAGE_NAME).hdd
	@echo "QEMU >>> Running $(IMAGE_NAME).hdd"
	@qemu-system-x86_64 $(QEMUARGS) -hda $(IMAGE_DIR)/$(IMAGE_NAME).hdd

.PHONY: run-hdd-uefi
run-hdd-uefi: ovmf $(IMAGE_DIR)/$(IMAGE_NAME).hdd
	@echo "QEMU >>> Running $(IMAGE_NAME).hdd with UEFI firmware"
	@qemu-system-x86_64 $(QEMUARGS) -bios ovmf/OVMF.fd -hda $(IMAGE_DIR)/$(IMAGE_NAME).hdd

ovmf:
	@echo "UEFI >>> Downloading firmware"
	@mkdir -p ovmf
	@cd ovmf && curl -Lo OVMF.fd https://retrage.github.io/edk2-nightly/bin/RELEASEX64_OVMF.fd

limine:
	@echo "LIMINE >>> Downloading limine"
	@git clone https://github.com/limine-bootloader/limine.git --branch=v7.x-binary --depth=1 > /dev/null 2>&1
	@echo "LIMINE >>> Building limine"
	@$(MAKE) -C limine > /dev/null 2>&1

.PHONY: kernel
kernel:
	@echo "KERNEL >>> Building kernel"
	@$(MAKE) -C kernel

$(IMAGE_DIR)/$(IMAGE_NAME).iso: limine kernel
	@echo "ISO >>> Removing old files"
	@rm -rf iso_root

	@echo "ISO >>> Creating directories"
	@mkdir -p iso_root/boot

	@echo "ISO >>> Copying kernel"
	@cp -v kernel/bin/tuxer.elf iso_root/boot/ > /dev/null 2>&1
	@mkdir -p iso_root/boot/limine 

	@echo "ISO >>> Copying limine files"
	@cp -v boot/limine.cfg limine/limine-bios.sys limine/limine-bios-cd.bin limine/limine-uefi-cd.bin iso_root/boot/limine/ > /dev/null 2>&1
	@cp -v boot/bootbg.jpg boot/FONT.F16 iso_root/ > /dev/null 2>&1
	
	@echo "ISO >>> Creating installing EFI loaders"
	@mkdir -p iso_root/EFI/BOOT > /dev/null 2>&1
	@cp -v limine/BOOTX64.EFI iso_root/EFI/BOOT/ > /dev/null 2>&1
	@cp -v limine/BOOTIA32.EFI iso_root/EFI/BOOT/ > /dev/null 2>&1

	@echo "ISO >>> Creating the ISO image"
	@xorriso -as mkisofs -b boot/limine/limine-bios-cd.bin \
		-no-emul-boot -boot-load-size 4 -boot-info-table \
		--efi-boot boot/limine/limine-uefi-cd.bin \
		-efi-boot-part --efi-boot-image --protective-msdos-label \
		iso_root -o $(IMAGE_DIR)/$(IMAGE_NAME).iso > /dev/null 2>&1

	@echo "ISO >>> Installing limine"
	@./limine/limine bios-install $(IMAGE_DIR)/$(IMAGE_NAME).iso > /dev/null 2>&1
	
	@echo "ISO >>> Cleaning up"
	@rm -rf iso_root

HDD_IMAGE = $(IMAGE_DIR)$(IMAGE_NAME).hdd

$(IMAGE_DIR)/$(IMAGE_NAME).hdd: limine kernel
	@echo "HDD >>> Removing old files"
	@rm -f $(HDD_IMAGE) > /dev/null 2>&1

	@echo "HDD >>> Creating the HDD image"
	@dd if=/dev/zero bs=1M count=64 of=$(HDD_IMAGE) > /dev/null 2>&1

	@echo "HDD >>> Partitioning the HDD image"
	@sgdisk $(HDD_IMAGE) -n 1:2048 -t 1:ef00 > /dev/null 2>&1

	@echo "HDD >>> Installing limine"
	@./limine/limine bios-install $(HDD_IMAGE) > /dev/null 2>&1

	@echo "HDD >>> Formatting the partition"
	@mformat -i $(HDD_IMAGE)@@1M -L32 -v "TUXEROS    " #> /dev/null 2>&1

	@echo "HDD >>> Copying files"
	@mmd -i $(HDD_IMAGE)@@1M ::/EFI ::/EFI/BOOT ::/boot ::/boot/limine > /dev/null 2>&1
	@mcopy -i $(HDD_IMAGE)@@1M kernel/bin/tuxer.elf ::/boot > /dev/null 2>&1
	@mcopy -i $(HDD_IMAGE)@@1M boot/limine.cfg  limine/limine-bios.sys ::/boot/limine > /dev/null 2>&1
	@mcopy -i $(HDD_IMAGE)@@1M boot/bootbg.jpg boot/FONT.F16 ::/ > /dev/null 2>&1
	@mcopy -i $(HDD_IMAGE)@@1M limine/BOOTX64.EFI ::/EFI/BOOT > /dev/null 2>&1
	@mcopy -i $(HDD_IMAGE)@@1M limine/BOOTIA32.EFI ::/EFI/BOOT > /dev/null 2>&1

	@echo "HDD >>> Finished"

.PHONY: clean
clean:

	@echo "CLEAN >>> Cleaning"
	@rm -rf iso_root $(IMAGE_NAME).iso $(IMAGE_NAME).hdd

	@echo "CLEAN >>> Cleaning kernel"
	@$(MAKE) -C kernel clean > /dev/null 2>&1

.PHONY: distclean
distclean: clean

	@echo "CLEAN >>> Distcleaning limine and OVMF"
	@rm -rf limine ovmf

	@echo "CLEAN >>> Distcleaning kernel"
	@$(MAKE) -C kernel distclean > /dev/null 2>&1
