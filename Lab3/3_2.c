#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/types.h>
#include <sys/stat.h>

pthread_mutex_t mutex;          //定义一个全局互斥量，在不同函数中  
sem_t empty,full;   
char buffer[10];            //定义一个全局变量，表示当前缓冲区

void *producer( void *arg );    //输入线程  
void *consumer( void *arg );    //输出线程  

int main(int argc , char *argv[]){  
    pthread_t thrd_prod , thrd_cons;  
    pthread_mutex_init( &mutex , NULL );    //初始化互斥量  
    empty=*sem_open("E",O_CREAT,0666,10);
    full=*sem_open("F",O_CREAT,0666,0);
    //创建输入和输出线程  
    if( pthread_create( &thrd_prod , NULL, producer ,  
                NULL ) != 0 )  
        printf( "thread create failed." ); 

    if( pthread_create( &thrd_cons , NULL, consumer ,  
                NULL ) != 0 )  
        printf( "thread create failed." );  

    //等待线程结束  
    if( pthread_join( thrd_prod , NULL ) != 0 )  
        printf( " wait thread failed.");  
    if( pthread_join( thrd_cons , NULL ) != 0 )  
        printf( " wait thread failed.");  

    pthread_mutex_destroy( &mutex );        //关闭互斥量  
    sem_close(&empty);
    sem_close(&full);
    sem_unlink("E");
    sem_unlink("F");
    return 0;  
}  

void *producer( void *arg){  
    	for(int i=0;;i++)
	{
		sem_wait(&empty);
		scanf("%c",&buffer[i%10]);
		sem_post(&full);
		
	}	
}  
void *consumer( void *arg ){  
    
	
	for(int i=0;;i++)
	{
		sem_wait(&full);
		printf("输出：%c\n",buffer[i%10]);
		sem_post(&empty);
		sleep(1);
		
	}	
}

