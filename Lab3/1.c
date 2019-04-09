#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/types.h>
#include <sys/stat.h>

sem_t *S1,*S2,*S3;
int main()
{
	pid_t pid_1,pid_2,pid_3,pid_4; 
	S1=sem_open("1",O_CREAT,0666,0);
	S2=sem_open("2",O_CREAT,0666,0);
	S3=sem_open("3",O_CREAT,0666,0);
	pid_1=getpid();
	pid_2=fork();
	if(pid_2==0)//子进程2
	{
		sem_wait(S1);
		printf("I am the process P2\n");
		sem_post(S1);
		sem_post(S2);
	}
	if(pid_2>0)//主进程1
	{
	
		pid_3=fork();
		if(pid_3==0)//子进程3
		{
			sem_wait(S1);
			printf("I am the process P3\n");
			sem_post(S1);
			sem_post(S3);
		}
		if(pid_3>0)//主进程1
		{
			printf("I am the process P1\n");
			sem_post(S1);
			pid_4=fork();

			if(pid_4==0)//子进程4
			{
				sem_wait(S2);
				sem_wait(S3);
				printf("I am the process P4\n");
				sem_post(S2);
				sem_post(S3);
			}
		}

	}




	sem_close(S1);
	sem_close(S2);
	sem_close(S3);
	sem_unlink("1");
	sem_unlink("2");
	sem_unlink("3");
	return 0;


}
