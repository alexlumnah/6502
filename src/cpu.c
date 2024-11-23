#include "cpu.h"
#include "opcode.h"

// Opcode Lookup Table
extern Opcode opcodes[256];

// Read word from memory - little-endian
word read_word(byte *mem, word addr) {

    // Little-endian format
    return mem[addr] + (mem[addr + 1] << 8);

}

// Reset CPU
void reset(Cpu *cpu, byte *mem) {

    // Start sequence cycles
    cpu->cycles += 8;

    // Clear all registers
    cpu->a = 0;
    cpu->x = 0;
    cpu->y = 0;
    cpu->s = 0;
    cpu->f = 0;

    // Read address from reset vector
    cpu->p = read_word(mem, VEC_RES);
}

// Execute next instruction
bool exec(Cpu *cpu, byte *mem) {

    // Fetch / Decode
    Opcode opc = opcodes[mem[cpu->p]];

    // TODO - Increment Cycles

    // Grab operand
    byte op = opc.addr(cpu, mem);

    // Perform instruction
    opc.inst(cpu, mem, op);

    return true;
}

