#  File:         Kernel Makefile
#  Description:  This is the makefile fdor building the kernel
#  Author:       RaphtikAtGHG
#  © 2024-present TuxerOS contributers

include config.mk

override CFILES := $(shell cd src && find -L * -type f -name '*.c')
override ASFILES := $(shell cd src && find -L * -type f -name '*.S')
override NASMFILES := $(shell cd src && find -L * -type f -name '*.asm')
override OBJ := $(addprefix obj/,$(CFILES:.c=.c.o) $(ASFILES:.S=.S.o) $(NASMFILES:.asm=.asm.o))
override HEADER_DEPS := $(addprefix obj/,$(CFILES:.c=.c.d) $(ASFILES:.S=.S.d))


.PHONY: all
all: bin/$(KERNEL)

src/limine.h:
	@echo "LIMINE >>> Downloading limine.h "
	@curl -Lo $@ https://github.com/limine-bootloader/limine/raw/trunk/limine.h > /dev/null 2>&1

bin/$(KERNEL): GNUmakefile linker.ld $(OBJ)
	@echo "LD >>> Linking $@"
	@mkdir -p "$$(dirname $@)"
	@$(KLD) $(OBJ) $(KLDFLAGS) -o $@

# Include header dependencies.
-include $(HEADER_DEPS)

# Compilation rules for *.c files.
obj/%.c.o: src/%.c GNUmakefile src/limine.h
	@echo "CC >>> Compiling $< to $@"
	@mkdir -p "$$(dirname $@)"
	@$(KCC) $(KCFLAGS) $(KCPPFLAGS) -c $< -o $@

# Compilation rules for *.S files.
obj/%.S.o: src/%.S GNUmakefile
	@echo "CC >>> Compiling $< to $@"
	@mkdir -p "$$(dirname $@)"
	@$(KCC) $(KCFLAGS) $(KCPPFLAGS) -c $< -o $@

# Compilation rules for *.asm (nasm) files.
obj/%.asm.o: src/%.asm GNUmakefile
	@echo "ASM >>> Compiling $< to $@"
	@mkdir -p "$$(dirname $@)"
	@nasm $(KNASMFLAGS) $< -o $@

# Remove object files and the final executable.
.PHONY: clean
clean:
	@echo "CLEAN >>> Cleaning"
	@rm -rf bin obj

.PHONY: distclean
distclean: clean
	@echo "CLEAN >>> Distcleaning"
	@rm -f src/limine.h
