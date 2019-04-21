#include<stdio.h>
int main()
{
	//rough use variables
	int i=0,j=0,n,n2,swap,totalBurstTime=0,burstTimeDone=0,totalTimeOfCompletion=0;
	char swap2;
	//standard variables
	int turnAroundTime2=0,averageTurnAroundTime=0,waitingTime2=0,averageWaitingTime=0;
	printf("\n\n\n\tPlease enter number of process.....!\n\t");
	scanf("%d",&n);
	int highPriority=n;
	n2=n;
	char processName[n];
	int arrivalTime[n],burstTime[n],priority[n],turnAroundTime[n],completionTime[n],waitingTime[n],status[n],remainingBurstTime[n];
	//taking inputs for process name, arrival time, burst time and priority
	char c='A';
	i=0;
	while(i<n)
	{
		printf("\n\tPlease enter Process name, Arrival time, Burst time and Priority for process %d\t",i+1);
		processName[i]=c;
		scanf("%i",&arrivalTime[i]);
		scanf("%i",&burstTime[i]);
		scanf("%i",&priority[i]);
		i++;
		c++;
	}
	i=0;
	while(i<n)
	{
		turnAroundTime[i]=0;
		completionTime[i]=0;
		waitingTime[i]=0;
		status[i]=0;
		totalBurstTime=totalBurstTime+burstTime[i];
		remainingBurstTime[i]=burstTime[i];
		i++;
	}
	
	//sorting on the basic of arrival time
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(arrivalTime[i]>arrivalTime[j])
			{	
				//arrival time swapping
				arrivalTime[i]=arrivalTime[i]+arrivalTime[j];
				arrivalTime[j]=arrivalTime[i]-arrivalTime[j];
				arrivalTime[i]=arrivalTime[i]-arrivalTime[j];
				
				//burst time swapping
				swap=burstTime[i];
				burstTime[i]=burstTime[j];
				burstTime[j]=swap;			
					
				//priority swapping
				swap=priority[i];
				priority[i]=priority[j];
				priority[j]=swap;				
				
				//process name swapping
				swap2=processName[i];
				processName[i]=processName[j];
				processName[j]=swap2;
				
				//remaining burst time swapping
				swap=remainingBurstTime[i];
				remainingBurstTime[i]=remainingBurstTime[j];
				remainingBurstTime[j]=swap;
			}
		}
		
	}
	//process execution starts 
	printf("\n\t Process Name \t Priority \t Arrival Time \t Burst Time \t Remaining Burst Time ");
	for(;burstTimeDone<totalBurstTime;)
	{
		
		
		//getting lowest priority process out of all processes
		highPriority=n-1;
		for(i=0;i<n;i++)
		{
			if(priority[i]<priority[highPriority] && status[i]!=1 && arrivalTime[i]<totalTimeOfCompletion)
			{
				highPriority=i;
			}
		}
		//deduceion of 2 unit of time as process is completing one phase
		totalTimeOfCompletion=arrivalTime[highPriority]-2;
		if(remainingBurstTime[highPriority]>=2&&remainingBurstTime[highPriority]==burstTime[highPriority])
		{
			burstTimeDone=burstTimeDone+2;
			remainingBurstTime[highPriority]=remainingBurstTime[highPriority]-2;
			totalTimeOfCompletion=totalTimeOfCompletion+2+2;
			printf("\n\t %c \t\t %d \t\t %d \t\t %d \t\t %d ",processName[highPriority],priority[highPriority],arrivalTime[highPriority],burstTime[highPriority],remainingBurstTime[highPriority]);
		}
		else if(remainingBurstTime[highPriority]>=2)
		{
			burstTimeDone=burstTimeDone+2;
			remainingBurstTime[highPriority]=remainingBurstTime[highPriority]-2;
			totalTimeOfCompletion=totalTimeOfCompletion+2;
			printf("\n\t %c \t\t %d \t\t %d \t\t %d \t\t %d ",processName[highPriority],priority[highPriority],arrivalTime[highPriority],burstTime[highPriority],remainingBurstTime[highPriority]);	
		}
		//deduceion of 1 unit of time
		else if(remainingBurstTime[highPriority]==1)
		{
			burstTimeDone=burstTimeDone+1;
			remainingBurstTime[highPriority]=remainingBurstTime[highPriority]-1;
			totalTimeOfCompletion=totalTimeOfCompletion+1;
			printf("\n\t %c \t\t %d \t\t %d \t\t %d \t\t %d ",processName[highPriority],priority[highPriority],arrivalTime[highPriority],burstTime[highPriority],remainingBurstTime[highPriority]);
		}
		//closing a process
		if(remainingBurstTime[highPriority]==0)
		{
			status[highPriority]=1;
			waitingTime[highPriority]=totalTimeOfCompletion-arrivalTime[highPriority]-burstTime[highPriority];
			completionTime[highPriority]=totalTimeOfCompletion;
			turnAroundTime[highPriority]=totalTimeOfCompletion-arrivalTime[highPriority];
			//deleting the process
			for(i=highPriority;i<n;i++)
			{
				processName[i]=processName[i+1];
				arrivalTime[i]=arrivalTime[i+1];
				burstTime[i]=burstTime[i+1];
				priority[i]=priority[i+1];
				turnAroundTime[i]=turnAroundTime[i+1];
				completionTime[i]=completionTime[i+1];
				waitingTime[i]=waitingTime[i+1];
				status[i]=status[i+1];
				remainingBurstTime[i]=remainingBurstTime[i+1];
				n=n-1;
			}
		}
		waitingTime2=waitingTime2+waitingTime[highPriority];
		turnAroundTime2=turnAroundTime2+turnAroundTime[highPriority];		
	}
	
	averageWaitingTime=waitingTime2/n2;
	averageTurnAroundTime=turnAroundTime2/n2;
	printf("\n\n\t Average Waiting Time is : %d",averageWaitingTime);
	printf("\n\n\t Average Turn Around Time is : %d",averageTurnAroundTime);
	return 0;
}
