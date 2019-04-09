#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<fcntl.h>
#include<sys/types.h>
#include <sys/stat.h>
pthread_mutex_t mutex;          //定义一个全局互斥量，在不同函数中  
int buffer_count=1000;             //定义一个全局变量，表示当前票数  

void *producer( void *arg );    //退票线程  
void *consumer( void *arg );    //售票线程  

int main(int argc , char *argv[]){  
    pthread_t thrd_prod , thrd_cons;  

    pthread_mutex_init( &mutex , NULL );    //初始化互斥量  

    //创建退票和售票线程  
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
    return 0;  
}  

void *producer( void *arg){  
    while(1){  
        pthread_mutex_lock( &mutex );   //加锁  
        //成功占有互斥量  
        printf( "退票完成！"); 
        buffer_count++;
        printf("当前票数： %d\n",buffer_count) ;  
        pthread_mutex_unlock( &mutex ); //解锁
    }  
}  
void *consumer( void *arg ){  
    while(1)
        {
        pthread_mutex_lock( &mutex );   //加锁  
        //成功占有互斥量
        printf( "售票完成！");  
        buffer_count--;
        printf("当前票数： %d\n",buffer_count) ;
        pthread_mutex_unlock( &mutex ); //解锁  
    }
}

