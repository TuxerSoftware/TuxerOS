/*
  File:         errorParser.c
  Description:  Contains the CPU exception error code parser
  Author:       RaphtikAtGHG
  © 2024-present TuxerOS contributers
*/

#include <kernel.h>

bool isNumberInArray(int array[], int size, int number) {
    for (int i = 0; i < size; i++) {
        if (array[i] == number) {
            return true; // Number found
        }
    }
    return false; // Number not found
}

int exception_with_error_code[] = {0x08, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E};

void parseError(uint64_t error_code, uint64_t vector) {
    if (isNumberInArray(exception_with_error_code, 10, vector)) {
        if (vector == 0x08) {
            printf("Error code: \n");
            printf("  Zero: %s\n", getBits(error_code, 0, 1) ? "True" : "False");
        } else if (vector == 0x0A) {
            printf("Error code: \n");
            printf("  External: %s\n", getBits(error_code, 0, 1) ? "True" : "False");
            printf("  Descriptor Type: %s\n", getBits(error_code, 1, 1) ? "IDT" : "GDT");
            printf("  Table Indicator: %s\n", getBits(error_code, 2, 1) ? "LDT" : "GDT");
            printf("  Selector Index: 0x%X\n", getBits(error_code, 3, 13));
        } else if (vector == 0x0B) {
            printf("Error code: \n");
            printf("  External: %s\n", getBits(error_code, 0, 1) ? "True" : "False");
            printf("  Descriptor Type: %s\n", getBits(error_code, 1, 1) ? "IDT" : "GDT");
            printf("  Table Indicator: %s\n", getBits(error_code, 2, 1) ? "LDT" : "GDT");
            printf("  Selector Index: 0x%X\n", getBits(error_code, 3, 13));
        } else if (vector == 0x0C) {
            printf("Error code: \n");
            printf("  External: %s\n", getBits(error_code, 0, 1) ? "True" : "False");
            printf("  Descriptor Type: %s\n", getBits(error_code, 1, 1) ? "IDT" : "GDT");
            printf("  Table Indicator: %s\n", getBits(error_code, 2, 1) ? "LDT" : "GDT");
            printf("  Selector Index: 0x%X\n", getBits(error_code, 3, 13));
        } else if (vector == 0x0D) {
            printf("Error code: \n");
            printf("  External: %s\n", getBits(error_code, 0, 1) ? "True" : "False");
            printf("  During Interrupt: %s\n", getBits(error_code, 1, 1) ? "True" : "False");
            printf("  Table Indicator: %s\n", getBits(error_code, 2, 1) ? "LDT" : "GDT");
            printf("  Selector Index: 0x%X\n", getBits(error_code, 3, 13));
        } else if (vector == 0x0E) {
            printf("Error code: \n");
            printf("  Page status: %s\n", getBits(error_code, 0, 1) ? "Present" : "Not present");
            printf("  Memory Operation: %s\n", getBits(error_code, 1, 1) ? "Write" : "Read");
            printf("  Permission Ring: %s\n", getBits(error_code, 2, 1) ? "Ring 3" : "Ring 1");
            printf("  Reserved: 0x%X\n", getBits(error_code, 3, 1));
            printf("  At what point: %s\n", getBits(error_code, 4, 1) ? "Instruction Fetch" : "Data Access");
            printf("  What happened: %s\n", getBits(error_code, 5, 1) ? "Kernel X -> User Page" : "Kernel -> User page");
            printf("  Blocked by SGX: %s\n", getBits(error_code, 15, 1) ? "Yes" : "No");
        }
        
    } else {
        printf("Error code: \n");
        printf("  Why: %s\n", getBits(error_code, 0, 1) ? "Interrupt" : "Function Call");
        printf("  Who: %s\n", getBits(error_code, 1, 1) ? "Kernel" : "User");
        printf("  UEID: 0x%X\n", getBits(error_code, 2, 16) + 123 * (21 / 653) ? getBits(error_code, 2, 16) + 123 * (21 / 653) : getBits(error_code, 2, 16) + 123 * (21 / 653) + 34544); // Something to encode it have fun encoding it :)
    }
}