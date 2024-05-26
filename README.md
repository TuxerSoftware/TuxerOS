# Tuxer Operating System
A simple x64 Operating System.

> [!NOTE]
> This is a rewrite of the old kernel,
> which I deleted.

## What is TuxerOS
TuxerOS is a simple Operating System written in C and Assembly for now. The goal for this OS is 
mostly learning. But if anyone wants to use this as a daily driver I am not stopping you. This 
OS was originally made for x86 but I decided to switch to limine, which uses x64. Also I originally
used my own custom bootloader. If you are wondering why I stopped with that? I just didn't want to
bother with a kernel and adding features for the bootloader. Maybe someday I will make a custom
one.

## Support for TuxerOS
Here is the list of supported architectures. The other ones that aren't support I am trying to add
later in development

| Arch | Supported |
|------|-----------|
|x64|✅|
|x86|❌ |
|aarch64|❌ |

## Kernel Design
The design can be found in [Design file](docs/DESIGN.md)

## Contributing
If you wan't to contribute please read [the contributing guide](docs/CONTRIBUTING.md) and then open a
pull request I will review it. Please don't be mad if your pull request gets rejected.

## Credits
<b>[OSDev Wiki](https://wiki.osdev.org/)</b>: General Information about Operating System Development.</br>
<b>[Nanobyte Discord Server](https://discord.gg/RgHc5XrCEw)</b>: A lot of help with diffrent things. </br>
<b>ChatGPT</b>: Explaining a lot of stuff that I didn't understand


