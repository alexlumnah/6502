#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../src/cpu.h"
#include "cJSON.h"


// Set state of Cpu based on JSON input
void set_state(Cpu *cpu, byte *mem, cJSON *state) {

	// Initialize Cpu
	reset(cpu, mem);

	// Set Cpu State
	cpu->p = (word) cJSON_GetObjectItem(state, "pc")->valueint;
	cpu->s = (byte) cJSON_GetObjectItem(state, "s")->valueint;
	cpu->a = (byte) cJSON_GetObjectItem(state, "a")->valueint;
	cpu->x = (byte) cJSON_GetObjectItem(state, "x")->valueint;
	cpu->y = (byte) cJSON_GetObjectItem(state, "y")->valueint;
    cpu->f = (byte) cJSON_GetObjectItem(state, "p")->valueint;

	// Ram
	cJSON *ram = cJSON_GetObjectItem(state, "ram");
	cJSON *element;
	word loc;
	byte val;
	for(int i=0; i<cJSON_GetArraySize(ram); i++) {
		element = cJSON_GetArrayItem(ram,i);
		loc = cJSON_GetArrayItem(element,0)->valueint;
		val = (byte) cJSON_GetArrayItem(element,1)->valueint;
		mem[loc] = val;
	}

}

// Check state of Cpu against JSON input
bool check_state(Cpu *cpu, byte *mem, cJSON *state, bool verbose) {

	int pass = 1;

	// Check Cpu State
	if(cpu->p != cJSON_GetObjectItem(state, "pc")->valueint) {
		pass = 0;
		if(verbose)
			printf("Unexpected PC. State: %d, Expected: %d\n",
					cpu->p, cJSON_GetObjectItem(state, "pc")->valueint);
	}
	if(cpu->s != cJSON_GetObjectItem(state, "s")->valueint) {
		pass = 0;
		if(verbose)
			printf("Unexpected S. State: %d, Expected: %d\n",
					cpu->s, cJSON_GetObjectItem(state, "s")->valueint);
	}
	if(cpu->a != cJSON_GetObjectItem(state, "a")->valueint) {
		pass = 0;
		if(verbose)
			printf("Unexpected A Register. State: %d, Expected: %d\n",
					cpu->a, cJSON_GetObjectItem(state, "a")->valueint);
	}
	if(cpu->x != cJSON_GetObjectItem(state, "x")->valueint) {
		pass = 0;
		if(verbose)
			printf("Unexpected X Register. State: %d, Expected: %d\n",
					cpu->x, cJSON_GetObjectItem(state, "x")->valueint);
	}
	if(cpu->y != cJSON_GetObjectItem(state, "y")->valueint) {
		pass = 0;
		if(verbose)
			printf("Unexpected Y Register. State: %d, Expected: %d\n",
					cpu->y, cJSON_GetObjectItem(state, "y")->valueint);
	}
	if(cpu->f != cJSON_GetObjectItem(state, "p")->valueint) {
		pass = 0;
		if(verbose) {
			printf("Unexpected F Register. State: %d, Expected: %d\n",
					cpu->f, cJSON_GetObjectItem(state, "p")->valueint);

            // Now determine which flags are off
            int f = (byte) cJSON_GetObjectItem(state, "p")->valueint;
            if(GET_BIT(cpu->f, FLAG_C) != GET_BIT(f, FLAG_C))
                printf("   C FLAG State: %d, Expected: %d\n",
                           GET_BIT(cpu->f, FLAG_C), GET_BIT(f, FLAG_C));
            if(GET_BIT(cpu->f, FLAG_Z) != GET_BIT(f, FLAG_Z))
                printf("   Z FLAG State: %d, Expected: %d\n",
                           GET_BIT(cpu->f, FLAG_Z), GET_BIT(f, FLAG_Z));
            if(GET_BIT(cpu->f, FLAG_I) != GET_BIT(f, FLAG_I))
                printf("   I FLAG State: %d, Expected: %d\n",
                           GET_BIT(cpu->f, FLAG_I), GET_BIT(f, FLAG_I));
            if(GET_BIT(cpu->f, FLAG_D) != GET_BIT(f, FLAG_D))
                printf("   D FLAG State: %d, Expected: %d\n",
                           GET_BIT(cpu->f, FLAG_D), GET_BIT(f, FLAG_D));
            if(GET_BIT(cpu->f, FLAG_B) != GET_BIT(f, FLAG_B))
                printf("   B FLAG State: %d, Expected: %d\n",
                           GET_BIT(cpu->f, FLAG_B), GET_BIT(f, FLAG_B));
            if(GET_BIT(cpu->f, FLAG_V) != GET_BIT(f, FLAG_V))
                printf("   V FLAG State: %d, Expected: %d\n",
                           GET_BIT(cpu->f, FLAG_V), GET_BIT(f, FLAG_V));
            if(GET_BIT(cpu->f, FLAG_N) != GET_BIT(f, FLAG_N))
                printf("   N FLAG State: %d, Expected: %d\n",
                        GET_BIT(cpu->f, FLAG_N), GET_BIT(f, FLAG_N));
        }
	}

	// Ram
	cJSON *ram = cJSON_GetObjectItem(state, "ram");
	cJSON *element;
	word loc;
	byte val;
	for(int i=0; i<cJSON_GetArraySize(ram); i++) {
		element = cJSON_GetArrayItem(ram,i);
		loc = cJSON_GetArrayItem(element,0)->valueint;
		val = (byte) cJSON_GetArrayItem(element,1)->valueint;
		if(mem[loc] != val) {
			pass = false;
			if(verbose)
				printf("Unexpected value at memory location %d. "
                       "State: %d, Expected: %d\n", loc, mem[loc], val);
		}
	}
	return pass;
}

// Run all tests in a file
bool test_opcode(Cpu *cpu, byte *mem, char file[100], bool verbose) {

	// Output true if test passes, false otherwise
	bool pass = true;

	// File variables
	FILE *fileptr;
	char *contents;
	long numbytes;

	// Open file
	fileptr = fopen(file,"r");
	if(fileptr == NULL) {
		printf("Unknown opcode at file: %s",file);
		return 0;
	}

	// Determine length of file to allocate proper string
	fseek(fileptr, 0, SEEK_END);	// Set pointer to end of file
	numbytes = ftell(fileptr);		// Read pointer location
	fseek(fileptr, 0, SEEK_SET);	// Set pointer to start

	// Read file contents into string
	contents = malloc(numbytes);
	fread(contents,sizeof(char),numbytes,fileptr);

	// Close file when done reading
	fclose(fileptr);

	// Parse the JSON
	cJSON *json = cJSON_Parse(contents);
	int numtests = cJSON_GetArraySize(json);

	// Iterate over each test in the file
	cJSON *item;
	for(int i=0; i < numtests; i++){

		// Grab test from json
		item = cJSON_GetArrayItem(json, i);

		// Set state of Cpu and execute instruction
		set_state(cpu, mem, cJSON_GetObjectItem(item,"initial"));
		exec(cpu, mem);

		// Check state
		if (check_state(cpu, mem, cJSON_GetObjectItem(item,"final"),false)) {
			if(verbose)
				printf("Test %d: %s Passed\n",i,
								cJSON_GetArrayItem(item, 0)->valuestring);
		} else {
			pass = false;
			if(verbose) {
				// Output which test fails
				printf("Test %d: %s Failed\n",i,
					cJSON_GetArrayItem(item, 0)->valuestring);

				// If verbosity is ON, rerun check state with verbosity on
				check_state(cpu, mem, cJSON_GetObjectItem(item,"final"),true);

				// Dump state of Cpu and non-zero memory
				printf("\n");
				dump_cpu(cpu);
				printf("\n");
				//dump_nz_mem(mem);
			}
			break;
		}
	}

	// Cleanup, then stop testing this opcode
	cJSON_Delete(json);
	free(contents);

	return pass;
}

// Main
int main(int argc, char* argv[]) {
	/*
	./test <op_code>
	Default: No Opcode will run all tests
	If opcode is supplied, only single test will run in verbose mode
	*/

	// Parse input
	bool run_all;
	char* opcode;
	if (argc == 1) {
		run_all = true;
	} else {
		run_all = false;
		opcode = argv[1];
	}

	// Instantiate and Memory
	Cpu cpu;
	Mem mem;

	// Reset Cpu
	reset(&cpu, mem);

	char file[100]; // String buffer of length 100
	bool pass;
	if(run_all) {
		printf("Executing all opcode tests:\n");
		for(int i=0; i<256; i++) {

			// Generate file name
			sprintf(file,
				 "/Users/lumnah/Documents/c/6502/tests/json/%02x.json",i);

			// Run all instruction tests, with verbosity OFF
			pass = test_opcode(&cpu, mem, file, false);
			printf("Opcode 0x%02x: %s\n",i,pass ? "PASS" : "FAIL");
		}
	} else {
		// Generate file name
		sprintf(file,
			 "/Users/lumnah/Documents/c/6502/tests/json/%s.json",opcode);

		// Run all instruction tests, with verbosity ON
		printf("Testing Opcode %s\n",(opcode));

		pass = test_opcode(&cpu, mem, file, true);

	}

	return 0;
}
