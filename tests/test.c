#include <stdio.h>
#include <stdlib.h>

#include "../src/cpu.h"
#include "cJSON.h"

int main() {
	/*
	// Instantiate and Memory
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
	dump_zp(&mem);*/

	// Open file with tests in it
	FILE *fileptr;
	char *contents;
	long numbytes;

	fileptr = fopen("/Users/lumnah/Documents/c/6502/tests/1d.json","r");

	if(fileptr == NULL) {
		printf("Can't open file \n");
	} else {

		// Determine length of file to allocate proper string
		fseek(fileptr, 0, SEEK_END);	// Set pointer to end of file
		numbytes = ftell(fileptr);		// Read pointer location
		fseek(fileptr, 0, SEEK_SET);	// Set pointer to start

		// Read file contents into string
		contents = malloc(numbytes);
		fread(contents,sizeof(char),numbytes,fileptr);

		// Dump file
		// printf("%ld",numbytes);
		// printf("%s",contents);

		// Begin parsing

		// Parse a test
		cJSON *json = cJSON_Parse(contents);
		int numtests = cJSON_GetArraySize(json);

		cJSON *item = cJSON_GetArrayItem(json, 0);

		cJSON *initial_state = cJSON_GetObjectItem(item,"initial");
		cJSON *final_state = cJSON_GetObjectItem(item,"final");



		printf("%d",cJSON_GetObjectItem(initial_state, "pc")->valueint);


	}



	// Close file when done reading
	fclose(fileptr);



	return 0;
}