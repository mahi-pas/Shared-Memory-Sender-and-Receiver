#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//Shared memory!

#define SHM_KEY 8999

int main(){
    key_t key = SHM_KEY;
    int shmid = shmget(key, 2 * sizeof(int), 0660);
    if(shmid == -1){
        perror("shmid() failed");
        return EXIT_FAILURE;
    }

    printf("shmid = %i\n", shmid);

    int* data = shmat(shmid, NULL, 0);

    if(data == (void*)-1){
        perror("shmat() failed");
        return EXIT_FAILURE;
    }

    //Halt until message recieved
    while(*(data+1) == 0){/*No Op*/ }

    //read data
    printf("Data read: %i\n",*(data));
    *(data+1) = 0; //Indicate that is it read

    //detach now
    int rc = shmdt(data);
    if(rc == -1){
        perror("shmdt() failed");
        return EXIT_FAILURE;
    }  

    //Send signal to delete now that it is done reading

    if(shmctl(shmid, IPC_RMID, 0) == -1){
        perror("shmctl() failed");
        return EXIT_FAILURE;
    }

}