#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	int P1pid=getpid();
	int P2pid,P3pid,P4pid,P5pid;
	pid_t P2,P3,P4,P5;
	P2=fork();
	if(P2==0)
	{
		P4=fork();
		if(P4==0)
		{
			while(1) printf("in P4,pid=%d,fatherpid=%d\n",getpid(),getppid());
		}
		else
		{
			P5=fork();
			if(P5==0)
			{
				while(1) printf("in P5,pid=%d,fatherpid=%d\n",getpid(),getppid());
			}
		}
		while(1) printf("in P2,pid=%d,fatherpid=%d\n",getpid(),getppid());
	}
	else
	{
		P3=fork();
		if(P3<0)printf("error in fork!");
		else if(P3==0)
		{
			while(1) printf("in P3,pid=%d,fatherpid=%d\n",getpid(),getppid());
		}
	}
	while(1) printf("\nin P1,pid=%d\n",P1pid);
	return 0;
}

