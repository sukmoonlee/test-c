#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define MEBIBYTE	1024*1024

void allocate_4k_pages_virt(int count) {
    int ret;
    ret = system("cp -f /proc/meminfo meminfo.before");
    printf("Attempting to allocate %i Mebibytes of virtual memory...\n", count);

    char *flops;
    int i;
    for (i=0; i<count; i++) {
        flops = malloc(MEBIBYTE);
        if (flops==NULL) {
            printf("Error allocating page %i, exiting\n", i+1);
            exit(132);
        }
        if ((i+1)%100==0) {
            printf("Allocated %i MiB\n", i+1);
        };
    }

    ret = system("ps aux |head -1");
    ret = system("ps aux |grep vsz |grep -v grep|grep -v bash");

    ret = system("cp -f /proc/meminfo meminfo.after");
    ret = system("sdiff -sd meminfo.before meminfo.after");

	char buffer[128];
	snprintf(buffer, sizeof(buffer), "cat /proc/%d/status", getpid());
    ret = system(buffer);
    printf("Press <Enter> to exit");
    fgetc(stdin);
}

int main(int argc, char *argv[]) {
    int count=100;

	if (argv[1]!=NULL) { count=atoi(argv[1]); }
    allocate_4k_pages_virt(count);
    return 0;
}
