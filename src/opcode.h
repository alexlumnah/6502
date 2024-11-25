#ifndef INSTR_H
#define INSTR_H

#include "cpu.h"

// Opcode Struct for Lookup
typedef struct {
    void (*inst)(Cpu*, byte*);
    void (*addr)(Cpu*, byte*);
    byte num_cycles;
} Opcode;

// Helper Functions
word read_word(byte *mem, word addr);

// Addressing Modes
void acc(Cpu *cpu, byte *mem);	// Accumulator
void aba(Cpu *cpu, byte *mem);	// Absolute Address
void abx(Cpu *cpu, byte *mem);	// Absolute, X-indexed
void aby(Cpu *cpu, byte *mem);	// Absolute, Y-indexed
void imm(Cpu *cpu, byte *mem);	// Immediate
void imp(Cpu *cpu, byte *mem);	// Implied
void ind(Cpu *cpu, byte *mem);	// Indirect
void xin(Cpu *cpu, byte *mem);	// X-indexed, Indirect
void yin(Cpu *cpu, byte *mem);	// Indirect, Y-indexed
void rel(Cpu *cpu, byte *mem);	// Relative
void zpg(Cpu *cpu, byte *mem);	// Zero Page
void zpx(Cpu *cpu, byte *mem);	// Zero Page, X-Indexed
void zpy(Cpu *cpu, byte *mem);	// Zero Page, Y-indexed
void xad(Cpu *cpu, byte *mem);	// Zero Page, Y-indexed


// Instructions
void adc(Cpu *cpu, byte *mem); // add with carry
void and(Cpu *cpu, byte *mem); // and (with accumulator)
void asl(Cpu *cpu, byte *mem); // arithmetic shift left
void bcc(Cpu *cpu, byte *mem); // branch on carry clear
void bcs(Cpu *cpu, byte *mem); // branch on carry set
void beq(Cpu *cpu, byte *mem); // branch on equal (zero set)
void bit(Cpu *cpu, byte *mem); // bit test
void bmi(Cpu *cpu, byte *mem); // branch on minus (negative set)
void bne(Cpu *cpu, byte *mem); // branch on not equal (zero clear)
void bpl(Cpu *cpu, byte *mem); // branch on plus (negative clear)
void brk(Cpu *cpu, byte *mem); // break / interrupt
void bvc(Cpu *cpu, byte *mem); // branch on overflow clear
void bvs(Cpu *cpu, byte *mem); // branch on overflow set
void clc(Cpu *cpu, byte *mem); // clear carry
void cld(Cpu *cpu, byte *mem); // clear decimal
void cli(Cpu *cpu, byte *mem); // clear interrupt disable
void clv(Cpu *cpu, byte *mem); // clear overflow
void cmp(Cpu *cpu, byte *mem); // compare (with accumulator)
void cpx(Cpu *cpu, byte *mem); // compare with X
void cpy(Cpu *cpu, byte *mem); // compare with Y
void dec(Cpu *cpu, byte *mem); // decrement
void dex(Cpu *cpu, byte *mem); // decrement X
void dey(Cpu *cpu, byte *mem); // decrement Y
void eor(Cpu *cpu, byte *mem); // exclusive or (with accumulator)
void inc(Cpu *cpu, byte *mem); // increment
void inx(Cpu *cpu, byte *mem); // increment X
void iny(Cpu *cpu, byte *mem); // increment Y
void jmp(Cpu *cpu, byte *mem); // jump
void jsr(Cpu *cpu, byte *mem); // jump subroutine
void lda(Cpu *cpu, byte *mem); // load accumulator
void ldx(Cpu *cpu, byte *mem); // load X
void ldy(Cpu *cpu, byte *mem); // load Y
void lsr(Cpu *cpu, byte *mem); // logical shift right
void nop(Cpu *cpu, byte *mem); // no operation
void ora(Cpu *cpu, byte *mem); // or with accumulator
void pha(Cpu *cpu, byte *mem); // push accumulator
void php(Cpu *cpu, byte *mem); // push processor status (SR)
void pla(Cpu *cpu, byte *mem); // pull accumulator
void plp(Cpu *cpu, byte *mem); // pull processor status (SR)
void rol(Cpu *cpu, byte *mem); // rotate left
void ror(Cpu *cpu, byte *mem); // rotate right
void rti(Cpu *cpu, byte *mem); // return from interrupt
void rts(Cpu *cpu, byte *mem); // return from subroutine
void sbc(Cpu *cpu, byte *mem); // subtract with carry
void sec(Cpu *cpu, byte *mem); // set carry
void sed(Cpu *cpu, byte *mem); // set decimal
void sei(Cpu *cpu, byte *mem); // set interrupt disable
void sta(Cpu *cpu, byte *mem); // store accumulator
void stx(Cpu *cpu, byte *mem); // store X
void sty(Cpu *cpu, byte *mem); // store Y
void tax(Cpu *cpu, byte *mem); // transfer accumulator to X
void tay(Cpu *cpu, byte *mem); // transfer accumulator to Y
void tsb(Cpu *cpu, byte *mem); // test and set memory bits with ac
void tsx(Cpu *cpu, byte *mem); // transfer stack pointer to X
void txa(Cpu *cpu, byte *mem); // transfer X to accumulator
void txs(Cpu *cpu, byte *mem); // transfer X to stack pointer
void tya(Cpu *cpu, byte *mem); // transfer Y to accumulator
void xxx(Cpu *cpu, byte *mem); // null function

#endif // INSTR_H

