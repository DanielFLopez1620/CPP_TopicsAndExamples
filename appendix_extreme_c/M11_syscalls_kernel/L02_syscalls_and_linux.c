// BASED ON THE "EXTREM C BOOK - 1 EDITION"
// Code wasn't tested

// NOTE: Do not try to run this file as it is experimental and may change you config.
// RISK OF SYS CORRUPTION

/**
 * For using C with kernel, we call it 'kernel development'. Keep in mind:
 * 
 * - Only one kernel process can run at a time, so if you get a crash, you will need a reboot.
 * - There is not glibc and its standards are not valid. So, do not try to call <stdio.h> or related. You
 *   will need 'kernel headers' and they may change according to your Unix. (Now you use <sys/system.h>)
 * - You can read/modify files but with different methods from the ones of libc.
 * - You have full permissions and access, so write secure  and relaible code.
 * - Do not use syscalls, you do not need them.
 * - A kernel process is created by copying images by using the boot loader, so you will
 *  need to do this to apply changes.
 * 
 * NOTE: Linux is a kernel, not a OS.
 * 
 * If you have a virtualization or a linux distro for experiments (not for works/studies),
 * you can make the next practice:
 * 
 *     sudo apt-get update
 *     sudo apt-get install -y build-essential autoconf  libncurses5-dev libssl-dev flex libelf-dev git
 * 
 * NOTE: apt is the main package manager from debian systems, sudo means super user mode.
 * 
 *     git clone https://github.com/torvalds/linux
 *     cd linux
 *     git checkout v5.3
 * 
 * Here you can explore the directories and watch for something that calls your attention.
 * 
 * Now, you can focus on the file of the sys calls: include/linux/syscalls.h, as this is generic
 * all linux archs exposes the same set of syscalls.
 * 
 * After this, you an generate a test, create a file and a folder: mkdir hello_workd/sys_hello_world.c, and
 * try with the code down here, in this file.
 * 
 * This code implements a macro for a syscall (with 4 args), but for implementing or know this call, you
 * will need to add it to the arch path: arch/x86/entry/syscalss/syscall_64.tbl
 * 
 *  999   64   hello_world    __x64_sys_hello_world
 * 
 * Here the '__x64' is used to indicate that the call is only for x64 systems. Now, for creating the kernel
 * you will need to create a Makefile (in the directory you have been using) with the next content for:
 
 *    obj-y := sys_hello_world.o
 * 
 * Then, the kernel path should be changed, from this:
 *  
 *    core-y += kernel/certs/mm/fs/ipc/security/crypto/block
 * 
 * To:
 * 
 *    core-y += kernel/certs/mm/fs/hello_world/ipc/security/crypto/block
 * 
 * With this done, you could build your kernel (remember, only if you are in an experimental environment that you
 * do not need working after trying this), for that you run:
 * 
 *     make localmodconfig
 *     make -j4
 *     sudo make modules_install install
 *     uname -r
 *     sudo reboot
 *     # After reboot
 *     uname -r 
 * 
 * If it works well, you should be able to  run and test the call:
 * 
 *     gcc L02_experimental_test.c -o sys_test.out
 *     dmesg
 *     strace ./sys_test.out
 * 
*/

#include <linux/kernel.h> // For printk
#include <linux/string.h> // For strcpy, strcat, strlen
#include <linux/slab.h> // For kmalloc, kfree
#include <linux/uaccess.h> // For copy_from_user, copy_to_user
#include <linux/syscalls.h> // For SYSCALL_DEFINE4
// Definition of the system call
SYSCALL_DEFINE4(hello_world,
                const char __user *, str, // Input name
                const unsigned int, str_len, // Length of input name
                char __user *, buf, // Output buffer
                unsigned int, buf_len) { // Length of output buffer
    // The kernel stack variable supposed to keep the content
    // of the input buffer
    char name[64];
    // The kernel stack variable supposed to keep the final
    // output message.
    char message[96];
    printk("System call fired!\n");
    if (str_len >= 64) {
    printk("Too long input string.\n");
    return -1;
    }
    // Copy data from user space into kernel space
    if (copy_from_user(name, str, str_len)) {
    printk("Copy from user space failed.\n");
    return -2;
    }
    // Build up the final message
    strcpy(message, "Hello ");
    strcat(message, name);
    strcat(message, "!");
    // Check if the final message can be fit into the output binary
    if (strlen(message) >= (buf_len - 1)) {
    printk("Too small output buffer.\n");
    return -3;
    }
    // Copy back the message from the kernel space to the user space
    if (copy_to_user(buf, message, strlen(message) + 1)) {
    printk("Copy to user space failed.\n");
    return -4;
    }
    // Print the sent message into the kernel log
    printk("Message: %s\n", message);
    return 0;
}
