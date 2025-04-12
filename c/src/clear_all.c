#include "shared_memory.h"

int main()
{

    // Delete semaphore
    sem_unlink("/sem_shm");

    // Delete shared memory
    shm_unlink("/shm_buf");

    return 0;
}