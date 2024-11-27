#include <assert.h>
#include <stdio.h>

#include "opcode.h"

// Helper Functions
// Read word from memory - little-endian
word read_word(byte *mem, word addr) {

    // Little-endian format
    return mem[addr] + (mem[(addr + 1) % MEM_SIZE] << 8);
}

// Read word from zp memory (wrap around at boundary) - little endian
word read_word_zp(byte *mem, word addr) {

    // Little-endian format
    return mem[addr % 256] + (mem[(addr + 1) % 256] << 8);
}

// Push onto stack
void push(Cpu *cpu, byte *mem, byte val) {
    
    mem[STACK_TOP + cpu->s--] = val;
}

// Pop from stack
byte pop(Cpu *cpu, byte *mem) {

    return mem[STACK_TOP + ++cpu->s];
}

// Pop status register from stack
byte popf(Cpu *cpu, byte *mem) {

    byte status = pop(cpu, mem);
    // Ignore BRK bit, and keep bit 5 the same
    status &= ~MASK_B;
    status |= (cpu->f & MASK_5);

    return status;
}

// Set N, Z Flags
void nz_flags(Cpu *cpu, byte reg) {

    if (reg == 0) {
        SET_BIT(cpu->f, FLAG_Z);
    } else {
        CLR_BIT(cpu->f, FLAG_Z);
    }

    if (SIGN(reg) == 1) {
        SET_BIT(cpu->f, FLAG_N);
    } else {
        CLR_BIT(cpu->f, FLAG_N);
    }
}

// Addressing Modes
// Accumulator
void acc(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    cpu->acc_mode = true;

    // Return value stored in accumulator
    cpu->op = cpu->a;
}

// Absolute Address
void aba(Cpu *cpu, byte *mem) {

    cpu->acc_mode = false;

    // Get operand from address from next two bytes
    cpu->addr = read_word(mem, cpu->p);
    cpu->p += 2;
    cpu->op = mem[cpu->addr];
}

// Absolute, X-indexed
void abx(Cpu *cpu, byte *mem) {

    cpu->acc_mode = false;

    // Get address from next two bytes
    cpu->addr = read_word(mem, cpu->p);
    cpu->p += 2;

    // Index address by the x register
    cpu->addr += cpu->x;
    cpu->op = mem[cpu->addr];
}

// Absolute, Y-indexed
void aby(Cpu *cpu, byte *mem) {

    cpu->acc_mode = false;

    // Get address from next two bytes
    cpu->addr = read_word(mem, cpu->p);
    cpu->p += 2;

    // Index address by the y register
    cpu->addr += cpu->y;
    cpu->op = mem[cpu->addr];
}

// Immediate
void imm(Cpu *cpu, byte *mem) {

    cpu->acc_mode = false;

    // Opcode is next immediate byte
    cpu->addr = cpu->p;
    cpu->p++;
    cpu->op = mem[cpu->addr];
}

// Implied
void imp(Cpu *cpu, byte *mem) {
    
    (void) mem;     // Suppress warnings

    // Opcode is acc_modeied by the instruction
    cpu->acc_mode = true;
}

// Indirect
void ind(Cpu *cpu, byte *mem) {
    
    cpu->acc_mode = false;

    // Next two bytes are a pointer to an address
    word ptr = read_word(mem, cpu->p);
    cpu->p += 2;

    // Get address from the pointer
    // Indirect addressing mode works only on a single page
    // If we cross a boundary, loop back to beginning of page
    byte lo = (ptr & 0x00ff) + 1;
    byte hi = (ptr & 0xff00) >> 8;
    cpu->addr = mem[ptr] + (mem[(hi << 8) + lo] << 8);
    cpu->op = mem[cpu->addr];
}

// X-indexed, Indirect
void xin(Cpu *cpu, byte *mem) {

    cpu->acc_mode = false;

    // Zero page contains a table of addresses
    // Address of table is next byte
    // X register is added to it
    byte ptr = mem[cpu->p];
    cpu->p++;

    // Index by X register
    ptr += cpu->x;

    // Get address from the pointer
    cpu->addr = read_word_zp(mem, ptr);
    cpu->op = mem[cpu->addr];
}

// Indirect, Y-indexed
void yin(Cpu *cpu, byte *mem) {
    
    cpu->acc_mode = false;

    // Pointer to first byte of 16-bit address
    word ptr = (word)mem[cpu->p];
    cpu->p++;
    cpu->addr = read_word_zp(mem, ptr);

    // Index with y-register
    cpu->addr += cpu->y;
    cpu->op = mem[cpu->addr];
}

// Relative
void rel(Cpu *cpu, byte *mem) {

    cpu->acc_mode = false;

    // Next byte contains a signed offset
    cpu->addr = cpu->p;
    cpu->p++;
    cpu->op = mem[cpu->addr];
}

// Zero Page
void zpg(Cpu *cpu, byte *mem) {

    cpu->acc_mode = false;

    // Next byte contains location on zero page
    cpu->addr = mem[cpu->p];
    cpu->p++;
    cpu->op = mem[cpu->addr];
}

// Zero Page, X-Indexed
void zpx(Cpu *cpu, byte *mem) {

    cpu->acc_mode = false;

    // Next byte contains location on zero page
    cpu->addr = mem[cpu->p];
    cpu->p++;

    // Indexed by x-register
    cpu->addr = (cpu->addr + cpu->x) % 256;
    cpu->op = mem[cpu->addr];
}

// Zero Page, Y-indexed
void zpy(Cpu *cpu, byte *mem) {

    cpu->acc_mode = false;

    // Next byte contains location on zero page
    cpu->addr = mem[cpu->p];
    cpu->p++;

    // Indexed by y-register
    cpu->addr = (cpu->addr + cpu->y) % 256;
    cpu->op = mem[cpu->addr];
}

// Null Addressing Mode - invalid opcode
void xad(Cpu *cpu, byte *mem) {

    (void) cpu;     // Suppress warnings
    (void) mem;     // Suppress warnings

    assert("Invalid opcode\n");
}


// Instructions
// add with carry
void adc(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    // Calculate binary sum for both modes, set N and Z flags
    byte carry = GET_BIT(cpu->f, FLAG_C);
    byte sum = cpu->a + cpu->op + carry;
    nz_flags(cpu, sum);
    
    // Binary Mode
    if (GET_BIT(cpu->f, FLAG_D) == 0) {

        // Carry Flag - Set if sum is smaller than either operand
        if (sum < cpu->a || sum < cpu->op) {
            SET_BIT(cpu->f, FLAG_C);
        } else {
            CLR_BIT(cpu->f, FLAG_C);
        }

        // Overflow Flag - set if adding two numbers of the same sign
        // and the sign of the result does not match
        if ((SIGN(cpu->a) == SIGN(cpu->op)) &&
            (SIGN(cpu->a) != SIGN(sum))) {
            SET_BIT(cpu->f, FLAG_V);
        } else {
            CLR_BIT(cpu->f, FLAG_V);
        }

        // Store Results
        cpu->a = sum;

    // BCD Mode
    } else { 

        // Operate on lo and hi nibble separately
        byte lo = (cpu->a & 0x0f) + (cpu->op & 0x0f) + carry;
        byte hi = (((cpu->a & 0xf0) >> 4) + ((cpu->op & 0xf0) >> 4));

        // Carry from low nibble to hi, if lo > 9
        if (lo > 9) {
            lo -= 10;
            hi++;
        }

        // 6502 Idiosyncracy - N and V flags set on intermediate result 
        byte int_res = (hi << 4) + (lo & 0x0f);
        if (SIGN(int_res) == 1) {
            SET_BIT(cpu->f, FLAG_N);
        } else {
            CLR_BIT(cpu->f, FLAG_N);
        }
        if ((SIGN(cpu->a)  == SIGN(cpu->op)) &&
            (SIGN(cpu->op) != SIGN(int_res))) {
            SET_BIT(cpu->f, FLAG_V);
        } else {
            CLR_BIT(cpu->f, FLAG_V);
        }

        // Correct overflow in hi nibble
        if (hi > 9) {
            hi -= 10;
            SET_BIT(cpu->f, FLAG_C);
        } else {
            CLR_BIT(cpu->f, FLAG_C);
        }

        // Store result
        cpu->a = (hi << 4) + (lo & 0x0f);
    }
}

// and (with accumulator)
void and(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings
    
    cpu->a = cpu->a & cpu->op;
    nz_flags(cpu, cpu->a);
}

// arithmetic shift left
void asl(Cpu *cpu, byte *mem) {

    // Calculate result
    byte result = cpu->op << 1;
    
    // Set flags
    nz_flags(cpu, result);
    if (cpu->op >> 7) {
        SET_BIT(cpu->f, FLAG_C);
    } else {
        CLR_BIT(cpu->f, FLAG_C);
    }

    // Store result
    if (cpu->acc_mode) {
        cpu->a = result;
    } else {
        mem[cpu->addr] = result;
    }
}

// branch on carry clear
void bcc(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings
    
    if (GET_BIT(cpu->f, FLAG_C) == 0)
        cpu->p += (int8_t)cpu->op;
}

// branch on carry set
void bcs(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    if (GET_BIT(cpu->f, FLAG_C) == 1)
        cpu->p += (int8_t)cpu->op;
}

// branch on equal (zero set)
void beq(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    if (GET_BIT(cpu->f, FLAG_Z) == 1)
        cpu->p += (int8_t)cpu->op;
}

// bit test
void bit(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings
    
    byte result = cpu->a & cpu->op;

    // Set flags
    if (result == 0) {
        SET_BIT(cpu->f, FLAG_Z);
    } else {
        CLR_BIT(cpu->f, FLAG_Z);
    }

    if (GET_BIT(cpu->op, 6)) {
        SET_BIT(cpu->f, FLAG_V);
    } else {
        CLR_BIT(cpu->f, FLAG_V);
    }

    if (SIGN(cpu->op)) {
        SET_BIT(cpu->f, FLAG_N);
    } else {
        CLR_BIT(cpu->f, FLAG_N);
    }
}

// branch on minus (negative set)
void bmi(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    if (GET_BIT(cpu->f, FLAG_N) == 1)
        cpu->p += (int8_t)cpu->op;
}

// branch on not equal (zero clear)
void bne(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    if (GET_BIT(cpu->f, FLAG_Z) == 0)
        cpu->p += (int8_t)cpu->op;
}

// branch on plus (negative clear)
void bpl(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    if (GET_BIT(cpu->f, FLAG_N) == 1)
        cpu->p += (int8_t)cpu->op;
}

// break / interrupt
void brk(Cpu *cpu, byte *mem) {
    
    SET_BIT(cpu->f, FLAG_B);

    // Push status and program counter
    cpu->p++;
    push(cpu, mem, (cpu->p & 0xff00) >> 8);
    push(cpu, mem, (cpu->p & 0x00ff));
    push(cpu, mem, cpu->f);

    // Clear break flag and set interrupt disable
    CLR_BIT(cpu->f, FLAG_B);
    SET_BIT(cpu->f, FLAG_I);
    
    // Set program counter to interrupt vector
    cpu->p = read_word(mem, VEC_IRQ);
}

// branch on overflow clear
void bvc(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    if (GET_BIT(cpu->f, FLAG_V) == 0)
        cpu->p += (int8_t)cpu->op;
}

// branch on overflow set
void bvs(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    if (GET_BIT(cpu->f, FLAG_V) == 1)
        cpu->p += (int8_t)cpu->op;
}

// clear carry
void clc(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    CLR_BIT(cpu->f, FLAG_C);
}

// clear decimal
void cld(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    CLR_BIT(cpu->f, FLAG_D);
}

// clear interrupt disable
void cli(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    CLR_BIT(cpu->f, FLAG_I);
}

// clear overflow
void clv(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    CLR_BIT(cpu->f, FLAG_V);
}

// compare (with accumulator)
void cmp(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    byte result = cpu->a - cpu->op;

    // Flags
    nz_flags(cpu, result);
    if (cpu->a >= cpu->op) {
        SET_BIT(cpu->f, FLAG_C);
    } else {
        CLR_BIT(cpu->f, FLAG_C);
    }
}

// compare with X
void cpx(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    byte result = cpu->x - cpu->op;

    // Flags
    nz_flags(cpu, result);
    if (cpu->x >= cpu->op) {
        SET_BIT(cpu->f, FLAG_C);
    } else {
        CLR_BIT(cpu->f, FLAG_C);
    }
}

// compare with Y
void cpy(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    byte result = cpu->y - cpu->op;

    // Flags
    nz_flags(cpu, result);
    if (cpu->y >= cpu->op) {
        SET_BIT(cpu->f, FLAG_C);
    } else {
        CLR_BIT(cpu->f, FLAG_C);
    }
}

// decrement
void dec(Cpu *cpu, byte *mem) {

    byte result = cpu->op - 1;
    nz_flags(cpu, result);
    mem[cpu->addr] = result;
}

// decrement X
void dex(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    byte result = cpu->x - 1;
    nz_flags(cpu, result);
    cpu->x = result;
}

// decrement Y
void dey(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    byte result = cpu->y - 1;
    nz_flags(cpu, result);
    cpu->y = result;
}

// exclusive or (with accumulator)
void eor(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    byte result = cpu->a ^ cpu->op;
    nz_flags(cpu, result);
    cpu->a = result;
}

// increment
void inc(Cpu *cpu, byte *mem) {

    byte result = cpu->op + 1;
    nz_flags(cpu, result);
    mem[cpu->addr] = result;
}

// increment X
void inx(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    byte result = cpu->x + 1;
    nz_flags(cpu, result);
    cpu->x = result;
}

// increment Y
void iny(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    byte result = cpu->y + 1;
    nz_flags(cpu, result);
    cpu->y = result;
}

// jump
void jmp(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    // Jump to absolute or indirect address
    cpu->p = cpu->addr;
}

// jump subroutine
void jsr(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    // Push first byte of pc - 1 first, then handle idio
    cpu->p--;
    push(cpu, mem, (cpu->p & 0xff00) >> 8);

    // 6502 Idiosyncrasy - if address is located in stack
    // it can be overwritten. Re-load address to handle.
    cpu->p--;
    aba(cpu, mem);
    cpu->p--;

    // Push second byte
    push(cpu, mem, (cpu->p & 0x00ff));

    // Set address to absolute value
    cpu->p = cpu->addr;
}

// load accumulator
void lda(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    cpu->a = cpu->op;
    nz_flags(cpu, cpu->a);
}

// load X
void ldx(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    cpu->x = cpu->op;
    nz_flags(cpu, cpu->x);
}

// load Y
void ldy(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    cpu->y = cpu->op;
    nz_flags(cpu, cpu->y);
}

// logical shift right
void lsr(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    // Calculate result
    byte result = cpu->op >> 1;
    
    // Set flags
    nz_flags(cpu, result);
    if (cpu->op & 1) {
        SET_BIT(cpu->f, FLAG_C);
    } else {
        CLR_BIT(cpu->f, FLAG_C);
    }

    // Store result
    if (cpu->acc_mode) {
        cpu->a = result;
    } else {
        mem[cpu->addr] = result;
    }
}

// no operation
void nop(Cpu *cpu, byte *mem) {
    // Do nothing
    (void) cpu;
    (void) mem;
}

// or with accumulator
void ora(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    cpu->a |= cpu->op;
    nz_flags(cpu, cpu->a);
}

// push accumulator
void pha(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    push(cpu, mem, cpu->a);
}

// push processor status (SR)
void php(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    // Set BRK bit when pushing
    push(cpu, mem, cpu->f | MASK_B);
}

// pull accumulator
void pla(Cpu *cpu, byte *mem) {

    cpu->a = pop(cpu, mem);
    nz_flags(cpu, cpu->a);
}

// pull processor status (SR)
void plp(Cpu *cpu, byte *mem) {

    cpu->f = popf(cpu, mem);
}

// rotate left
void rol(Cpu *cpu, byte *mem) {

    // Calculate result
    byte carry = GET_BIT(cpu->f, FLAG_C);
    byte result = (cpu->op << 1) + carry;
    
    // Set flags
    nz_flags(cpu, result);
    if (GET_BIT(cpu->op, 7) == 1) {
        SET_BIT(cpu->f, FLAG_C);
    } else {
        CLR_BIT(cpu->f, FLAG_C);
    }

    // Store result
    if (cpu->acc_mode) {
        cpu->a = result;
    } else {
        mem[cpu->addr] = result;
    }
}

// rotate right
void ror(Cpu *cpu, byte *mem) {

    // Calculate result
    byte carry = GET_BIT(cpu->f, FLAG_C);
    byte result = (cpu->op >> 1) + (carry << 7);
    
    // Set flags
    nz_flags(cpu, result);
    if (GET_BIT(cpu->op, 0) == 1) {
        SET_BIT(cpu->f, FLAG_C);
    } else {
        CLR_BIT(cpu->f, FLAG_C);
    }

    // Store result
    if (cpu->acc_mode) {
        cpu->a = result;
    } else {
        mem[cpu->addr] = result;
    }
}

// return from interrupt
void rti(Cpu *cpu, byte *mem) {

    cpu->f  = popf(cpu, mem);
    cpu->p  = pop(cpu, mem);
    cpu->p += pop(cpu, mem) << 8;
}

// return from subroutine
void rts(Cpu *cpu, byte *mem) {

    cpu->p  = pop(cpu, mem);
    cpu->p += pop(cpu, mem) << 8;
    cpu->p += 1;
}

// subtract with carry
void sbc(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    // Calculate binary sum for both modes, set N and Z flags
    byte carry = GET_BIT(cpu->f, FLAG_C);
    byte diff = cpu->a - cpu->op - !carry;

    // Set flags - same for both binary and decimal
    nz_flags(cpu, diff);
    
    // Carry Flag - Cleared if it was used for subtraction
    if ((cpu->op + !carry) > cpu->a) {
        CLR_BIT(cpu->f, FLAG_C);
    } else {
        SET_BIT(cpu->f, FLAG_C);
    }

    // Overflow Flag - Treat like addition of two's complement
    if ((SIGN(cpu->a) == !SIGN(cpu->op)) &&
        (SIGN(cpu->a) != SIGN(diff))) {
        SET_BIT(cpu->f, FLAG_V);
    } else {
        CLR_BIT(cpu->f, FLAG_V);
    }


    // Binary Mode
    if (GET_BIT(cpu->f, FLAG_D) == 0) {

        // Store Results
        cpu->a = diff;

    // BCD Mode
    } else { 

        // Operate on lo and hi nibble separately
        byte lo = (cpu->a & 0x0f) - (cpu->op & 0x0f) - !carry;
        byte hi = (((cpu->a & 0xf0) >> 4) - ((cpu->op & 0xf0) >> 4));

        // Carry from lo nibble to hi if overflowing
        if (GET_BIT(lo, 4) == 1) {
            lo += 10;
            hi--;
        }
        // Correct overflow in hi nibble
        if (GET_BIT(hi, 4) == 1) {
            hi += 10;
        }

        // Store result
        cpu->a = (hi << 4) + (lo & 0x0f);
    }
}

// set carry
void sec(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings
    
    SET_BIT(cpu->f, FLAG_C);
}

// set decimal
void sed(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings
    
    SET_BIT(cpu->f, FLAG_D);
}

// set interrupt disable
void sei(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings
    
    SET_BIT(cpu->f, FLAG_I);
}

// store accumulator
void sta(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings
    
    mem[cpu->addr] = cpu->a;
}

// store X
void stx(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    mem[cpu->addr] = cpu->x;
}

// store Y
void sty(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    mem[cpu->addr] = cpu->y;
}

// transfer accumulator to X
void tax(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings
    
    cpu->x = cpu->a;
    nz_flags(cpu, cpu->x);
}

// transfer accumulator to Y
void tay(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings
    
    cpu->y = cpu->a;
    nz_flags(cpu, cpu->y);
}

// transfer stack pointer to X
void tsx(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    cpu->x = cpu->s;
    nz_flags(cpu, cpu->x);
}

// transfer X to accumulator
void txa(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    cpu->a = cpu->x;
    nz_flags(cpu, cpu->a);
}

// transfer X to stack pointer
void txs(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    cpu->s = cpu->x;
}

// transfer Y to accumulator
void tya(Cpu *cpu, byte *mem) {

    (void) mem;     // Suppress warnings

    cpu->a = cpu->y;
    nz_flags(cpu, cpu->a);
}

// null function
void xxx(Cpu *cpu, byte *mem) {

    (void) cpu;     // Suppress warnings
    (void) mem;     // Suppress warnings
    // Do nothing
}

const Opcode opcodes[256] = {
	{&brk, &imp, 5},{&ora, &xin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&ora, &zpg, 5},{&asl, &zpg, 5},{&xxx, &xad, 0},{&php, &imp, 5},{&ora, &imm, 5},{&asl, &acc, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&ora, &aba, 5},{&asl, &aba, 5},{&xxx, &xad, 0},
	{&bpl, &rel, 5},{&ora, &yin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&ora, &zpx, 5},{&asl, &zpx, 5},{&xxx, &xad, 0},{&clc, &imp, 5},{&ora, &aby, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&ora, &abx, 5},{&asl, &abx, 5},{&xxx, &xad, 0},
	{&jsr, &aba, 5},{&and, &xin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&bit, &zpg, 5},{&and, &zpg, 5},{&rol, &zpg, 5},{&xxx, &xad, 0},{&plp, &imp, 5},{&and, &imm, 5},{&rol, &acc, 5},{&xxx, &xad, 0},{&bit, &aba, 5},{&and, &aba, 5},{&rol, &aba, 5},{&xxx, &xad, 0},
	{&bmi, &rel, 5},{&and, &yin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&and, &zpx, 5},{&rol, &zpx, 5},{&xxx, &xad, 0},{&sec, &imp, 5},{&and, &aby, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&and, &abx, 5},{&rol, &abx, 5},{&xxx, &xad, 0},
	{&rti, &imp, 5},{&eor, &xin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&eor, &zpg, 5},{&lsr, &zpg, 5},{&xxx, &xad, 0},{&pha, &imp, 5},{&eor, &imm, 5},{&lsr, &acc, 5},{&xxx, &xad, 0},{&jmp, &aba, 5},{&eor, &aba, 5},{&lsr, &aba, 5},{&xxx, &xad, 0},
	{&bvc, &rel, 5},{&eor, &yin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&eor, &zpx, 5},{&lsr, &zpx, 5},{&xxx, &xad, 0},{&cli, &imp, 5},{&eor, &aby, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&eor, &abx, 5},{&lsr, &abx, 5},{&xxx, &xad, 0},
	{&rts, &imp, 5},{&adc, &xin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&adc, &zpg, 5},{&ror, &zpg, 5},{&xxx, &xad, 0},{&pla, &imp, 5},{&adc, &imm, 5},{&ror, &acc, 5},{&xxx, &xad, 0},{&jmp, &ind, 5},{&adc, &aba, 5},{&ror, &aba, 5},{&xxx, &xad, 0},
	{&bvs, &rel, 5},{&adc, &yin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&adc, &zpx, 5},{&ror, &zpx, 5},{&xxx, &xad, 0},{&sei, &imp, 5},{&adc, &aby, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&adc, &abx, 5},{&ror, &abx, 5},{&xxx, &xad, 0},
	{&xxx, &xad, 0},{&sta, &xin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&sty, &zpg, 5},{&sta, &zpg, 5},{&stx, &zpg, 5},{&xxx, &xad, 0},{&dey, &imp, 5},{&xxx, &xad, 0},{&txa, &imp, 5},{&xxx, &xad, 0},{&sty, &aba, 5},{&sta, &aba, 5},{&stx, &aba, 5},{&xxx, &xad, 0},
	{&bcc, &rel, 5},{&sta, &yin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&sty, &zpx, 5},{&sta, &zpx, 5},{&stx, &zpy, 5},{&xxx, &xad, 0},{&tya, &imp, 5},{&sta, &aby, 5},{&txs, &imp, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&sta, &abx, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},
	{&ldy, &imm, 5},{&lda, &xin, 5},{&ldx, &imm, 5},{&xxx, &xad, 0},{&ldy, &zpg, 5},{&lda, &zpg, 5},{&ldx, &zpg, 5},{&xxx, &xad, 0},{&tay, &imp, 5},{&lda, &imm, 5},{&tax, &imp, 5},{&xxx, &xad, 0},{&ldy, &aba, 5},{&lda, &aba, 5},{&ldx, &aba, 5},{&xxx, &xad, 0},
	{&bcs, &rel, 5},{&lda, &yin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&ldy, &zpx, 5},{&lda, &zpx, 5},{&ldx, &zpy, 5},{&xxx, &xad, 0},{&clv, &imp, 5},{&lda, &aby, 5},{&tsx, &imp, 5},{&xxx, &xad, 0},{&ldy, &abx, 5},{&lda, &abx, 5},{&ldx, &aby, 5},{&xxx, &xad, 0},
	{&cpy, &imm, 5},{&cmp, &xin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&cpy, &zpg, 5},{&cmp, &zpg, 5},{&dec, &zpg, 5},{&xxx, &xad, 0},{&iny, &imp, 5},{&cmp, &imm, 5},{&dex, &imp, 5},{&xxx, &xad, 0},{&cpy, &aba, 5},{&cmp, &aba, 5},{&dec, &aba, 5},{&xxx, &xad, 0},
	{&bne, &rel, 5},{&cmp, &yin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&cmp, &zpx, 5},{&dec, &zpx, 5},{&xxx, &xad, 0},{&cld, &imp, 5},{&cmp, &aby, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&cmp, &abx, 5},{&dec, &abx, 5},{&xxx, &xad, 0},
	{&cpx, &imm, 5},{&sbc, &xin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&cpx, &zpg, 5},{&sbc, &zpg, 5},{&inc, &zpg, 5},{&xxx, &xad, 0},{&inx, &imp, 5},{&sbc, &imm, 5},{&nop, &imp, 5},{&xxx, &xad, 0},{&cpx, &aba, 5},{&sbc, &aba, 5},{&inc, &aba, 5},{&xxx, &xad, 0},
	{&beq, &rel, 5},{&sbc, &yin, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&sbc, &zpx, 5},{&inc, &zpx, 5},{&xxx, &xad, 0},{&sed, &imp, 5},{&sbc, &aby, 5},{&xxx, &xad, 0},{&xxx, &xad, 0},{&xxx, &xad, 0},{&sbc, &abx, 5},{&inc, &abx, 5},{&xxx, &xad, 0}
};

