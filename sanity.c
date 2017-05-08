#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

// Performance stuct of a process
struct perf {
	int ctime;
	int ttime;
	int stime;
	int retime;
	int rutime;
}performance;

void fib(int n) {
	if (n <= 1)
		return;
	fib(n-1);
	fib(n-2);
}

void
sanity(void)
{   
  int waitingtime = 0, runningtime = 0, turnaroundtime = 0, sleeptime = 0,numOfChilds = 50;
  int donePID;
  int i = 0,pid[numOfChilds],start = 0, finished = 0,k = 0,usecpu=0;
  int avgWT = 0, avgRT = 0, avgTAT = 0, avgST = 0;
  struct perf performance;
  
  for (i = 0; i < numOfChilds ;i = i + 1) {
	pid[i] = fork(); 
	if(pid[i] < 0) {
		printf(1,"failed to fork");      
	}

	if(pid[i] == 0) { 
		for(k=0; k < 5; k++) {
			start = uptime();
			finished = uptime();
			while((finished - start) < 5) {
				usecpu = usecpu - 1; 
				usecpu = usecpu + 1;
				usecpu = usecpu * 1;
				usecpu = usecpu / 1;
				usecpu = usecpu % 1;
				finished = uptime();
			}				 
			sleep(15);
		}
		exit(0);
	}  
  }     
  
  for (i = 0; i < numOfChilds; i++) {       
	  donePID =  wait_stat(0,&performance);
	  waitingtime = performance.retime;
	  runningtime = performance.rutime;
	  turnaroundtime = performance.ttime - performance.ctime;
	  sleeptime = performance.stime;			  
	  avgWT =    avgWT + waitingtime;
	  avgRT =    avgRT + runningtime;
	  avgTAT = avgTAT + turnaroundtime;
	  avgST = avgST + sleeptime;
		  
	  printf(1,"Child with pid %d has ended. The results are:\n",donePID);
	  printf(1,"Waiting time: %d.\n",waitingtime); 
	  printf(1,"Running time: %d.\n",runningtime);           
	  printf(1,"Turnaround time: %d.\n",turnaroundtime); 	
	  printf(1,"Sleep time: %d.\n\n", sleeptime);

	  if(i == numOfChilds - 1) {
		avgWT = avgWT / numOfChilds;
		avgRT = avgRT / numOfChilds;
		avgTAT = avgTAT / numOfChilds;
		avgST = avgST / numOfChilds;
					
		printf(1,"\nAverages:\nWaiting Time: %d.\nRunning Time: %d.\nTurnaround Time: %d.\nSleep Time: %d.\n", avgWT, avgRT, avgTAT, avgST); 			
	  }
  }
}

int
main(int argc, char *argv[])
{
  if(argc == 1){
    sanity();
  }
  
  exit(0);
}
