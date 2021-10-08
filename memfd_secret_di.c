#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <errno.h> 

int main(void){
	printf("memfd_secret");
        int fd;
        fd = syscall(SYS_memfd_secret, O_CLOEXEC);
	printf("The fd: %d\n", fd);
	printf("errno = %d\n", errno);
        return 0;
}
