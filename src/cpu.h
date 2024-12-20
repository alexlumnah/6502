#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

// Memory Size
#define MEM_SIZE (0xffff + 1)   // 16-bit Memory Addresses

// System Vectors
#define VEC_NMI (0xfffa)    // Non-Maskable Interrupt Vector (16-bit)
#define VEC_RES (0xfffc)    // Reset Vector (16-bit)
#define VEC_IRQ (0xfffe)    // Interupt Request Vector (16-bit)

#define STACK_TOP (0x0100)  // Top of stack

// Status Flag Bits
#define FLAG_C (0)   // Carry Flag      (1 = Carry True)
#define FLAG_Z (1)   // Zero Flag       (1 = Result Zero)
#define FLAG_I (2)   // Interrupt Flag  (1 = Interrupt Disabled)
#define FLAG_D (3)   // Decimal Flag    (1 = Decimal Mode Active)
#define FLAG_B (4)   // Break Flag      (1 = Status Pushed to Stack)
#define FLAG_V (6)   // Overflow Flag   (1 = Overflow Occurred)
#define FLAG_N (7)   // Negative Flag   (1 = Result Negative)

// Status Flag Bit Masks
#define MASK_C (1 << FLAG_C)
#define MASK_Z (1 << FLAG_Z)
#define MASK_I (1 << FLAG_I)
#define MASK_D (1 << FLAG_D)
#define MASK_B (1 << FLAG_B)
#define MASK_5 (1 << 5)
#define MASK_V (1 << FLAG_V)
#define MASK_N (1 << FLAG_N)

// Status Flag Get/Set/Cear Macros
#define GET_BIT(reg, bit) (((reg) >> (bit)) & 1)
#define SET_BIT(reg, bit)  ((reg) |=  (1 << (bit)))
#define CLR_BIT(reg, bit)  ((reg) &= ~(1 << (bit)))

// Other Useful Macros
#define SIGN(byte) (((byte) >> 7) & 1)

// Standard Data Sizes
typedef uint8_t  byte;
typedef uint16_t word;

// CPU Structure
typedef struct {
    // Registers
    word p;         // Program Counter
    byte a;         // Accumulator
    byte x;         // X Register
    byte y;         // Y Register
    byte s;         // Stack Pointer
    byte f;         // Status Flag Register

    // Internal State
    bool acc_mode;  // Accumulator Address Mode?
    word addr;      // Address of Operand (if not implicit or accumulator)
    byte op;        // Value of Operand (if not implicit or accumulator)
    long cycles;    // CPU Cycles

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
