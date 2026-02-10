#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define MAX 15

int pid[15];
int arrival[15];
int burst[15];
int priority[15];
int total_processes=0;

void loadData(){
    FILE*f;
    f=fopen("processinfo.csv","r");
    if(f==NULL){
        printf("File not found. Creating a sample 'processinfo.csv' for you...\n");
        f=fopen("processinfo.csv","w");
        fprintf(f,"1,0,5,2\n");
        fprintf(f,"2,1,3,1\n");
        fprintf(f,"3,2,8,3\n");
        fprintf(f,"4,3,6,4\n");
        fclose(f);
        f=fopen("processinfo.csv","r");
    }
    int i=0;
    while(i<MAX){
        int p_id,arr,bur,prio;
        if(fscanf(f,"%d,%d,%d,%d",&p_id,&arr,&bur,&prio)==EOF){
            break;
        }
        pid[i]=p_id;
        arrival[i]=arr;
        burst[i]=bur;
        priority[i]=prio;
        i++;
    }
    total_processes=i;
    fclose(f);
    printf("Data loaded successfully. Found %d processes.\n\n",total_processes);
}

void printTableHeader(){
    printf("PID\tArr\tBurst\tComp\tTAT\tWait\n");
    printf("------------------------------------------------\n");
}

void runFCFS(){
    printf("RUNNING FCFS\n");
    int i,j;
    for(i=0;i<total_processes;i++){
        for(j=0;j<total_processes-1;j++){
            if(arrival[j]>arrival[j+1]){
                int temp;
                temp=pid[j];pid[j]=pid[j+1];pid[j+1]=temp;
                temp=arrival[j];arrival[j]=arrival[j+1];arrival[j+1]=temp;
                temp=burst[j];burst[j]=burst[j+1];burst[j+1]=temp;
                temp=priority[j];priority[j]=priority[j+1];priority[j+1]=temp;
            }
        }
    }
    int current_time=0;
    float total_wait=0;
    float total_tat=0;
    printTableHeader();
    for(i=0;i<total_processes;i++){
        if(current_time<arrival[i]){
            current_time=arrival[i];
        }
        current_time=current_time+burst[i];
        int completion=current_time;
        int turnaround=completion-arrival[i];
        int waiting=turnaround-burst[i];
        total_wait=total_wait+waiting;
        total_tat=total_tat+turnaround;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",pid[i],arrival[i],burst[i],completion,turnaround,waiting);
    }
    printf("\nAverage Waiting Time: %.2f\n",total_wait/total_processes);
    printf("Average Turnaround Time: %.2f\n",total_tat/total_processes);
    printf("Throughput: %.2f\n",(float)total_processes/current_time);
    printf("=============================\n\n");
}

void runSJF(){
    printf("======== RUNNING SJF (Non-Preemptive) ========\n");
    int completed[MAX]={0};
    int current_time=0;
    int count_done=0;
    float total_wait=0;
    float total_tat=0;
    printTableHeader();
    while(count_done<total_processes){
        int shortest_index=-1;
        int min_burst=99999;
        int i;
        for(i=0;i<total_processes;i++){
            if(arrival[i]<=current_time&&completed[i]==0){
                if(burst[i]<min_burst){
                    min_burst=burst[i];
                    shortest_index=i;
                }
            }
        }
        if(shortest_index!=-1){
            current_time=current_time+burst[shortest_index];
            completed[shortest_index]=1;
            count_done++;
            int completion=current_time;
            int turnaround=completion-arrival[shortest_index];
            int waiting=turnaround-burst[shortest_index];
            total_wait=total_wait+waiting;
            total_tat=total_tat+turnaround;
            printf("P%d\t%d\t%d\t%d\t%d\t%d\n",pid[shortest_index],arrival[shortest_index],burst[shortest_index],completion,turnaround,waiting);
        }else{
            current_time++;
        }
    }
    printf("\nAverage Waiting Time: %.2f\n",total_wait/total_processes);
    printf("Average Turnaround Time: %.2f\n",total_tat/total_processes);
    printf("Throughput: %.2f\n",(float)total_processes/current_time);
    printf("=============================================\n\n");
}

void runPriority(){
    printf("======== RUNNING PRIORITY (Non-Preemptive) ========\n");
    int completed[MAX]={0};
    int current_time=0;
    int count_done=0;
    float total_wait=0;
    float total_tat=0;
    printTableHeader();
    while(count_done<total_processes){
        int best_index=-1;
        int highest_priority=99999;
        int i;
        for(i=0;i<total_processes;i++){
            if(arrival[i]<=current_time&&completed[i]==0){
                if(priority[i]<highest_priority){
                    highest_priority=priority[i];
                    best_index=i;
                }
            }
        }
        if(best_index!=-1){
            current_time=current_time+burst[best_index];
            completed[best_index]=1;
            count_done++;
            int completion=current_time;
            int turnaround=completion-arrival[best_index];
            int waiting=turnaround-burst[best_index];
            total_wait=total_wait+waiting;
            total_tat=total_tat+turnaround;
            printf("P%d\t%d\t%d\t%d\t%d\t%d\n",pid[best_index],arrival[best_index],burst[best_index],completion,turnaround,waiting);
        }else{
            current_time++;
        }
    }
    printf("\nAverage Waiting Time: %.2f\n",total_wait/total_processes);
    printf("Average Turnaround Time: %.2f\n",total_tat/total_processes);
    printf("Throughput: %.2f\n",(float)total_processes/current_time);
    printf("====================================================\n\n");
}

int main(){
    loadData();
    runFCFS();
    runSJF();
    runPriority();
    return 0;
}
