#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 10

//Function prototypes for thread use (assignment specification)
void *sorter(void *params);
void *merger(void *params);

//Declaring global arrays for thread use (assignment specification)
//int array[SIZE] = {44, 232, 12, 7, 523, 78, 187, 474, 34, 72};
//int array[SIZE] = {12, 3, 56, 59, 109, 543, 333, 66, 23, 93};
int array[SIZE] = {45, 667, 345, 123, 44, 19, 56, 68, 176, 221};

int sorted_array[SIZE];

//Struct for thread utilization to specify arg
typedef struct {
	int from_index;
	int to_index;
} parameters;

int main() {

	//Display the array of integers
	printf("\nArray of integers that will be used for merge sort: \n");
	for (int x = 0; x < SIZE; x++) {
		printf("%d ", array[x]);
	}

	printf("\n\n");

	//Specifying an array of three threads
	pthread_t t_array[3];
	
	parameters* args = (parameters*) malloc(sizeof(parameters));
		//For first sublist we need to use indices 0 through 4	
		args -> from_index = 0;
		args -> to_index = ((SIZE / 2) - 1);
		pthread_create(&t_array[0], 0, sorter, args);

	sleep(1);
	
	args = (parameters*) malloc(sizeof(parameters));
		//For second sublist we need to use indices 5 through 9
		args -> from_index = (SIZE / 2);
		args -> to_index = (SIZE - 1);
		pthread_create(&t_array[1], 0, sorter, args);

	//Must wait until threads finish sublist sorting
	pthread_join(t_array[0], NULL);
	pthread_join(t_array[1], NULL);

	sleep(1);

	args = (parameters*) malloc(sizeof(parameters));
		//For merge we must utilize all indices
		args -> from_index = 0;
		args -> to_index = (SIZE - 1);
		pthread_create(&t_array[2], 0, merger, args);

	//Waiting for the completion of the merging thread
	pthread_join(t_array[2], NULL);
	
	return 0;

}

void *sorter(void *params) {

	parameters *t_params = (parameters *)params;
	
	//The thread must know start and end index of sublist to sort it
	int start = t_params -> from_index;
	int finish = t_params -> to_index + 1;	

	//Print the sublist that the thread will sort
	printf("Thread will sort the following sublist: \n");
	for (int x = start; x < finish; x++) {
		printf("%d ", array[x]);
	}

	printf("\n");
	
	//Sort sublist using bubble sort
	for (int x = start; x < finish; x++) {

		for (int y = start; y < finish - 1; y++) {
				
			//If true, a swap will need to take place
			if (array[y] > array[y + 1]) {
				int temp = array[y];	
				array[y] = array[y + 1];
				array[y + 1] = temp;
			}			
		}	
	}
	
	//Copy the sorted sublist to the destination array
	printf("\nSorted sublist: \n");
	for (int x = start; x < finish; x++) {
		printf("%d ", array[x]);
		sorted_array[x] = array[x];
	}

	printf("\n\n");	
	
	pthread_exit(0);

}

void *merger(void *params) {

	parameters *t_params = (parameters *)params;

	//Thread must know start and end index of merged list to sort it
	int start = t_params -> from_index;
	int finish = t_params -> to_index + 1;

	//Sort merged list using bubble sort 
	for (int x = start; x < finish; x++) {

		for (int y = start; y < finish - 1; y++) {

			if (sorted_array[y] > sorted_array[y + 1]) {
				//If true, a swap will need to take place	
				int temp = sorted_array[y];
				sorted_array[y] = sorted_array[y + 1];
				sorted_array[y + 1] = temp;
			}
		}
	}
	
	//Display the final merged, sorted array
	printf("Final merged and sorted array: \n");
	for (int x = 0; x < SIZE; x++) {
		printf("%d ", sorted_array[x]);
	}

	printf("\n\n");
	
	pthread_exit(0);
	 
}
