# Makefile configuration
override MAKEFLAGS += --no-print-directory -j$(shell nproc) -rR

# ISO image
override ISO_NAME := TuxerOS
override ISO_DIR := build/

# HDD image
override HDD_NAME := TuxerOS
override HDD_DIR := build/


override ROOTFS := rootfs/

# Kernel Image
override KERNEL := tuxer.elf

# Building
override KLD = x86_64-elf-ld
override KCC = x86_64-elf-gcc
override KNASM = nasm

# Default variables
define DEFAULT_VAR =
    ifeq ($(origin $1),default)
        override $(1) := $(2)
    endif
    ifeq ($(origin $1),undefined)
        override $(1) := $(2)
    endif
endef

override KCFLAGS += \
    -Wall \
    -Wextra \
    -std=gnu11 \
    -ffreestanding \
    -fno-stack-protector \
    -fno-stack-check \
    -fno-lto \
    -fPIE \
    -m64 \
    -march=x86-64 \
    -mno-80387 \
    -mmmx \
    -msse \
    -msse2 \
    -mno-red-zone \
    -Wno-old-style-declaration 

override KCPPFLAGS := \
    -I src \
    -I include \
    $(KCPPFLAGS) \
    -MMD \
    -MP

override KLDFLAGS += \
    -m elf_x86_64 \
    -nostdlib \
    -static \
    -pie \
    --no-dynamic-linker \
    -z text \
    -z max-page-size=0x1000 \
    -T linker.ld

override KNASMFLAGS += \
    -Wall \
    -f elf64

override QEMUARGS += \
    -M pc \
    -m 2G \
    -boot d \
    --no-reboot --no-shutdown \
    -d int,cpu_reset,unimp \
    -D qemu.log \
    -monitor stdio