#include <stdio.h>
#include <stdlib.h>

void recursive_function(int depth) {
    char arr[1024]; // Виділяємо 1 KB пам'яті в стеку
    printf("Глубина рекурсії: %d, адреса стеку: %p\n", depth, (void*)&arr);
    recursive_function(depth + 1);
}

int main() {
    printf("Початок рекурсії...\n");
    recursive_function(1);
    return 0;
}

//gcc -Wall 6.c -o 6
