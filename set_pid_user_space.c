#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char command[128];

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PID>\n", argv[0]);
        return 1;
    }

    int pid = atoi(argv[1]);
    if (pid <= 0) {
        fprintf(stderr, "Invalid PID: %d\n", pid);
        return 1;
    }

    // Construct the command to load the kernel module with the PID parameter
    snprintf(command, sizeof(command), "sudo insmod print_sched_entity.ko pid=%d", pid);

    // Execute the command
    int ret = system(command);
    if (ret != 0) {
        fprintf(stderr, "Failed to load module. Are you running as root?\n");
        return 1;
    }

    printf("Module loaded successfully for PID: %d\n", pid);
    printf("Check dmesg for output.\n");

    return 0;
}
