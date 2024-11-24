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

// Status Flag Bits
#define FLG_C (0)   // Carry Flag      (1 = Carry True)
#define FLG_Z (1)   // Zero Flag       (1 = Result Zero)
#define FLG_I (2)   // Interrupt Flag  (1 = Interrupt Disabled)
#define FLG_D (3)   // Decimal Flag    (1 = Decimal Mode Active)
#define FLG_B (4)   // Break Flag      (1 = Status Pushed to Stack)
#define FLG_V (6)   // Overflow Flag   (1 = Overflow Occurred)
#define FLG_N (7)   // Negative Flag   (1 = Result Negative)

// Status Flag Get/Set/Cear Macros
#define GET_FLAG(reg, flag) ((reg & (1 << flag)) >> flag)
#define SET_FLAG(reg, flag) (reg |=  (1 << flag))
#define CLR_FLAG(reg, flag) (reg &= ~(1 << flag))

// Other Useful Macros
#define SIGN(byte) (byte >> 7)

// Status Flag Bit Masks
#define MSK_C (1 << FLG_C)
#define MSK_Z (1 << FLG_Z)
#define MSK_I (1 << FLG_I)
#define MSK_D (1 << FLG_D)
#define MSK_B (1 << FLG_B)
#define MSK_V (1 << FLG_V)
#define MSK_N (1 << FLG_N)

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

// Memory
typedef byte Mem[MEM_SIZE];

// Functions
void reset(Cpu *cpu, byte *mem);
bool exec(Cpu *cpu, byte *mem);

void dump_cpu(Cpu *cpu);
void dump_zp(byte *mem);
void dump_mem(byte *mem);

#endif  // CPU_H
