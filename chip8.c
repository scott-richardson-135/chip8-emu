#include "chip8.h"
#include <string.h>
#include <stdbool.h>


void init_state(struct State *state) {
    //4kb of memory
    memset(state->memory, 0, MEM_SIZE);

    //16 8 bit registers 
    memset(state->registers, 0, sizeof(state->registers));

    state->I = 0; //I register for pointing at memory
    state->PC = 0x200; //program counter, starts at 0x200


    //Flat array for screen (64 * 32). Bools because each pixel is on or off
    //indexed by (y * 64 + x)
    memset(state->display_buf, 0, sizeof(state->display_buf));

    /*Stack is a hard coded array of 16 slots for 16 bit return addresses
    SP is the index into the array of the next free slot*/

    memset(state->stack, 0, sizeof(state->stack));
    state->SP = 0;

    //2 timers that decrement at 60Hz until they reach 0
    state->delay_timer = 0;
    state->sound_timer = 0;

    setup_font(state);
}

void setup_font(struct State *state) {
    uint8_t chip8_fontset[80] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    memcpy(state->memory + 0x50, chip8_fontset, 80);
}
