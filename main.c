#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MEM_SIZE 4096

void setup_font(uint8_t *memory) {
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

    memcpy(memory + 0x50, chip8_fontset, 80);
}

int main(int argc, char *argv[]) {
    
    /*STATE SETUP
    this is probably a dumb way to do it but it's a start */

    //4kb of memory
    uint8_t memory[MEM_SIZE] = {0};

    //16 8 bit registers 
    uint8_t registers[16] = {0};

    uint16_t I = 0; //I register for pointing at memory
    uint16_t PC = 0x200; //program counter, starts at 0x200


    //Flat array for screen (64 * 32). Bools because each pixel is on or off
    //indexed by (y * 64 + x)
    bool display_buf[2048] = {0};

    /*Stack is a hard coded array of 16 slots for 16 bit return addresses
    SP is the index into the array of the next free slot*/
    uint16_t stack[16] = {0};
    uint8_t SP = 0;

    //2 timers that decrement at 60Hz until they reach 0
    uint8_t delay_timer = 0;
    uint8_t sound_timer = 0;


    setup_font(memory);

    //TODO - probably separate all this state into a struct

    return 0;
}