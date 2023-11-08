// Brandon Jennings
// Producer Consumer Problem
// Operating Systems
// Consumer file

#include "pro_con.h"

void *consumer(void *arg) {
    int item;
    while(1) {
        sem_wait(full);					// Wait for a full slot
        item = SharedMem->buffer[SharedMem->out];		// Get item from the buffer
        printf("Picked up %d\n", item);				// Printing the item consumed
        SharedMem->out = (SharedMem->out + 1) % BUFFER_SIZE;	// Increment the out pointer
        sem_post(empty);					// Signal the buffer is empty
        sleep(2);						// Holds for 2 seconds
    }
}

int main(){
    int fd;
    char *addr;
    pthread_t con_thread; 					// Declaring pthread_t variable
    
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
    
    // Maps the object into the address space
    addr = mmap(NULL, sizeof(SharedMem), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    SharedMem = (SharedMemory *) addr;
    
    pthread_create(&con_thread, NULL, consumer, NULL);	// Creates consumer thread, assigned to con_thread variable
        
    pthread_join(con_thread, NULL);			// Waits for consumer thread to finish executing

    sem_unlink("/empty");					// Unlinks empty semaphore
    sem_unlink("/full");					// Unlinks full semaphore

    return 0;
}
