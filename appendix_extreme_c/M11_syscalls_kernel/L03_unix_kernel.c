// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code was tested with gcc

#include <stdio.h>

/**
 * A kernel structure is not standarized, but it has different types. But here the thing
 * they have in common is the form they expose their functionalities (with syscalls).
 * 
 * In one hand, we have the monolithic kernel, which means there is one kernel process and 
 * then one adress that contains smaller parts of the process. On the other hand, we have the
 * microkernel approach which is based on services and pushing them to the filesystem, devices
 * and process managment to create smaller processes.
 * 
 * To mention more differences of them:
 * 
 * - Monolithic is a sinlge process that contains all the services provided, and it's located
 * in the kernel space, they are fast as all the resources are in the same place. In terms of devices,
 * the drivers in the kernel, so if a driver fails it could crash the kernel. Also, in security
 * terms, if malware reaches the kernel, a small bunch of it can crash the system. Finally, a change
 * means that all the kernel need to be compiled again.
 * 
 * - Microkernel uses server processes taht are located in the user space, this adds a security
 * layer where not everything will be damaged if a malicious code is injected. Also, if changes are
 * needed, only some services need to be compiled again.
 * 
 * LINUX: Was developed by Linus Torvalds, after the invention of MINIX, and it's a monolithic
 * kernel system. But it offered some changes, kernel modules can be written and modified dinamically.
 * But what is a kernel module? It a tool for develop new functionalities in a running kernel and they
 * are 'kernel object files' that are compiled and loaded dynamically. A recommendation here, if
 * something goes wrong with a module the kernel will crash. Now let's mention some facts:
 * 
 * - They aim to be used by device drivers, remember that they are located in /dev.
 * - The /proc dir can be used to read meta-info of kernel modules.
 * - Similar to procfs, it exists another option called sysfs.
 * 
 * If you are asking about adding a kernel module, of course there is a possibility to do it (with a
 * lot of care), and we can do that with a C file. Similar to the case exposed before, we need to define
 * syscalls inside of it and create an implementation in the /proc dir. After this, you can create
 * a 'Makefile' to trigger the build tools, construct and clean the space. Then run 'make' and when all
 * is ready, you should be able to run 'insmod' with sudo to load the kernel module.
 * 
 * For checking the results you can use 'dmesg' or use 'cat' on the object in the /proc dir.
 * 
 * NOTE: Kernel object files use the extension '.ko'. And they can be loaded or unloaded without
 * rebooting the system. As a recommendation, take care on what you add, because they can be vulnerabilities
 * to your system if not managed well.
 * 
*/

int main(int argc, char const *argv[])
{
    prinf("Here is a list of resources if you are interested in knowing more:\n");
    prinf("\thttps://en.wikipedia.org/wiki/Tanenbaum%%E2%%80%%93Torvalds_debate\n");
    return 0;
}
