# Variables
KERNEL_SRC := /lib/modules/$(shell uname -r)/build
USER_PROG := set_pid_user_space
MODULE := print_sched_entity

# Default target
all: $(MODULE).ko $(USER_PROG)


# Build kernel module
$(MODULE).ko: $(MODULE).c
	make -C $(KERNEL_SRC) M=$(PWD) modules

# Build user space program
$(USER_PROG): $(USER_PROG).c
	$(CC) -o $(USER_PROG) $(USER_PROG).c

module:
	gcc -Wall -Wextra -D__KERNEL__ -DMODULE -I$(KERNEL_SRC)/include -c print_sched_entity.c -o print_sched_entity.o

# Clean the build
clean:
	make -C $(KERNEL_SRC) M=$(PWD) clean
	rm -f $(USER_PROG)

# Load the kernel module
load: $(MODULE).ko
	sudo insmod $(MODULE).ko

