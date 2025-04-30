#include "mylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <semaphore.h>
#include <fcntl.h>    // For O_CREAT, O_EXCL

typedef void (*fnc)();
int main(int argc, char** argv)
{
    sem_t *vsem = sem_open("/victim_semaphore", O_CREAT, 0666, 0); // Initial value = 0
    if (vsem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    sem_t *asem = sem_open("/attacker_semaphore", O_CREAT, 0666, 0); // Initial value = 0
    if (asem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    
    for (size_t j = 0; j < 1000; j++) {
        for (size_t i = 0; i < 100; i++) {
          int cached = i % 2 == 0;
          fnc target = (fnc) (cached * (size_t) victim + (1 - cached) * (size_t) dummy);
        
        sem_wait(asem);
    
        target();
        target();
        target();
          
        sem_post(vsem);
        }
      }

    sem_close(asem);
    sem_close(vsem);
    sem_unlink("/victim_semaphore");
}
