#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 10 //Define size of the array we will be testing

//Function prototypes for thread use (assignment specification)
void print_array(int arr[], int start, int end);
void *sorter(void *params);
void *merger(void *params);

//Declaring global arrays for thread use (assignment specification)
int array[SIZE] = {44, 232, 12, 7, 523, 78, 187, 474, 34, 72};
//int array[SIZE] = {12, 3, 56, 59, 109, 543, 333, 66, 23, 93};
//int array[SIZE] = {45, 667, 345, 123, 44, 19, 56, 6, 221, 60};

int sorted_array[SIZE]; //Array to store the results of sorted sublists

//Struct for thread utilization to specify arg (from PDF)
typedef struct {
	int from_index;
	int to_index;
} parameters;

int main() {

	//Display the array of integers
	printf("\nArray of integers that will be used for merge sort: \n");
	print_array(array, 0, SIZE);

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

//The following function will print the contents of an array
void print_array(int arr[], int start, int end) {

	for (int x = start; x < end; x++) {
		printf("%d ", arr[x]);
	}

}

//The following function will sort a sublist using its starting and ending indices
void *sorter(void *params) {

	parameters *t_params = (parameters *)params;
	
	//The thread must know start and end index of sublist to sort it
	int start = t_params -> from_index;
	int finish = t_params -> to_index + 1;	

	//Print the sublist that the thread will sort
	printf("Thread will sort the following sublist: \n");
	print_array(array, start, finish);

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
	print_array(array, start, finish);

	printf("\n\n");	
	
	pthread_exit(0);

}

//The following function 
void *merger(void *params) {

	parameters *t_params = (parameters *)params;

	//Thread must know start and end index of merged list to sort it
	int start = t_params -> from_index;
	int finish = t_params -> to_index + 1;
	
	printf("Current state of unsorted array: \n");
	print_array(array, 0, SIZE);
	printf("\n\n");

	int temp[SIZE];
	int mid = 0;

	for (int x = 0; x < SIZE - 1; x++) {

		if (array[x] > array[x + 1] ) {
			mid = x + 1;
			break;
		}
	}

	/*
	 Need to walk through each sublist within the unsorted array 
	 and determine the next integer to be allocated within a 
	 temporary array. The elements of the temporary array are 
	 then copied to a sorted, global array variable. 
	 */

	int a = 0, b = mid, c = 0;	
	while (a < mid && b < finish) {

		if (array[a] < array[b]) 
			temp[c++] = array[a++];
		
		else 
			temp[c++] = array[b++]; 
	}
	
	//Remaining array elements are added to the temporary array
	while (a < mid) 
		temp[c++] = array[a++];

	while (b < finish)
		temp[c++] = array[b++];

	//Copy elements to sorted_array
	for (int x = start; x < finish; x++) {
		sorted_array[x] = temp[x]; 
	}

	//Display the final merged, sorted array
	printf("Final merged and sorted array: \n");
	print_array(sorted_array, 0, SIZE);

	printf("\n\n");
	
	pthread_exit(0);
	 
}
