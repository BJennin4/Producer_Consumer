// Brandon Jennings
// Producer Consumer Problem
// Operating Systems
// Header File

#ifndef PRO_CON_H
#define PRO_CON_H

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 2 // Setting buffer size

typedef struct {
    int in;
    int out;
    int buffer[BUFFER_SIZE];
} SharedMemory;

SharedMemory *SharedMem;

sem_t *empty;
sem_t *full;

#endif //PRO_CON
