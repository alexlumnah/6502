#define MEM_SIZE 65536

// Define our types
typedef unsigned char BYTE;
typedef unsigned short WORD;

// CPU Structure
typedef struct {
	BYTE A, X, Y;	// Registers
	WORD PC; 		// Program Counter
	BYTE S;			// Stack Pointer

	// Status Register
	BYTE C : 1;	// Carry Flag (1 = True)
	BYTE Z : 1;	// Zero Flag (1 = Result Zero)
	BYTE I : 1; // IRQ Disable (1 = Disable)
	BYTE D : 1; // Decimal Mode (1 = True)
	BYTE B : 1;	// Break Command (1 = BRK)
	BYTE V : 1; // Overflow (1 = True)
	BYTE N : 1; // Negative (1 = Neg)

	long cycles;
} CPU;

// Memory Structure
typedef BYTE Memory[MEM_SIZE];

//CPU Functions
void execute(CPU *cpu, Memory *mem);
void init(CPU *cpu, Memory *mem);
void reset(CPU *cpu, Memory *mem);
void dump_cpu(CPU *cpu);
void dump_zp(Memory *mem);

// Addressing Modes
BYTE ACC(CPU *cpu, Memory *mem);	// Accumulator
BYTE ABS(CPU *cpu, Memory *mem);	// Absolute
BYTE ABX(CPU *cpu, Memory *mem);	// Absolute, X-indexed
BYTE ABY(CPU *cpu, Memory *mem);	// Absolute, Y-indexed
BYTE IMM(CPU *cpu, Memory *mem);	// Immediate
BYTE IMP(CPU *cpu, Memory *mem);	// Implied
BYTE IND(CPU *cpu, Memory *mem);	// Indirect
BYTE XIN(CPU *cpu, Memory *mem);	// X-indexed, Indirect
BYTE YIN(CPU *cpu, Memory *mem);	// Indirect, Y-indexed
BYTE REL(CPU *cpu, Memory *mem);	// Relative
BYTE ZPG(CPU *cpu, Memory *mem);	// Zero Page
BYTE ZPX(CPU *cpu, Memory *mem);	// Zero Page, X-Indexed
BYTE ZPY(CPU *cpu, Memory *mem);	// Zero Page, Y-indexed
BYTE XAD(CPU *cpu, Memory *mem);	// Zero Page, Y-indexed


//Instuctions
void ADC(CPU *cpu, Memory *mem, BYTE operand); // add with carry
void AND(CPU *cpu, Memory *mem, BYTE operand); // and (with accumulator)
void ASL(CPU *cpu, Memory *mem, BYTE operand); // arithmetic shift left
void BCC(CPU *cpu, Memory *mem, BYTE operand); // branch on carry clear
void BCS(CPU *cpu, Memory *mem, BYTE operand); // branch on carry set
void BEQ(CPU *cpu, Memory *mem, BYTE operand); // branch on equal (zero set)
void BIT(CPU *cpu, Memory *mem, BYTE operand); // bit test
void BMI(CPU *cpu, Memory *mem, BYTE operand); // branch on minus (negative set)
void BNE(CPU *cpu, Memory *mem, BYTE operand); // branch on not equal (zero clear)
void BPL(CPU *cpu, Memory *mem, BYTE operand); // branch on plus (negative clear)
void BRK(CPU *cpu, Memory *mem, BYTE operand); // break / interrupt
void BVC(CPU *cpu, Memory *mem, BYTE operand); // branch on overflow clear
void BVS(CPU *cpu, Memory *mem, BYTE operand); // branch on overflow set
void CLC(CPU *cpu, Memory *mem, BYTE operand); // clear carry
void CLD(CPU *cpu, Memory *mem, BYTE operand); // clear decimal
void CLI(CPU *cpu, Memory *mem, BYTE operand); // clear interrupt disable
void CLV(CPU *cpu, Memory *mem, BYTE operand); // clear overflow
void CMP(CPU *cpu, Memory *mem, BYTE operand); // compare (with accumulator)
void CPX(CPU *cpu, Memory *mem, BYTE operand); // compare with X
void CPY(CPU *cpu, Memory *mem, BYTE operand); // compare with Y
void DEC(CPU *cpu, Memory *mem, BYTE operand); // decrement
void DEX(CPU *cpu, Memory *mem, BYTE operand); // decrement X
void DEY(CPU *cpu, Memory *mem, BYTE operand); // decrement Y
void EOR(CPU *cpu, Memory *mem, BYTE operand); // exclusive or (with accumulator)
void INC(CPU *cpu, Memory *mem, BYTE operand); // increment
void INX(CPU *cpu, Memory *mem, BYTE operand); // increment X
void INY(CPU *cpu, Memory *mem, BYTE operand); // increment Y
void JMP(CPU *cpu, Memory *mem, BYTE operand); // jump
void JSR(CPU *cpu, Memory *mem, BYTE operand); // jump subroutine
void LDA(CPU *cpu, Memory *mem, BYTE operand); // load accumulator
void LDX(CPU *cpu, Memory *mem, BYTE operand); // load X
void LDY(CPU *cpu, Memory *mem, BYTE operand); // load Y
void LSR(CPU *cpu, Memory *mem, BYTE operand); // logical shift right
void NOP(CPU *cpu, Memory *mem, BYTE operand); // no operation
void ORA(CPU *cpu, Memory *mem, BYTE operand); // or with accumulator
void PHA(CPU *cpu, Memory *mem, BYTE operand); // push accumulator
void PHP(CPU *cpu, Memory *mem, BYTE operand); // push processor status (SR)
void PLA(CPU *cpu, Memory *mem, BYTE operand); // pull accumulator
void PLP(CPU *cpu, Memory *mem, BYTE operand); // pull processor status (SR)
void ROL(CPU *cpu, Memory *mem, BYTE operand); // rotate left
void ROR(CPU *cpu, Memory *mem, BYTE operand); // rotate right
void RTI(CPU *cpu, Memory *mem, BYTE operand); // return from interrupt
void RTS(CPU *cpu, Memory *mem, BYTE operand); // return from subroutine
void SBC(CPU *cpu, Memory *mem, BYTE operand); // subtract with carry
void SEC(CPU *cpu, Memory *mem, BYTE operand); // set carry
void SED(CPU *cpu, Memory *mem, BYTE operand); // set decimal
void SEI(CPU *cpu, Memory *mem, BYTE operand); // set interrupt disable
void STA(CPU *cpu, Memory *mem, BYTE operand); // store accumulator
void STX(CPU *cpu, Memory *mem, BYTE operand); // store X
void STY(CPU *cpu, Memory *mem, BYTE operand); // store Y
void TAX(CPU *cpu, Memory *mem, BYTE operand); // transfer accumulator to X
void TAY(CPU *cpu, Memory *mem, BYTE operand); // transfer accumulator to Y
void TSX(CPU *cpu, Memory *mem, BYTE operand); // transfer stack pointer to X
void TXA(CPU *cpu, Memory *mem, BYTE operand); // transfer X to accumulator
void TXS(CPU *cpu, Memory *mem, BYTE operand); // transfer X to stack pointer
void TYA(CPU *cpu, Memory *mem, BYTE operand); // transfer Y to accumulator
void XXX(CPU *cpu, Memory *mem, BYTE operand); // Null function

// Instructions
typedef struct {
	void (*inst)(CPU*,Memory*,BYTE);	// Instruction Type
	BYTE (*addr)(CPU*,Memory*);			// Addressing Mode
	int cycles;							// Number of base cycles
} OPCODE;

