#include <assert.h>
#include <stdio.h>

#include "opcode.h"

// Helper Functions
// Read word from memory - little-endian
word read_word(byte *mem, word addr) {

    // Little-endian format
    return mem[addr] + (mem[addr + 1] << 8);

}

// Addressing Modes
// Accumulator
byte acc(Cpu *cpu, byte *mem) {

    // Return value stored in accumulator
    return cpu->a;
}

// Absolute Address
byte aba(Cpu *cpu, byte *mem) {

    // Get address from next two bytes
    word addr = read_word(mem, cpu->p);
    cpu->p += 2;

    // Return value stored at this address
    return mem[addr];
}

// Absolute, X-indexed
byte abx(Cpu *cpu, byte *mem) {

    // Get address from next two bytes
    word addr = read_word(mem, cpu->p);
    cpu->p += 2;

    // Index address by the x register
    addr += cpu->x;

    return mem[addr];
}

// Absolute, Y-indexed
byte aby(Cpu *cpu, byte *mem) {

    // Get address from next two bytes
    word addr = read_word(mem, cpu->p);
    cpu->p += 2;

    // Index address by the x register
    addr += cpu->y;

    return mem[addr];
}

// Immediate
byte imm(Cpu *cpu, byte *mem) {

    // Opcode is next immediate byte
    byte op = mem[cpu->p];
    cpu->p++;

    return op;
}

// Implied
byte imp(Cpu *cpu, byte *mem) {
    
    // Opcode is implied by the instruction
    // Frequently used by the accumulator
    return cpu->a;
}

// Indirect
byte ind(Cpu *cpu, byte *mem) {
    
    // Next two bytes are a pointer to an address
    word ptr = read_word(mem, cpu->p);
    cpu->p += 2;
    word addr = read_word(mem, ptr);

    return mem[addr];
}

// X-indexed, Indirect
byte xin(Cpu *cpu, byte *mem) {

    // Zero page contains a table of addresses
    // Address of table is next byte
    // Z register is added to it
    byte addr = mem[cpu->p];
    cpu->p++;

    addr += cpu->x;

    return mem[(word)addr];
}

// Indirect, Y-indexed
byte yin(Cpu *cpu, byte *mem) {
    
    // Pointer to first byte of 16-bit address
    word ptr = (word)mem[cpu->p];
    cpu->p++;
    word addr = read_word(mem, ptr);

    // Index with y-register
    addr += cpu->y;

    return mem[addr];
}

// Relative
byte rel(Cpu *cpu, byte *mem) {

    // Next byte contains an offset
    int8_t offset = mem[cpu->p];
    cpu->p++;
    word addr = cpu->p + offset;

    return mem[addr];
}

// Zero Page
byte zpg(Cpu *cpu, byte *mem) {

    // Next byte contains location on zero page
    word addr = mem[cpu->p];
    cpu->p++;

    return mem[addr];
}

// Zero Page, X-Indexed
byte zpx(Cpu *cpu, byte *mem) {

    // Next byte contains location on zero page
    word addr = mem[cpu->p];
    cpu->p++;

    // Indexed by x-register
    addr += cpu->x;

    return mem[addr];
}

// Zero Page, Y-indexed
byte zpy(Cpu *cpu, byte *mem) {

    // Next byte contains location on zero page
    word addr = mem[cpu->p];
    cpu->p++;

    // Indexed by y-register
    addr += cpu->y;

    return mem[addr];
}

// Null Addressing Mode - invalid opcode
byte xad(Cpu *cpu, byte *mem) {
    return 0;
}


// Instructions
// test and reset bits with acc
void trb(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'trb' not yet implemented\n");
}

// push index Y on stack
void phy(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'phy' not yet implemented\n");
}

// push index X on stack
void phx(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'phx' not yet implemented\n");
}

// pull index Y from stack
void ply(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'ply' not yet implemented\n");
}

// pull index X from stack
void plx(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'plx' not yet implemented\n");
}

// store zero in memory
void stz(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'stz' not yet implemented\n");
}

// branch always
void bra(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'bra' not yet implemented\n");
}

// add with carry
void adc(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'adc' not yet implemented\n");
}

// and (with accumulator)
void and(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'and' not yet implemented\n");
}

// arithmetic shift left
void asl(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'asl' not yet implemented\n");
}

// branch on carry clear
void bcc(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'bcc' not yet implemented\n");
}

// branch on carry set
void bcs(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'bcs' not yet implemented\n");
}

// branch on equal (zero set)
void beq(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'beq' not yet implemented\n");
}

// bit test
void bit(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'bit' not yet implemented\n");
}

// branch on minus (negative set)
void bmi(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'bmi' not yet implemented\n");
}

// branch on not equal (zero clear)
void bne(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'bne' not yet implemented\n");
}

// branch on plus (negative clear)
void bpl(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'bpl' not yet implemented\n");
}

// break / interrupt
void brk(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'brk' not yet implemented\n");
}

// branch on overflow clear
void bvc(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'bvc' not yet implemented\n");
}

// branch on overflow set
void bvs(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'bvs' not yet implemented\n");
}

// clear carry
void clc(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'clc' not yet implemented\n");
}

// clear decimal
void cld(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'cld' not yet implemented\n");
}

// clear interrupt disable
void cli(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'cli' not yet implemented\n");
}

// clear overflow
void clv(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'clv' not yet implemented\n");
}

// compare (with accumulator)
void cmp(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'cmp' not yet implemented\n");
}

// compare with X
void cpx(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'cpx' not yet implemented\n");
}

// compare with Y
void cpy(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'cpy' not yet implemented\n");
}

// decrement
void dec(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'dec' not yet implemented\n");
}

// decrement X
void dex(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'dex' not yet implemented\n");
}

// decrement Y
void dey(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'dey' not yet implemented\n");
}

// exclusive or (with accumulator)
void eor(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'eor' not yet implemented\n");
}

// increment
void inc(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'inc' not yet implemented\n");
}

// increment X
void inx(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'inx' not yet implemented\n");
}

// increment Y
void iny(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'iny' not yet implemented\n");
}

// jump
void jmp(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'jmp' not yet implemented\n");
}

// jump subroutine
void jsr(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'jsr' not yet implemented\n");
}

// load accumulator
void lda(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'lda' not yet implemented\n");
}

// load X
void ldx(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'ldx' not yet implemented\n");
}

// load Y
void ldy(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'ldy' not yet implemented\n");
}

// logical shift right
void lsr(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'lsr' not yet implemented\n");
}

// no operation
void nop(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'nop' not yet implemented\n");
}

// or with accumulator
void ora(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'ora' not yet implemented\n");
}

// push accumulator
void pha(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'pha' not yet implemented\n");
}

// push processor status (SR)
void php(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'php' not yet implemented\n");
}

// pull accumulator
void pla(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'pla' not yet implemented\n");
}

// pull processor status (SR)
void plp(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'plp' not yet implemented\n");
}

// rotate left
void rol(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'rol' not yet implemented\n");
}

// rotate right
void ror(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'ror' not yet implemented\n");
}

// return from interrupt
void rti(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'rti' not yet implemented\n");
}

// return from subroutine
void rts(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'rts' not yet implemented\n");
}

// subtract with carry
void sbc(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'sbc' not yet implemented\n");
}

// set carry
void sec(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'sec' not yet implemented\n");
}

// set decimal
void sed(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'sed' not yet implemented\n");
}

// set interrupt disable
void sei(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'sei' not yet implemented\n");
}

// store accumulator
void sta(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'sta' not yet implemented\n");
}

// store X
void stx(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'stx' not yet implemented\n");
}

// store Y
void sty(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'sty' not yet implemented\n");
}

// transfer accumulator to X
void tax(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'tax' not yet implemented\n");
}

// transfer accumulator to Y
void tay(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'tay' not yet implemented\n");
}

// test and set memory bits with ac
void tsb(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'tsb' not yet implemented\n");
}

// transfer stack pointer to X
void tsx(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'tsx' not yet implemented\n");
}

// transfer X to accumulator
void txa(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'txa' not yet implemented\n");
}

// transfer X to stack pointer
void txs(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'txs' not yet implemented\n");
}

// transfer Y to accumulator
void tya(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'tya' not yet implemented\n");
}

// null function
void xxx(Cpu *cpu, byte *mem, byte op) {
    //printf("Instruction 'xxx' not yet implemented\n");
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

