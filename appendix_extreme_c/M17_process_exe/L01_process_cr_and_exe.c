// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was not tested

#include <stdio.h>

/**
 * A program is a process, which should come from an executable and it can be executed multiple times.
 * In Unix-like systems, the onion exposes some utilities with the API. But before moving on, there must
 * be a distinction between 'process creation' (spawning a new one) and 'process execution' (using an
 * existing one as host), which are create by syscalls. So, there are two keyworks 'fork' which spawns
 * process and 'exec' which replace the caller of a process.
 * 
 * Here, the POSIX is also important, the 'fork' function is found in the 'unistd.h' file, the 'posix_spawn'
 * and the 'posix_spawnp' are from the file 'spawn.h', and the group of exec*a re also in 'unistd.h'. Where
 * this last ones aren't sys calls, but rather functions to use them.
 *
 *  
 * 
*/