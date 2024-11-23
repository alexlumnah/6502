#include <assert.h>

#include "opcode.h"

// Addressing Modes
// Accumulator
byte acc(Cpu *cpu, byte *mem) {
    assert("addressing mode not yet implemented" && false);
    return 0;
}

// Absolute Address
byte aba(Cpu *cpu, byte *mem) {
    assert("addressing mode not yet implemented" && false);
    return 0;
}

// Absolute, X-indexed
byte abx(Cpu *cpu, byte *mem) {
    assert("addressing mode not yet implemented" && false);
    return 0;
}

// Absolute, Y-indexed
byte aby(Cpu *cpu, byte *mem) {
    assert("addressing mode not yet implemented" && false);
    return 0;
}

// Immediate
byte imm(Cpu *cpu, byte *mem) {
    assert("addressing mode not yet implemented" && false);
    return 0;
}

// Implied
byte imp(Cpu *cpu, byte *mem) {
    assert("addressing mode not yet implemented" && false);
    return 0;
}

// Indirect
byte ind(Cpu *cpu, byte *mem) {
    assert("addressing mode not yet implemented" && false);
    return 0;
}

// X-indexed, Indirect
byte xin(Cpu *cpu, byte *mem) {
    assert("addressing mode not yet implemented" && false);
    return 0;
}

// Indirect, Y-indexed
byte yin(Cpu *cpu, byte *mem) {
    assert("addressing mode not yet implemented" && false);
    return 0;
}

// Relative
byte rel(Cpu *cpu, byte *mem) {
    assert("addressing mode not yet implemented" && false);
    return 0;
}

// Zero Page
byte zpg(Cpu *cpu, byte *mem) {
    assert("addressing mode not yet implemented" && false);
    return 0;
}

// Zero Page, X-Indexed
byte zpx(Cpu *cpu, byte *mem) {
    assert("addressing mode not yet implemented" && false);
    return 0;
}

// Zero Page, Y-indexed
byte zpy(Cpu *cpu, byte *mem) {
    assert("addressing mode not yet implemented" && false);
    return 0;
}

// Zero Page, Y-indexed
byte xad(Cpu *cpu, byte *mem) {
    assert("addressing mode not yet implemented" && false);
    return 0;
}


// Instructions
// test and reset bits with acc
void trb(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// push index Y on stack
void phy(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// push index X on stack
void phx(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// pull index Y from stack
void ply(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// pull index X from stack
void plx(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// store zero in memory
void stz(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// branch always
void bra(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// add with carry
void adc(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// and (with accumulator)
void and(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// arithmetic shift left
void asl(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// branch on carry clear
void bcc(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// branch on carry set
void bcs(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// branch on equal (zero set)
void beq(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// bit test
void bit(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// branch on minus (negative set)
void bmi(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// branch on not equal (zero clear)
void bne(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// branch on plus (negative clear)
void bpl(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// break / interrupt
void brk(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// branch on overflow clear
void bvc(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// branch on overflow set
void bvs(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// clear carry
void clc(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// clear decimal
void cld(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// clear interrupt disable
void cli(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// clear overflow
void clv(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// compare (with accumulator)
void cmp(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// compare with X
void cpx(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// compare with Y
void cpy(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// decrement
void dec(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// decrement X
void dex(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// decrement Y
void dey(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// exclusive or (with accumulator)
void eor(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// increment
void inc(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// increment X
void inx(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// increment Y
void iny(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// jump
void jmp(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// jump subroutine
void jsr(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// load accumulator
void lda(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// load X
void ldx(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// load Y
void ldy(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// logical shift right
void lsr(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// no operation
void nop(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// or with accumulator
void ora(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// push accumulator
void pha(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// push processor status (SR)
void php(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// pull accumulator
void pla(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// pull processor status (SR)
void plp(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// rotate left
void rol(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// rotate right
void ror(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// return from interrupt
void rti(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// return from subroutine
void rts(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// subtract with carry
void sbc(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// set carry
void sec(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// set decimal
void sed(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// set interrupt disable
void sei(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// store accumulator
void sta(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// store X
void stx(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// store Y
void sty(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// transfer accumulator to X
void tax(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// transfer accumulator to Y
void tay(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// test and set memory bits with ac
void tsb(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// transfer stack pointer to X
void tsx(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// transfer X to accumulator
void txa(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// transfer X to stack pointer
void txs(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// transfer Y to accumulator
void tya(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
}

// null function
void xxx(Cpu *cpu, byte *mem, byte op) {
    assert("instruction not yet implemented" && false);
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

