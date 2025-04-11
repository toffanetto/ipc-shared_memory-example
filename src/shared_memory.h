
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/eventfd.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAYLOAD_SIZE 64

typedef struct shm_buf_ {
    uint32_t size;
    char string[PAYLOAD_SIZE];
} shm_buf_t;