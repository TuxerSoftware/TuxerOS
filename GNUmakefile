# Nuke built-in rules and variables.
override MAKEFLAGS += -rR --no-print-directory -j$(shell nproc)

override IMAGE_NAME := TuxerOS

override IMAGE_DIR := build/

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
run: $(IMAGE_DIR)/$(IMAGE_NAME).iso
	@echo "QEMU >>> Running $(IMAGE_DIR)/$(IMAGE_NAME).iso"
	@qemu-system-x86_64 -M q35 -m 2G -cdrom $(IMAGE_DIR)/$(IMAGE_NAME).iso -boot d --no-reboot --no-shutdown

.PHONY: run-uefi
run-uefi: ovmf $(IMAGE_NAME).iso
	@echo "QEMU >>> Running $(IMAGE_NAME).iso with UEFI firmware"
	@qemu-system-x86_64 -M q35 -m 2G -bios ovmf/OVMF.fd -cdrom $(IMAGE_NAME).iso -boot d

.PHONY: run-hdd
run-hdd: $(IMAGE_NAME).hdd
	@echo "QEMU >>> Running $(IMAGE_NAME).hdd"
	@qemu-system-x86_64 -M q35 -m 2G -hda $(IMAGE_NAME).hdd

.PHONY: run-hdd-uefi
run-hdd-uefi: ovmf $(IMAGE_NAME).hdd
	@echo "QEMU >>> Running $(IMAGE_NAME).hdd with UEFI firmware"
	@qemu-system-x86_64 -M q35 -m 2G -bios ovmf/OVMF.fd -hda $(IMAGE_NAME).hdd

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
	@cp -v kernel/bin/tuxer iso_root/boot/ > /dev/null 2>&1
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

$(IMAGE_NAME).hdd: limine kernel

	@echo "HDD >>> Removing old files"
	@rm -f $(IMAGE_NAME).hdd

	@echo "HDD >>> Creating the HDD image"
	@dd if=/dev/zero bs=1M count=0 seek=64 of=$(IMAGE_NAME).hdd

	@echo "HDD >>> Partitioning the HDD image"
	@sgdisk $(IMAGE_NAME).hdd -n 1:2048 -t 1:ef00

	@echo "HDD >>> Installing limine"
	@./limine/limine bios-install $(IMAGE_NAME).hdd > /dev/null 2>&1

	@echo "HDD >>> Formatting the HDD image"
	@mformat -i $(IMAGE_NAME).hdd@@1M > /dev/null 2>&1

	@echo "HDD >>> Copying files"
	@mmd -i $(IMAGE_NAME).hdd@@1M ::/EFI ::/EFI/BOOT ::/boot ::/boot/limine > /dev/null 2>&1
	@mcopy -i $(IMAGE_NAME).hdd@@1M kernel/bin/kernel ::/boot > /dev/null 2>&1
	@mcopy -i $(IMAGE_NAME).hdd@@1M limine.cfg limine/limine-bios.sys ::/boot/limine > /dev/null 2>&1
	@mcopy -i $(IMAGE_NAME).hdd@@1M limine/BOOTX64.EFI ::/EFI/BOOT > /dev/null 2>&1
	@mcopy -i $(IMAGE_NAME).hdd@@1M limine/BOOTIA32.EFI ::/EFI/BOOT > /dev/null 2>&1

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
