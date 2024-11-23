#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

// Memory Size
#define MEM_SIZE (0xffff)   // 16-bit Memory Addresses

// System Vectors
#define VEC_NMI (0xfffa)    // Non-Maskable Interrupt Vector (16-bit)
#define VEC_RES (0xfffc)    // Reset Vector (16-bit)
#define VEC_IRQ (0xfffe)    // Interupt Request Vector (16-bit)

// Status Flag Bit Masks
#define FLAG_C (1 << 0) // Carry Flag      (1 = Carry True)
#define FLAG_Z (1 << 1) // Zero Flag       (1 = Result Zero)
#define FLAG_I (1 << 2) // Interrupt Flag  (1 = Interrupt Disabled)
#define FLAG_D (1 << 3) // Decimal Flag    (1 = Decimal Mode Active)
#define FLAG_B (1 << 4) // Break Flag      (1 = Status Pushed to Stack)
#define FLAG_V (1 << 6) // Overflow Flag   (1 = Overflow Occurred)
#define FLAG_N (1 << 7) // Negative Flag   (1 = Result Negative)

// Standard Data Sizes
typedef uint8_t  byte;
typedef uint16_t word;

// CPU Structure
typedef struct {
    word p;     // Program Counter
    byte a;     // Accumulator
    byte x;     // X Register
    byte y;     // Y Register
    byte s;     // Stack Pointer
    byte f;     // Status Flag Register

    long cycles; // CPU Cycles

} Cpu;

// Memory Bank
typedef byte Mem[MEM_SIZE];

void reset(Cpu *cpu, byte *mem);
bool exec(Cpu *cpu, byte *mem);

#endif  // CPU_H
