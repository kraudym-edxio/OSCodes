#include <stdio.h>

#define MAX 30		   //A defined maximum for array sizes 

void swap(int *x, int *y); //Function swaps the contents of two array indices 

int main() {

	int p_count; //Keep track of process count for loop conditions

	//Arrays needed to implement Priority Scheduling
	int priority_arr[MAX], burstTime_arr[MAX], p_num[MAX], waitTime_arr[MAX], completeTime_arr[MAX]; 

	//Start by prompting user to enter the process count
	printf("Enter the process count: ");
	scanf("%d", &p_count);

	//Loop and ask user to input burst time as well as priority number
	printf("Enter the burst time & priority for each process...!\n");
	for (int x = 0; x < p_count; x++) {

		printf("\nFor p[%d]: Burst time and priority, respectively: ", x + 1);
		scanf("%d %d", &burstTime_arr[x], &priority_arr[x]);
		p_num[x] = x + 1;
	} 

	//Selection sort algorithm in order to sort priorities, burst times, and process numbers
	for (int x = 0; x < p_count; x++) {
	
		int index = x;
		
		//Determine the index of the minimum element for swapping process 
		for (int y = x + 1; y < p_count; y++) {
			
			if (priority_arr[y] < priority_arr[index]) {
				index = y;
			} 
		}	

		//Begin swapping for each necessary array, swap minimum with first element
		swap(&priority_arr[x], &priority_arr[index]);
		swap(&burstTime_arr[x], &burstTime_arr[index]);
		swap(&p_num[x], &p_num[index]);
	}

	int totalTime = 0;	//Initialize total time
	waitTime_arr[0] = 0;	//Waiting time for the first process is zero

	//Determine the wait timees for each process, add to total
	for (int x = 1; x < p_count; x++ ) {
	
		waitTime_arr[x] = 0;
		
		for (int y = 0; y < x; y++) {
			waitTime_arr[x] += burstTime_arr[y];
		}

		totalTime += waitTime_arr[x];

	}

	//Calculate average wait time based on totalTime over process count
	int averageWaitTime = totalTime / p_count;
	totalTime = 0;

	printf("\nSummary Table Printout: \n");	
	printf("\nProcess \t Burst Time \t Waiting Time \t Completion Time");

	for (int x = 0; x < p_count; x++) {

		//Calculate turnaround/completion time for each process
		completeTime_arr[x] = burstTime_arr[x] + waitTime_arr[x]; 	
		totalTime += completeTime_arr[x];

		//Print statement for each row of the summary table 
		printf("\np[%d] \t\t\t%d \t\t%d \t\t%d", p_num[x], burstTime_arr[x], waitTime_arr[x], completeTime_arr[x]);

	}

	int averageCompletionTime = totalTime / p_count;

	//Display final averages
	printf("\n\nAverage Waiting Time: %d\nAverage Completion Time: %d\n", averageWaitTime, averageCompletionTime);

	return 0;

}

//Function swaps the contents of two array elements 
void swap(int *x, int *y) {

	int temp = *x;
	*x = *y;
	*y = temp;

}
