#include <stdio.h>
#include "cpu.h"

int main() {
	// instantiate
	CPU cpu;
	Memory mem;

	// Initialize and reset CPU
	init(&cpu, &mem);
	reset(&cpu, &mem);
	
	// Inline code
	cpu.A = 0x00;
	cpu.X = 0x02;

	dump_cpu(&cpu);
	printf("\n");
	mem[0x00] = 0x1d;
	mem[0x01] = 0x08;
	mem[0x02] = 0x00;
	mem[0x0A] = 0xf0;
	execute(&cpu, &mem);

	printf("\n");
	dump_cpu(&cpu);
	dump_zp(&mem);
	/*


	printf("%d\n", opcodes[0].cycles);
	// void (*inst)(CPU*, Memory*) = *(inst_set[0].inst);
	// void (*addr)(CPU*, Memory*) = *(inst_set[0].addr);
	// inst(&cpu,&mem);
	// addr(&cpu,&mem);
	(*(opcodes[0].inst))(&cpu,&mem);
	(*(opcodes[0].addr))(&cpu,&mem);*/
	return 0;
}