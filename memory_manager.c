#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>

#define PAGE_SIZE 256
#define PAGE_ENTRIES 256
#define PAGE_OFFSET 8

#define FRAME_SIZE 256
#define BUFFER_SIZE 256

#define MASK 255

#define PHYSICAL_MEM_SIZE PAGE_SIZE * PAGE_ENTRIES

int table[PAGE_ENTRIES];

signed char memoryBlock[PHYSICAL_MEM_SIZE];
signed char *backingStore;

int main (int argc, char* argv[]) {

	//Need to check if user has ran the program using (./a.out addresses.txt)
	if (argc < 2) {
		printf("Specified less arguments than required, exiting...\n");
		return 0;
	}

	FILE *input = fopen(argv[1], "r"); //Need to open addresses.txt for reading
	FILE *output = fopen("out.txt", "w");

	int backing = open("BACKING_STORE.bin", O_RDONLY);
	backingStore = mmap(0, PHYSICAL_MEM_SIZE, PROT_READ, MAP_PRIVATE, backing, 0);

	char buffer[BUFFER_SIZE];
	unsigned char freePage = 0;

	while (fgets(buffer, BUFFER_SIZE, input) != NULL) {
 
		int logical_address = atoi(buffer);
		int offset = logical_address & MASK;
		
		int logicalNum = MASK & (logical_address >> PAGE_OFFSET);
		int physicalNum = table[logicalNum];

		//Page fault procedure
		if (physicalNum == -1) {
			physicalNum = freePage;
			freePage++;

			memcpy(memoryBlock + physicalNum * PAGE_SIZE, backingStore + logicalNum * PAGE_SIZE, PAGE_SIZE); 
			table[logicalNum] = physicalNum;
		}

		int physical_address = (physicalNum << PAGE_OFFSET) | offset;
		signed char value = memoryBlock[physicalNum * PAGE_SIZE + offset];		

		fprintf(output, "Virtual Address: %d \t Physical Address: %d \t Value: %d\n", logical_address, physical_address, value);

	}

	return 0;

}
