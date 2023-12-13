// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

struct sh_mem_t;

struct sh_mem_t* sh_mem_new();

void sh_mem_delete(struct sh_mem_t*);

void sh_mem_ctor(struct sh_mem_t*,
                 const char*, // name
                 size_t); // size

void sh_mem_dtor(struct sh_mem_t*);

char* sh_mem_getptr(struct sh_mem_t*);
__int32_t sh_mem_isowner(struct sh_mem_t*);
void sh_mem_setowner(struct sh_mem_t*, __int32_t is_owner); 