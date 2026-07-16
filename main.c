#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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

    printf("Rom bytes at 0x200:\n");
    for (int i = 0; i < 16; i++) {
        printf("0x%02X ", state->memory[0x200 + i]);
    }
    printf("\n");

}

void decode_and_execute(uint16_t instruction, struct State *state) {
    uint8_t first_nibble = (instruction & 0xF000) >> 12;
    uint8_t X = (instruction & 0x0F00) >> 8;
    uint8_t Y = (instruction & 0x00F0) >> 4;
    uint8_t N = (instruction & 0x000F);
    
    uint8_t NN = (instruction & 0x00FF);
    uint8_t NNN = (instruction & 0x0FFF);

    switch (first_nibble) {
        
    }

}

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Usage: %s <rom_file>\n", argv[0]);
        return 1;
    }

    /*STATE SETUP*/
    struct State state;
    init_state(&state);


    /*LOAD ROM*/
    //TODO separate rom loading to its own function
    // maybe this needs some better handling if the file isn't right but I don't care right now
    FILE *rom_file = fopen(argv[1], "rb");
    if (rom_file == NULL) {
        perror("Error opening file");
        return 1;
    } 

    //find the end of file and calculate how big the file is
    fseek(rom_file, 0, SEEK_END); 
    long file_size = ftell(rom_file);
    rewind(rom_file);

    if (file_size > MEM_SIZE - 0x200) {
        printf("ROM file too large");
        return 1;
    }

    size_t bytes_read = fread(state.memory + 0x200, 1, file_size, rom_file);
    if (bytes_read != (size_t)file_size) {
        perror("error reading file");
        fclose(rom_file);
        return 1;
    }

    fclose(rom_file);

    /*FETCH/DECODE/EXECUTE LOOP*/
    while(1) {
        //FETCH
        /*this looks cooked, but to read 2 bytes from memory I read the first one in, then
        shift that over and or with the next byte to combine to one 16 bit value*/
        uint16_t instruction = ((uint16_t)state.memory[state.PC] << 8) | state.memory[state.PC + 1];

        state.PC += 2; //increment program counter to be ready for next 

        //decode and execute
        decode_and_execute(instruction, &state);

    }

    print_state(&state); //debug
    
    return 0;
}