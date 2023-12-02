// Varad Charholikar
// PA01
// 1032220170

#include<stdio.h>

struct rr_scheduling {

	int bt;
	int at;
	int wt;
	int tat;
	int rem_bt;

};



void insertionSort(struct rr_scheduling arr[10], int size) {
  for (int i= 1; i< size; i++) {
  struct rr_scheduling temp = arr[i];
    int key = arr[i].at;

    int j = i - 1;

    while (key < arr[j].at && j >= 0) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = temp;
  }
}

int main(){

	
	float avg_wt, avg_tat;
	int n, total_wt, total_tat,tq;
	int t=0;
	struct rr_scheduling arr[10];
	
	printf("Enter the time quantum: \n");
	scanf("%d",&tq);
	
	printf("Enter the total number of processes: \n");
	scanf("%d",&n);
	
	
	for(int i=0; i<n; i++){
	printf("Enter arival time for %d process:\n",i+1);
		scanf("%d",&arr[i].at);
	
		printf("Enter burst time for %d process:\n",i+1);
		int bt;
		scanf("%d",&bt);
		arr[i].bt = bt;
		arr[i].rem_bt = bt;
	
	}
	
	insertionSort(arr,n);
	
	while(1){
	int flag = 1;
	for(int i=0; i<n; i++){
		if(arr[i].rem_bt > 0){
			flag = 0;
			if(arr[i].rem_bt  > tq){
				t = t+tq;
				arr[i].rem_bt  -= tq;
			}
		}
		else{
			t = t + arr[i].rem_bt ;
			arr[i].rem_bt  = 0;
			printf("%d",t);
			arr[i].wt = t - arr[i].bt;
			arr[i].tat = t - arr[i].at;
		}
	}
	
	if(flag == 1){
		break;
	}
	}
	
	
	for(int i=0; i<n; i++){
		total_wt += arr[i].wt;
		total_tat += arr[i].tat;
	}
	
	avg_wt = total_wt/n;
	avg_tat = total_tat/n;
	
	
	
	printf("Process Number \t Arival Time \t Burst Time \t Wating Time \t Turnaround Time \n");
	
	for(int i=0; i<n; i++){
		printf("\t %d \t \t %d \t \t %d \t \t %d \t \t %d \n", i+1,arr[i].at,arr[i].bt,arr[i].wt,arr[i].tat);
	}
	
		printf("\n\nThe Average Waiting Time is %f", avg_wt);
		printf("\n\nThe Average Turnaround Time is %f\n\n", avg_tat);
	
	return 0;
		
}

//Output:
//Process number          Arrival Time            Burst Time              Waiting Time            Turnaround Time

//        1                       0                       4                       2                       6

//        2                       2                       3                       2                       5

//        3                       5                       4                       2                       6

//The Average Waiting Time is 2.000000

//The Average Turnaround Time is 5.666666