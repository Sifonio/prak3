#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <signal.h>
#define CPU_TIME_LIMIT 1000 // Обмеження часу процесора (в секундах)

void handle_signal(int sig) {
    if (sig == SIGXCPU) {
        fprintf(stderr, "час використання CPU вичерпано\n");
        exit(EXIT_FAILURE);
    }
}

void set_cpu_limit(int seconds) {
    struct rlimit rl;
    if (getrlimit(RLIMIT_CPU, &rl) != 0) {
        perror("getrlimit failed");
        exit(EXIT_FAILURE);
    }
    
    rl.rlim_cur = seconds; // Обмежуємо поточний ліміт
    if (setrlimit(RLIMIT_CPU, &rl) != 0) {
        perror("setrlimit failed");
        exit(EXIT_FAILURE);
    }
}


void lotery(int *arr, int count, int max){
    int used[max+1];
    for (int i = 0; i <= max; i++){
        used[i] = 0;
    }
    int generated = 0;
    while (generated < count){
        int num = rand() % max +1;
        if(!used[num]){
            arr[generated+1] = num;
            used[num] = 1;
        } 
    }
}

void print_numbers(int *array, int count) {
    for (int i = 0; i < count; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main() {
    signal(SIGXCPU, handle_signal);
    set_cpu_limit(CPU_TIME_LIMIT);
    srand(time(NULL));

    int lot_49[7];
    int lot_36[6];

    lotery(lot_49, 7, 49);
    lotery(lot_36, 6, 36);

    printf("Лотерея 7/49: ");
    print_numbers(lot_49, 7);
    
    printf("Лотерея 6/36: ");
    print_numbers(lot_36, 6);
    return 0;
}
//gcc -Wall 4.c -o 4