#include "shared_memory.h"

int main()
{
    // Shared memory variables
    shm_buf_t *shm_buf = NULL;
    int shm_fd = -1;
    size_t buf_size = sizeof(shm_buf_t);

    // Semaphore variable
    sem_t *sem_shm;

    // Creating semaphore
    sem_shm = sem_open("/sem_shm", O_CREAT, 0644, 1);

    // Create shared memory resource
    shm_fd = shm_open("/shm_buf", O_RDWR | O_CREAT, 0644);

    // Allocate shared memory size
    ftruncate(shm_fd, buf_size);

    // Map the shared memory address in local process addressing
    shm_buf = mmap(0, buf_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    shm_buf->size = 0;

    // Now we can access the shared memory segment directly from shm_buf
    // Trying to get the semaphore and waiting until it occurs
    while (1)
    {
        if (sem_trywait(sem_shm) == 0)
        {
            // Semaphore picked!
            strcpy(shm_buf->string, "Updating size each interation...");
            shm_buf->size = shm_buf->size + 1;

            // Realaesing the semaphore
            sem_post(sem_shm);
        }
    }

    // Cleaning semaphore stuff
    sem_close(sem_shm);
    // sem_unlink("/sem_shm");

    // Cleaning shared memory stuff (deletes the shared section)
    // shm_unlink("/shm_buf");

    return 0;
}