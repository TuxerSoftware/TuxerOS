/*+===================================================================
  File:      KMAIN.C

  Summary:   This file contains the implementation of the
             kernel main function in C

  Structs:   

  Functions: kmain: The main function of the kernel

  Defines:   
             
  Copyright 2024-present Tuxer-Software
  This file is licensed under the Apache License, Version 2.0
===================================================================+*/

#include <kernel.h>

extern struct flanterm_context* ft_ctx;

void kmain() {

    printf("Hello, World from kmain()!\n");

}