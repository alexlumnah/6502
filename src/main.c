#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"

int main(void) {

    Cpu* cpu = calloc(1, sizeof(Cpu));
    Mem mem;

    reset(cpu, mem);

    dump_cpu(cpu);

    exec(cpu, mem);

    printf("Hello, world!\n");
}
