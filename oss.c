#include <stdio.h>
#include "ClockSemaphore.h"
int main() {

    int live_processes = 0;
    const int MAX_PROCESSES = 18;

    Semaphore clock_semaphore = semaphore(&clock_semaphore);

    printf("Hello, World!\n");
    return 0;
}