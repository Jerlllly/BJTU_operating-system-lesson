#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
    key_t  key;
    int shm_id;
    int sem_id;
    int value = 0;

    key = ftok(".", 0xFF);


    shm_id = shmget(key, 1024, IPC_CREAT|0644);
    if(-1 == shm_id)
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    char *shm_ptr;
    shm_ptr = shmat(shm_id, NULL, 0);
    if(NULL == shm_ptr)
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    while(1)
    {

        {
            printf("\nNow, snd message process running:\n");
            printf("\tInput the snd message:  ");
            scanf("%s", shm_ptr);


        }

        if(0 == (strcmp(shm_ptr ,"end")))
        {
            printf("\nExit sender process now!\n");
            break;
        }
    }
    shmdt(shm_ptr);
    return 0;
}
