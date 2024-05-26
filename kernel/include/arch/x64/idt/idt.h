/*+===================================================================
  File:      IDT.H

  Summary:   This file is the header file for the Interrupt
             Descriptor Table (IDT) declerations.

  Structs:   idt_entry_t: Structure for an IDT entry.
             idt_ptr_t: Structure for an IDT pointer.

  Functions: init_idt: Initializes the IDT.
             load_idt: Loads the IDT using inline assembly.

  Defines:   IDT_ENTRIES: The number of entries in the IDT.

  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#pragma once

#include <kernel.h>

#define IDT_ENTRIES 256
