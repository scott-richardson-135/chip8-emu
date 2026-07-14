#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include <stdbool.h>

#define MEM_SIZE 4096

struct State {
    uint8_t memory[MEM_SIZE];  //4kb of memory
    uint8_t registers[16];     //16 8 bit registers
    uint16_t I;                //I register for pointing at memory
    uint16_t PC;               //program counter, starts at 0x200

    bool display_buf[2048];    //Flat array for screen (64 * 32). Bools because each pixel is on or off
                               //indexed by (y * 64 + x)

    uint16_t stack[16];        //Stack is a hard coded array of 16 slots for 16 bit return addresses
    uint8_t SP;                //SP is the index into the array of the next free slot

    uint8_t delay_timer;       //2 timers that decrement at 60Hz until they reach 0
    uint8_t sound_timer;
};

void init_state(struct State *state);

void setup_font(struct State *state);

#endif