// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>

__int32_t owner_process_set = 0;
__int32_t owner_process = 0;

typedef struct 
{
    char* name; // Name of the shared memory region
    int shm_fd; // Shared memory file descriptor object
    void* map_ptr;  // Pointer to the mapped region
    char* ptr;  // Pointer to content
    size_t size; // Size of the region
} sh_mem_t;

sh_mem_t* sh_mem_new()
{
    return (sh_mem_t*) malloc(sizeof(sh_mem_t));
}

void sh_mem_delete(sh_mem_t* shm)
{
    free(shm->name);
    free(shm);
}

void sh_mem_ctor(sh_mem_t* shm, const char* name, size_t size)
{
    shm->size = size;
    shm->name = (char*)malloc(strlen(name) + 1); // Manually allocate string
    shm->shm_fd = shm_open(shm->name, O_RDWR, 0600);
    if(shm->shm_fd >= 0)
    {
        if(!owner_process_set)
        {
            owner_process = 0;
            owner_process_set = 1;
        }
        printf("The shared memory object %s is available and now open.\n", shm->name);
    }
    else if (errno == ENOENT)
    {
        printf("WARN: Shared memory %s doesn't exist, trying creation...\n", shm->name);
        
    }
}
