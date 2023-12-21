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

/**
 * Generate a new shared memory object allocation 
 * 
 * @return Direction in memory to the allocated object.
*/
sh_mem_t* sh_mem_new()
{
    return (sh_mem_t*) malloc(sizeof(sh_mem_t));
}

/**
 * Delete and free pointer of the object and inner pointers.
 * 
 * @param shm Pointer to the shared memory object structure.
*/
void sh_mem_delete(sh_mem_t* shm)
{
    free(shm->name);
    free(shm);
}

/**
 * Constructor of a shared memory object
 * 
 * @param shm  Pointer to the shared memory object structure.
 * @param name  Name of the shared memory region
 * @param size  Size in bytes of the shared memory object
 * 
 * @return Pointer to the mapped shared memory region.
 * 
 * @exception Launches a warn if the shared memory object isn't available.
 * @exception Launches an error and exits if the shared memory isn't available and couldn't be created.
 * @exception Launches an error and exits if the region couldn't be truncated after creation.
 * @exception Launches an error and exits if it wasn't possible to map the region
*/
void sh_mem_ctor(sh_mem_t* shm, const char* name, size_t size)
{
    shm->size = size;
    shm->name = (char*)malloc(strlen(name) + 1); // Manually allocate string
    strcpy(shm->name, name);
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
        shm->shm_fd = shm_open(shm->name, O_CREAT | O_RDWR, 0600);
        if(shm->shm_fd >= 0)
        {
            if(owner_process_set)
            {
                owner_process = 1;
                owner_process_set = 1;
            }
            printf("The shared memory %s was created.\n", shm->name);
            if(ftruncate(shm->shm_fd, shm->size) < 0)
            {
                fprintf(stderr, "ERROR: Couldn't truncate region %s: %s\n", shm->name, strerror(errno));
                exit(1);
            }
        }
        else
        {
            fprintf(stderr, "ERROR: Shared memory %s wasn't created: %s\n", shm->name, strerror(errno));
            exit(1);
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Couldn't create shared memory %s: %s\n", shm->name, strerror(errno));
        exit(1);
    }

    shm->map_ptr = mmap(0, shm->size, PROT_READ | PROT_WRITE, MAP_SHARED, shm->shm_fd, 0);
    if(shm->map_ptr == MAP_FAILED)
    {
        fprintf(stderr, "ERROR: Couldn't map region %s: %s\n", shm->name, strerror(errno));
        exit(1);
    }
    shm->ptr = (char*) shm->map_ptr;
}

/**
 * Destructor of shared memory object
 * 
 * @param shm Pointer to the shared memory object
 * 
 * @exception Launches an error and exits if the memory region cannot be unmapped.
 * @exception Launches an error and exits if the couldn't close the sahred memory region.
 * @exception Launches an error and extis if the unlinking process (in case of ownership) fails.
*/
void sh_mem_dtor(sh_mem_t* shm)
{
    if (munmap(shm->map_ptr, shm->size) < 0)
    {
        fprintf(stderr, "ERROR: Couldn't unmap region %s: %s\n", shm->name, strerror(errno));
        exit(1);
    }
    printf("Unmapping achieved for region: %s\n", shm->name);

    if(close(shm->shm_fd) < 0)
    {
        fprintf(stderr, "ERROR: Couldn't close shared memory region %s: %s\n", shm->name, strerror(errno));
        exit(1);
    }
    printf("The shared memory %s was closed succesfully", shm->name);

    if(owner_process)
    {
        if(shm_unlink(shm->name) < 0)
        {
            fprintf(stderr, "ERROR: Unlinking %s wasn't achieved: %s\n", shm->name, strerror(errno));
            exit(1);
        }
        printf("The memory region %s was unlinked and deleted\n", shm->name);
    }
}

/**
 * Getter of the pointer of the shared memory region.
 * 
 * @param shm Pointer to the shared memory object.
 * 
 * @return Pointer to the memory region.
*/
char* sh_mem_getptr(sh_mem_t* shm)
{
    return shm->ptr;
}

/**
 * Getter of the ownership of the shared memory object.
 * 
 * @param shm Pointer to the shared memory object
 * 
 * @return True (1) if it is owner of the region, False (0) otherwise.
*/
__int32_t sh_mem_isowner(sh_mem_t* shm)
{
    return owner_process;
}
