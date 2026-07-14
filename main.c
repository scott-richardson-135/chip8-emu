#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "chip8.h"

#define MEM_SIZE 4096
#define FONT_START_ADDR 0x50

void print_state(struct State *state) {
    printf("PC: 0x%03X   I: 0x%03X   SP: %u\n", state->PC, state->I, state->SP);

    printf("Registers:\n");
    for (int i = 0; i < 16; i++) {
        printf("  V%X: 0x%02X\n", i, state->registers[i]);
    }

    printf("Stack:\n");
    for (int i = 0; i < 16; i++) {
        printf("  [%d]: 0x%04X\n", i, state->stack[i]);
    }

    printf("Delay timer: %u   Sound timer: %u\n", state->delay_timer, state->sound_timer);

    printf("Font bytes at 0x%02X (first 16 bytes):\n  ", FONT_START_ADDR);
    for (int i = 0; i < 16; i++) {
        printf("0x%02X ", state->memory[FONT_START_ADDR + i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    
    /*STATE SETUP*/
    struct State state;
    init_state(&state);


    print_state(&state);
    

    return 0;
}