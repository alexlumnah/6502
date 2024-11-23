#ifndef INSTR_H
#define INSTR_H

#include "cpu.h"

// Opcode Struct for Lookup
typedef struct {
    void (*inst)(Cpu*, byte*, byte);
    byte (*addr)(Cpu*, byte*);
    byte num_cycles;
} Opcode;

// Addressing Modes
byte acc(Cpu *cpu, byte *mem);	// Accumulator
byte aba(Cpu *cpu, byte *mem);	// Absolute Address
byte abx(Cpu *cpu, byte *mem);	// Absolute, X-indexed
byte aby(Cpu *cpu, byte *mem);	// Absolute, Y-indexed
byte imm(Cpu *cpu, byte *mem);	// Immediate
byte imp(Cpu *cpu, byte *mem);	// Implied
byte ind(Cpu *cpu, byte *mem);	// Indirect
byte xin(Cpu *cpu, byte *mem);	// X-indexed, Indirect
byte yin(Cpu *cpu, byte *mem);	// Indirect, Y-indexed
byte rel(Cpu *cpu, byte *mem);	// Relative
byte zpg(Cpu *cpu, byte *mem);	// Zero Page
byte zpx(Cpu *cpu, byte *mem);	// Zero Page, X-Indexed
byte zpy(Cpu *cpu, byte *mem);	// Zero Page, Y-indexed
byte xad(Cpu *cpu, byte *mem);	// Zero Page, Y-indexed


// Instructions
void trb(Cpu *cpu, byte *mem, byte op); // test and reset bits with acc
void phy(Cpu *cpu, byte *mem, byte op); // push index Y on stack
void phx(Cpu *cpu, byte *mem, byte op); // push index X on stack
void ply(Cpu *cpu, byte *mem, byte op); // pull index Y from stack
void plx(Cpu *cpu, byte *mem, byte op); // pull index X from stack
void stz(Cpu *cpu, byte *mem, byte op); // store zero in memory
void bra(Cpu *cpu, byte *mem, byte op); // branch always
void adc(Cpu *cpu, byte *mem, byte op); // add with carry
void and(Cpu *cpu, byte *mem, byte op); // and (with accumulator)
void asl(Cpu *cpu, byte *mem, byte op); // arithmetic shift left
void bcc(Cpu *cpu, byte *mem, byte op); // branch on carry clear
void bcs(Cpu *cpu, byte *mem, byte op); // branch on carry set
void beq(Cpu *cpu, byte *mem, byte op); // branch on equal (zero set)
void bit(Cpu *cpu, byte *mem, byte op); // bit test
void bmi(Cpu *cpu, byte *mem, byte op); // branch on minus (negative set)
void bne(Cpu *cpu, byte *mem, byte op); // branch on not equal (zero clear)
void bpl(Cpu *cpu, byte *mem, byte op); // branch on plus (negative clear)
void brk(Cpu *cpu, byte *mem, byte op); // break / interrupt
void bvc(Cpu *cpu, byte *mem, byte op); // branch on overflow clear
void bvs(Cpu *cpu, byte *mem, byte op); // branch on overflow set
void clc(Cpu *cpu, byte *mem, byte op); // clear carry
void cld(Cpu *cpu, byte *mem, byte op); // clear decimal
void cli(Cpu *cpu, byte *mem, byte op); // clear interrupt disable
void clv(Cpu *cpu, byte *mem, byte op); // clear overflow
void cmp(Cpu *cpu, byte *mem, byte op); // compare (with accumulator)
void cpx(Cpu *cpu, byte *mem, byte op); // compare with X
void cpy(Cpu *cpu, byte *mem, byte op); // compare with Y
void dec(Cpu *cpu, byte *mem, byte op); // decrement
void dex(Cpu *cpu, byte *mem, byte op); // decrement X
void dey(Cpu *cpu, byte *mem, byte op); // decrement Y
void eor(Cpu *cpu, byte *mem, byte op); // exclusive or (with accumulator)
void inc(Cpu *cpu, byte *mem, byte op); // increment
void inx(Cpu *cpu, byte *mem, byte op); // increment X
void iny(Cpu *cpu, byte *mem, byte op); // increment Y
void jmp(Cpu *cpu, byte *mem, byte op); // jump
void jsr(Cpu *cpu, byte *mem, byte op); // jump subroutine
void lda(Cpu *cpu, byte *mem, byte op); // load accumulator
void ldx(Cpu *cpu, byte *mem, byte op); // load X
void ldy(Cpu *cpu, byte *mem, byte op); // load Y
void lsr(Cpu *cpu, byte *mem, byte op); // logical shift right
void nop(Cpu *cpu, byte *mem, byte op); // no operation
void ora(Cpu *cpu, byte *mem, byte op); // or with accumulator
void pha(Cpu *cpu, byte *mem, byte op); // push accumulator
void php(Cpu *cpu, byte *mem, byte op); // push processor status (SR)
void pla(Cpu *cpu, byte *mem, byte op); // pull accumulator
void plp(Cpu *cpu, byte *mem, byte op); // pull processor status (SR)
void rol(Cpu *cpu, byte *mem, byte op); // rotate left
void ror(Cpu *cpu, byte *mem, byte op); // rotate right
void rti(Cpu *cpu, byte *mem, byte op); // return from interrupt
void rts(Cpu *cpu, byte *mem, byte op); // return from subroutine
void sbc(Cpu *cpu, byte *mem, byte op); // subtract with carry
void sec(Cpu *cpu, byte *mem, byte op); // set carry
void sed(Cpu *cpu, byte *mem, byte op); // set decimal
void sei(Cpu *cpu, byte *mem, byte op); // set interrupt disable
void sta(Cpu *cpu, byte *mem, byte op); // store accumulator
void stx(Cpu *cpu, byte *mem, byte op); // store X
void sty(Cpu *cpu, byte *mem, byte op); // store Y
void tax(Cpu *cpu, byte *mem, byte op); // transfer accumulator to X
void tay(Cpu *cpu, byte *mem, byte op); // transfer accumulator to Y
void tsb(Cpu *cpu, byte *mem, byte op); // test and set memory bits with ac
void tsx(Cpu *cpu, byte *mem, byte op); // transfer stack pointer to X
void txa(Cpu *cpu, byte *mem, byte op); // transfer X to accumulator
void txs(Cpu *cpu, byte *mem, byte op); // transfer X to stack pointer
void tya(Cpu *cpu, byte *mem, byte op); // transfer Y to accumulator
void xxx(Cpu *cpu, byte *mem, byte op); // null function

#endif // INSTR_H

