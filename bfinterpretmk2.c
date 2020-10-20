#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Brainfuck interpreter By Daniel Hannon*/
FILE * fptr;
int main(int argc, char**argv) {
	if (argc == 1) {
		printf("Sorry Buddy it needs to have a file attached!");
		return 1;
	}
	char current = 0;
	char ** array_starts = (char **) malloc(256 * sizeof(char*));
	short int array_depth = 0;
	unsigned char * memory = (char*) malloc (30000 * sizeof(char));
	memset(memory,0,sizeof(memory));
	int memory_pos = 0;
	fptr = fopen(argv[1],"r");
	while(!feof(fptr)) {
		current = fgetc(fptr);
		switch(current) {
			case '+':
				*(memory + memory_pos) = *(memory + memory_pos) + 1;
				break;
			case ',':
				*(memory + memory_pos) = getchar();
				break;
			case '-':
				*(memory + memory_pos) = *(memory + memory_pos) - 1;
				break;
			case '.':
				putchar(*(memory + memory_pos));
				break;
			case '<':
				if (memory_pos == 0) {
					memory_pos = 29999;
				} else {
					memory_pos--;
				}
				break;
			case '>':
				if(memory_pos == 29999) {
					memory_pos = 0;
				} else {
					memory_pos++;
				}
				break;
			case '[':
				if(*(memory + memory_pos) != 0) {
					/*Access a hidden pointer in the FILE struct to quickly jump to a position in the file*/
					*(array_starts + array_depth) = fptr->_IO_read_ptr;
					array_depth++;
				} else {
					while(current = fgetc(fptr)) {
						if (current == ']' || feof(fptr)) {
							break;
						}
					}
				}
				break;
			case ']':
				if(array_depth > 0) {
					if(*(memory + memory_pos) != 0) {
						/*This is very illegal*/
						fptr->_IO_read_ptr = *(array_starts + array_depth - 1);
					}
					else {
						array_depth--;
					}
				}
				break;
			default:
				break;
		}
	}
	fclose(fptr);
}