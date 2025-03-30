#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/resource.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024

void check_ulimit() {
    struct rlimit limit;
    if (getrlimit(RLIMIT_MEMLOCK, &limit) == 0) {
        printf("Current ulimit -l (locked memory): %lu KB\n", limit.rlim_cur / 1024);
    } else {
        perror("getrlimit");
    }
}

int main() {
    key_t key = ftok("shmfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    printf("Shared memory segment created with ID: %d\n", shmid);

    char *shmaddr = (char *)shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1) {
        perror("shmat");
        exit(1);
    }
    
    check_ulimit();
    
    strcpy(shmaddr, "аруцрпт");
    printf("Дані записані у пам'ять: %s\n", shmaddr);

    if (shmdt(shmaddr) == -1) {
        perror("shmdt");
        exit(1);
    }
    printf("Detached from shared memory.\n");
    return 0;
}
//gcc -Wall 7.c -o 7
