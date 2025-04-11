#include "shared_memory.h"

shm_buf_t *shm_buf = NULL;
int shm_fd = -1;
size_t buf_size = sizeof(shm_buf_t);

int main()
{

    sem_t *sem_shm = sem_open("/sem_shm", O_CREAT, 0644, 1);


    // Create shared memory resource
    shm_fd = shm_open("/shm_buf", O_RDWR | O_CREAT, 0644);

    // Allocate shared memory size
    ftruncate(shm_fd, buf_size);

    // Map the shared memory address in local process addressing
    shm_buf = mmap(0, buf_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    // Now we can access the shared memory segment directly from shm_buf

    if(sem_wait(sem_shm) == 0){

        strcpy(shm_buf->string, "Hello World from SHM!");
        shm_buf->size = strlen(shm_buf->string);

        sem_post(sem_shm);
    }



    sem_close(sem_shm);
    sem_unlink("/sem_shm");

    return 0;

}