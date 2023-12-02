// Varad Charholikar
// PA01
// 1032220170

#include<stdio.h>

	struct fcfs_scheduling{
	
		int at, bt, wt, tat;
	
	};
	
	void insertionSort(struct fcfs_scheduling array[30], int n) {
  		for (int i = 1; i < n; i++) {
			 int key = array[i].at;
			 int j = i - 1;

			 while (key < array[j].at && j >= 0) {
				array[j + 1].at = array[j].at;
				--j;
			 }
			 array[j + 1].at = key;
	  }
	}

	int main(){
		int n, totalwt = 0, totaltat = 0;
		float avgwt, avgtat;

		struct fcfs_scheduling arr[30];
		// input n
		printf("Enter the total number of processes: ");
		scanf("%d", &n);
		// input at and bt
		for(int i = 0; i < n; i++){
			int temp;
			printf("Enter the Arrival Time of the process %d: ", i+1);
			scanf("%d", &temp);
			arr[i].at = temp;

			printf("Enter the Burst Time of the process %d: ", i+1);
			scanf("%d", &temp);
			arr[i].bt = temp;
		}

		//sorting
		insertionSort(arr, n);
		
		//Calculating waiting time
		arr[0].wt = 0;
		
		for(int i = 0; i < n; i++){
			arr[i].wt = 0;
			for(int j = 0; j < i; j++){
				arr[i].wt = arr[i].wt + arr[j].bt;
			}
			arr[i].wt = arr[i].wt - arr[i].at;
			if(arr[i].wt < 0){
				arr[i].wt = 0;
			}
		}
		
		// Calculating TAT
		for(int i = 0; i < n; i++){
			arr[i].tat = arr[i].bt + arr[i].wt;
		}
		
		//Average wt and tat
		for(int i = 0; i < n; i++){
			totalwt = totalwt + arr[i].wt;
			totaltat = totaltat + arr[i].tat;
		}
		
		avgwt = totalwt / n;
		
		avgtat = totaltat / n;
		
		printf("\n\nProcess number		Arrival Time		Burst Time		Waiting Time		Turnaround Time");
		
		for(int i = 0; i < n; i++){
			printf("\n\n	%d			%d			%d			%d			%d", i+1, arr[i].at, arr[i].bt, arr[i].wt, arr[i].tat);
		}
		
		
		printf("\n\nThe Average Waiting Time is %f", avgwt);
		printf("\n\nThe Average Turnaround Time is %f\n\n", avgtat);
		

}

//Output:
//Process number          Arrival Time            Burst Time              Waiting Time            Turnaround Time

//        1                       0                       3                       0                       3

//        2                       2                       5                       1                       6

//        3                       4                       2                       4                       6

//The Average Waiting Time is 1.000000

//The Average Turnaround Time is 5.000000