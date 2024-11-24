#include <stdio.h>

#include "cpu.h"
#include "opcode.h"

// Opcode Lookup Table
extern Opcode opcodes[256];

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
    cpu->p++;

    // TODO - Increment Cycles

    // Grab operand
    byte op = opc.addr(cpu, mem);

    // Perform instruction
    opc.inst(cpu, mem, op);

    return true;
}

// Dump CPU registers
void dump_cpu(Cpu *cpu) {
    printf("CPU = {\n");
    printf("  Registers:\n");
    printf("    [PC] = 0x%02x\n", cpu->p);
    printf("    [AC] = 0x%02x\n", cpu->a);
    printf("    [XR] = 0x%02x\n", cpu->x);
    printf("    [YR] = 0x%02x\n", cpu->y);
    printf("    [SP] = 0x%02x\n", cpu->s);
    printf("    [SR] = 0x%02x\n", cpu->f);
    printf("  Flags:\n");
    printf("    [C] -> %d\n", GET_FLAG(cpu->f, FLG_C));
    printf("    [Z] -> %d\n", GET_FLAG(cpu->f, FLG_Z));
    printf("    [I] -> %d\n", GET_FLAG(cpu->f, FLG_I));
    printf("    [D] -> %d\n", GET_FLAG(cpu->f, FLG_D));
    printf("    [B] -> %d\n", GET_FLAG(cpu->f, FLG_B));
    printf("    [V] -> %d\n", GET_FLAG(cpu->f, FLG_V));
    printf("    [N] -> %d\n", GET_FLAG(cpu->f, FLG_N));
    printf("  Cycle Count: %ld\n", cpu->cycles);
    printf("}\n");
}

void dump_zp(byte *mem);
void dump_mem(byte *mem);

