symbol-file kernel/bin/tuxer
set disassembly-flavor intel
target remote | qemu-system-x86_64 -M q35 -m 2G -hda build/TuxerOS.hdd -boot d --no-reboot --no-shutdown -S -gdb stdio