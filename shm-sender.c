#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>



//Shared memory!

#define SHM_KEY 8999

int main(){
    key_t key = SHM_KEY;
    int shmid = shmget(key, 2 * sizeof(int), IPC_CREAT | IPC_EXCL | 0660);

    if (shmid == -1){
        perror("shmget() failed");
        return EXIT_FAILURE;
    }

    printf("shmid = %i\n", shmid);

    int* data = shmat(shmid, NULL, 0);

    if(data == (void*)-1){
        perror("shmat() failed");
        return EXIT_FAILURE;
    }

    char msg[100];
    printf("What number should I send? ");
    fgets(msg, 100, stdin);

    int output = atoi(msg);

    printf("Sending %i...\n",output);

    *(data) = output;
    *(data+1) = 1; //Set to 1 to indicate that it is finished

    //Halt until data read
    while(*(data+1) == 1){/*No Op*/ }

    printf("Data read!\n");

    //detach now
    int rc = shmdt(data);
    if(rc == -1){
        perror("shmdt() failed");
        return EXIT_FAILURE;
    }    

    return EXIT_SUCCESS;
}