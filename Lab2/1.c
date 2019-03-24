#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{

	pid_t pid;
	pid=fork();
	if (pid<0)
{
		perror("fork failed");
		exit(0);
}
	else if(pid==0)
{
		execl("/usr/bin/vi","vi",NULL);
}
	else
{
	for(int i=0;i<1000;i++)
{}}
	return 0;

}
