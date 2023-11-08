// Brandon Jennings
// Producer Consumer Problem
// Operating Systems
// Producer File

#include "pro_con.h"

void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 10;					// Produce an item
        sem_wait(empty);					// Wait for an empty slot
        SharedMem->buffer[SharedMem->in] = item;		// Put item in the buffer
        printf("%d items put on the table.\n", item);		// Printing item produced
        SharedMem->in = (SharedMem->in + 1) % BUFFER_SIZE;	// Increment the in pointer
        sem_post(full);						// Signal the buffer is full
        sleep(2); 						// Holds for 2 seconds
    }
}

int main(){
    int fd;
    char *addr;
    pthread_t pro_thread; 					// Declaring pthread_t variable
    
    empty = sem_open("/empty",O_CREAT,0666,BUFFER_SIZE);	// Initializes empty semaphore with value of 2
    full = sem_open("/full",O_CREAT,0666,BUFFER_SIZE);		// Initializes full semaphore with value of 0
 
    // Creates/accesses a shared memory object named /memObj
    fd = shm_open("/memObj", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR); 
    
    // Exits on failure of memory object creation
    if (fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    
    // Sets size of shared memory object to size of an int
    if (ftruncate(fd, sizeof(SharedMem)) == -1) {
    	perror("ftruncate");
    	exit(EXIT_FAILURE);
    }
    
    // Maps the object into the address space and reinitializes SharedMem
    addr = mmap(NULL, sizeof(SharedMem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    SharedMem = (SharedMemory *) addr;
    
    pthread_create(&pro_thread, NULL, producer, NULL);		// Creates producer thread, assigned to pro_thread variable
        
    pthread_join(pro_thread, NULL);				// Waits for producer thread to finish executing

    sem_unlink("/empty");					// Unlinks empty semaphore
    sem_unlink("/full");					// Unlinks full semaphore

    return 0;
}

