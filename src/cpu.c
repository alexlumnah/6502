#include <stdio.h>
#include "cpu.h"

// Instruction lookup table
const OPCODE opcodes[65536] = { 
	{&BRK, &IMP, 5},{&ORA, &XIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&ORA, &ZPG, 5},{&ASL, &ZPG, 5},{&XXX, &XAD, 0},{&PHP, &IMP, 5},{&ORA, &IMM, 5},{&ASL, &ACC, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&ORA, &ABS, 5},{&ASL, &ABS, 5},{&XXX, &XAD, 0},
	{&BPL, &REL, 5},{&ORA, &YIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&ORA, &ZPX, 5},{&ASL, &ZPX, 5},{&XXX, &XAD, 0},{&CLC, &IMP, 5},{&ORA, &ABY, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&ORA, &ABX, 5},{&ASL, &ABX, 5},{&XXX, &XAD, 0},
	{&JSR, &ABS, 5},{&AND, &XIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&BIT, &ZPG, 5},{&AND, &ZPG, 5},{&ROL, &ZPG, 5},{&XXX, &XAD, 0},{&PLP, &IMP, 5},{&AND, &IMM, 5},{&ROL, &ACC, 5},{&XXX, &XAD, 0},{&BIT, &ABS, 5},{&AND, &ABS, 5},{&ROL, &ABS, 5},{&XXX, &XAD, 0},
	{&BMI, &REL, 5},{&AND, &YIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&AND, &ZPX, 5},{&ROL, &ZPX, 5},{&XXX, &XAD, 0},{&SEC, &IMP, 5},{&AND, &ABY, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&AND, &ABX, 5},{&ROL, &ABX, 5},{&XXX, &XAD, 0},
	{&RTI, &IMP, 5},{&EOR, &XIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&EOR, &ZPG, 5},{&LSR, &ZPG, 5},{&XXX, &XAD, 0},{&PHA, &IMP, 5},{&EOR, &IMM, 5},{&LSR, &ACC, 5},{&XXX, &XAD, 0},{&JMP, &ABS, 5},{&EOR, &ABS, 5},{&LSR, &ABS, 5},{&XXX, &XAD, 0},
	{&BVC, &REL, 5},{&EOR, &YIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&EOR, &ZPX, 5},{&LSR, &ZPX, 5},{&XXX, &XAD, 0},{&CLI, &IMP, 5},{&EOR, &ABY, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&EOR, &ABX, 5},{&LSR, &ABX, 5},{&XXX, &XAD, 0},
	{&RTS, &IMP, 5},{&ADC, &XIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&ADC, &ZPG, 5},{&ROR, &ZPG, 5},{&XXX, &XAD, 0},{&PLA, &IMP, 5},{&ADC, &IMM, 5},{&ROR, &ACC, 5},{&XXX, &XAD, 0},{&JMP, &IND, 5},{&ADC, &ABS, 5},{&ROR, &ABS, 5},{&XXX, &XAD, 0},
	{&BVS, &REL, 5},{&ADC, &YIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&ADC, &ZPX, 5},{&ROR, &ZPX, 5},{&XXX, &XAD, 0},{&SEI, &IMP, 5},{&ADC, &ABY, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&ADC, &ABX, 5},{&ROR, &ABX, 5},{&XXX, &XAD, 0},
	{&XXX, &XAD, 0},{&STA, &XIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&STY, &ZPG, 5},{&STA, &ZPG, 5},{&STX, &ZPG, 5},{&XXX, &XAD, 0},{&DEY, &IMP, 5},{&XXX, &XAD, 0},{&TXA, &IMP, 5},{&XXX, &XAD, 0},{&STY, &ABS, 5},{&STA, &ABS, 5},{&STX, &ABS, 5},{&XXX, &XAD, 0},
	{&BCC, &REL, 5},{&STA, &YIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&STY, &ZPX, 5},{&STA, &ZPX, 5},{&STX, &ZPY, 5},{&XXX, &XAD, 0},{&TYA, &IMP, 5},{&STA, &ABY, 5},{&TXS, &IMP, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&STA, &ABX, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},
	{&LDY, &IMM, 5},{&LDA, &XIN, 5},{&LDX, &IMM, 5},{&XXX, &XAD, 0},{&LDY, &ZPG, 5},{&LDA, &ZPG, 5},{&LDX, &ZPG, 5},{&XXX, &XAD, 0},{&TAY, &IMP, 5},{&LDA, &IMM, 5},{&TAX, &IMP, 5},{&XXX, &XAD, 0},{&LDY, &ABS, 5},{&LDA, &ABS, 5},{&LDX, &ABS, 5},{&XXX, &XAD, 0},
	{&BCS, &REL, 5},{&LDA, &YIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&LDY, &ZPX, 5},{&LDA, &ZPX, 5},{&LDX, &ZPY, 5},{&XXX, &XAD, 0},{&CLV, &IMP, 5},{&LDA, &ABY, 5},{&TSX, &IMP, 5},{&XXX, &XAD, 0},{&LDY, &ABX, 5},{&LDA, &ABX, 5},{&LDX, &ABY, 5},{&XXX, &XAD, 0},
	{&CPY, &IMM, 5},{&CMP, &XIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&CPY, &ZPG, 5},{&CMP, &ZPG, 5},{&DEC, &ZPG, 5},{&XXX, &XAD, 0},{&INY, &IMP, 5},{&CMP, &IMM, 5},{&DEX, &IMP, 5},{&XXX, &XAD, 0},{&CPY, &ABS, 5},{&CMP, &ABS, 5},{&DEC, &ABS, 5},{&XXX, &XAD, 0},
	{&BNE, &REL, 5},{&CMP, &YIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&CMP, &ZPX, 5},{&DEC, &ZPX, 5},{&XXX, &XAD, 0},{&CLD, &IMP, 5},{&CMP, &ABY, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&CMP, &ABX, 5},{&DEC, &ABX, 5},{&XXX, &XAD, 0},
	{&CPX, &IMM, 5},{&SBC, &XIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&CPX, &ZPG, 5},{&SBC, &ZPG, 5},{&INC, &ZPG, 5},{&XXX, &XAD, 0},{&INX, &IMP, 5},{&SBC, &IMM, 5},{&NOP, &IMP, 5},{&XXX, &XAD, 0},{&CPX, &ABS, 5},{&SBC, &ABS, 5},{&INC, &ABS, 5},{&XXX, &XAD, 0},
	{&BEQ, &REL, 5},{&SBC, &YIN, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&SBC, &ZPX, 5},{&INC, &ZPX, 5},{&XXX, &XAD, 0},{&SED, &IMP, 5},{&SBC, &ABY, 5},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&XXX, &XAD, 0},{&SBC, &ABX, 5},{&INC, &ABX, 5},{&XXX, &XAD, 0}
};


// Execute Instruction
void execute(CPU *cpu, Memory *mem) {

	// Pull Opcode from the address in the program counter
	printf("Contents of PC: 0x%x\n", cpu->PC);

	BYTE code = (*mem)[cpu->PC];
	OPCODE opcode = opcodes[code];
	cpu->PC++;		// Increment PC

	// Print Op Code
	printf("Opcode: 0x%02x\n",code);

	// Fetch operand from address function
	BYTE operand = (opcode.addr)(cpu, mem);
	printf("Operand: 0x%02x\n",operand);

	// Now do operation
	(opcode.inst)(cpu, mem, operand);
	
}

// Initialize CPU and Memory
void init(CPU *cpu, Memory *mem) {
	// Initialize CPU
	cpu->cycles = 0;
	cpu->A = 0;
	cpu->X = 0;
	cpu->Y = 0;
	cpu->PC = 0;
	cpu->S = 0;
	cpu->C = 0;
	cpu->Z = 0;
	cpu->I = 0;
	cpu->D = 0;
	cpu->B = 0;
	cpu->V = 0;
	cpu->N = 0;

	// Initialize Memory
	int i;
	for(i=0; i<MEM_SIZE; i++) {
		(*mem)[i] = 0;	// Operator [] comes before *
	}
}

// Reset CPU
void reset(CPU *cpu, Memory *mem) {
	cpu->cycles += 6;				// Increment Cycles by 6 on reset
	cpu->I = 1; 					// Mask interrupt
	cpu->PC = (*mem)[0xfffd] << 8;	// Initialize Program Counter
	cpu->PC += (*mem)[0xfffc];
}




void dump_cpu(CPU *cpu) {
	// print
	printf("Contents of A: 0x%02x\n", cpu->A);
	printf("Contents of X: 0x%02x\n", cpu->X);
	printf("Contents of Y: 0x%02x\n", cpu->Y);
	printf("Contents of PC: 0x%04x\n", cpu->PC);
	printf("Contents of S: 0x%02x\n", cpu->S);
	printf("Contents of C: 0b%d\n", (BYTE) cpu->C);
	printf("Contents of N: 0b%d\n", (BYTE) cpu->N);
	printf("Contents of Z: 0b%d\n", (BYTE) cpu->Z);
}

void dump_zp(Memory *mem){

	printf("Memory Dump:");
	int i, j;
	for(j=0; j<16; j++) {
		printf("\n%02d: ",j);
		for(i=0; i<16; i++) {
			printf("0x%02x  ",(*mem)[j*16 + i]);
		}
	}
}

/*
Flag methods
*/
void N_Z_Flags(CPU *cpu) {
	// Negative Flag
	if(cpu->A & (1<<7)){
		cpu->N = 1;
	} else {
		cpu->N = 0;
	}

	// Zero Flag
	if(cpu->A == 0x00){
		cpu->Z = 1;
	} else {
		cpu->Z = 0;
	}
}

/*
Addressing Modes
*/

// Accumulator
BYTE ACC(CPU *cpu, Memory *mem) {
	return cpu->A;
}

// Absolute
BYTE ABS(CPU *cpu, Memory *mem) {
	WORD addr = (*mem)[cpu->PC];
	cpu->PC++;
	addr += ((*mem)[cpu->PC] << 8);
	cpu->PC++;

	return (*mem)[addr];
}

// Absolute, X-indexed
BYTE ABX(CPU *cpu, Memory *mem) {
	WORD addr = (*mem)[cpu->PC];
	cpu->PC++;
	addr += ((*mem)[cpu->PC] << 8);
	cpu->PC++;

	addr += cpu->X;
	printf("Address: 0x%02x",addr);
	return (*mem)[addr];
}

// Absolute, Y-indexed
BYTE ABY(CPU *cpu, Memory *mem) {
	WORD addr = (*mem)[cpu->PC];
	cpu->PC++;
	addr += ((*mem)[cpu->PC] << 8);
	cpu->PC++;

	addr += cpu->Y;
	return (*mem)[addr];
}

// Immediate
BYTE IMM(CPU *cpu, Memory *mem) {
	WORD addr = (*mem)[cpu->PC] << 8;
	cpu->PC++;

	return (*mem)[addr];
}

// Implied
BYTE IMP(CPU *cpu, Memory *mem) {
	return 0x00;
}

BYTE IND(CPU *cpu, Memory *mem) {	// Indirect
	BYTE operand = 0x00;
	return operand;
}

BYTE XIN(CPU *cpu, Memory *mem) {	// X-indexed, Indirect
	BYTE operand = 0x00;
	return operand;
}

BYTE YIN(CPU *cpu, Memory *mem) {	// Indirect, Y-indexed
	BYTE operand = 0x00;
	return operand;
}

BYTE REL(CPU *cpu, Memory *mem) {	// Relative
	BYTE operand = 0x00;
	return operand;
}

BYTE ZPG(CPU *cpu, Memory *mem) {	// Zero Page
	BYTE operand = 0x00;
	return operand;
}

BYTE ZPX(CPU *cpu, Memory *mem) {	// Zero Page, X-Indexed
	BYTE operand = 0x00;
	return operand;
}

BYTE ZPY(CPU *cpu, Memory *mem) {	// Zero Page, Y-indexed
	BYTE operand = 0x00;
	return operand;
}

BYTE XAD(CPU *cpu, Memory *mem) {	// Null
	BYTE operand = 0x00;
	return operand;
}


/*
Instuctions
*/
void ADC(CPU *cpu, Memory *mem, BYTE operand) { // add with carry

}

void AND(CPU *cpu, Memory *mem, BYTE operand) { // and (with accumulator)

}

void ASL(CPU *cpu, Memory *mem, BYTE operand) { // arithmetic shift left

}

void BCC(CPU *cpu, Memory *mem, BYTE operand) { // branch on carry clear

}

void BCS(CPU *cpu, Memory *mem, BYTE operand) { // branch on carry set

}

void BEQ(CPU *cpu, Memory *mem, BYTE operand) { // branch on equal (zero set)

}

void BIT(CPU *cpu, Memory *mem, BYTE operand) { // bit test

}

void BMI(CPU *cpu, Memory *mem, BYTE operand) { // branch on minus (negative set)

}

void BNE(CPU *cpu, Memory *mem, BYTE operand) { // branch on not equal (zero clear)

}

void BPL(CPU *cpu, Memory *mem, BYTE operand) { // branch on plus (negative clear)

}

void BRK(CPU *cpu, Memory *mem, BYTE operand) { // break / interrupt

}

void BVC(CPU *cpu, Memory *mem, BYTE operand) { // branch on overflow clear

}

void BVS(CPU *cpu, Memory *mem, BYTE operand) { // branch on overflow set

}

void CLC(CPU *cpu, Memory *mem, BYTE operand) { // clear carry

}

void CLD(CPU *cpu, Memory *mem, BYTE operand) { // clear decimal

}

void CLI(CPU *cpu, Memory *mem, BYTE operand) { // clear interrupt disable

}

void CLV(CPU *cpu, Memory *mem, BYTE operand) { // clear overflow

}

void CMP(CPU *cpu, Memory *mem, BYTE operand) { // compare (with accumulator)

}

void CPX(CPU *cpu, Memory *mem, BYTE operand) { // compare with X

}

void CPY(CPU *cpu, Memory *mem, BYTE operand) { // compare with Y

}

void DEC(CPU *cpu, Memory *mem, BYTE operand) { // decrement

}

void DEX(CPU *cpu, Memory *mem, BYTE operand) { // decrement X

}

void DEY(CPU *cpu, Memory *mem, BYTE operand) { // decrement Y

}

void EOR(CPU *cpu, Memory *mem, BYTE operand) { // exclusive or (with accumulator)

}

void INC(CPU *cpu, Memory *mem, BYTE operand) { // increment

}

void INX(CPU *cpu, Memory *mem, BYTE operand) { // increment X

}

void INY(CPU *cpu, Memory *mem, BYTE operand) { // increment Y

}

void JMP(CPU *cpu, Memory *mem, BYTE operand) { // jump

}

void JSR(CPU *cpu, Memory *mem, BYTE operand) { // jump subroutine

}

void LDA(CPU *cpu, Memory *mem, BYTE operand) { // load accumulator

}

void LDX(CPU *cpu, Memory *mem, BYTE operand) { // load X

}

void LDY(CPU *cpu, Memory *mem, BYTE operand) { // load Y

}

void LSR(CPU *cpu, Memory *mem, BYTE operand) { // logical shift right

}

void NOP(CPU *cpu, Memory *mem, BYTE operand) { // no operation

}

// OR with Accumulator
void ORA(CPU *cpu, Memory *mem, BYTE operand) {

	cpu->A = cpu->A | operand;
	N_Z_Flags(cpu);

}

void PHA(CPU *cpu, Memory *mem, BYTE operand) { // push accumulator

}

void PHP(CPU *cpu, Memory *mem, BYTE operand) { // push processor status (SR)

}

void PLA(CPU *cpu, Memory *mem, BYTE operand) { // pull accumulator

}

void PLP(CPU *cpu, Memory *mem, BYTE operand) { // pull processor status (SR)

}

void ROL(CPU *cpu, Memory *mem, BYTE operand) { // rotate left

}

void ROR(CPU *cpu, Memory *mem, BYTE operand) { // rotate right

}

void RTI(CPU *cpu, Memory *mem, BYTE operand) { // return from interrupt

}

void RTS(CPU *cpu, Memory *mem, BYTE operand) { // return from subroutine

}

void SBC(CPU *cpu, Memory *mem, BYTE operand) { // subtract with carry

}

void SEC(CPU *cpu, Memory *mem, BYTE operand) { // set carry

}

void SED(CPU *cpu, Memory *mem, BYTE operand) { // set decimal

}

void SEI(CPU *cpu, Memory *mem, BYTE operand) { // set interrupt disable

}

void STA(CPU *cpu, Memory *mem, BYTE operand) { // store accumulator

}

void STX(CPU *cpu, Memory *mem, BYTE operand) { // store X

}

void STY(CPU *cpu, Memory *mem, BYTE operand) { // store Y

}

void TAX(CPU *cpu, Memory *mem, BYTE operand) { // transfer accumulator to X

}

void TAY(CPU *cpu, Memory *mem, BYTE operand) { // transfer accumulator to Y

}

void TSX(CPU *cpu, Memory *mem, BYTE operand) { // transfer stack pointer to X

}

void TXA(CPU *cpu, Memory *mem, BYTE operand) { // transfer X to accumulator

}

void TXS(CPU *cpu, Memory *mem, BYTE operand) { // transfer X to stack pointer

}

void TYA(CPU *cpu, Memory *mem, BYTE operand) { // transfer Y to accumulator
}

void XXX(CPU *cpu, Memory *mem, BYTE operand) { // transfer Y to accumulator
}

