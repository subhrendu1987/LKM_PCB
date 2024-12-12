#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/pid.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Print Scheduler Class for a given PID");

static int pid = -1; // Default PID
module_param(pid, int, 0444);
MODULE_PARM_DESC(pid, "PID of the task");

static int __init sched_class_init(void) {
    struct task_struct *task;
    
    if (pid < 0) {
        printk(KERN_ERR "Invalid PID provided.\n");
        return -EINVAL;
    }

    // Find the task_struct for the given PID
    task = find_task_by_vpid(pid);
    if (!task) {
        printk(KERN_ERR "Task with PID %d not found.\n", pid);
        return -ESRCH;
    }

    // Check the scheduler class and print its name
    if (task->sched_class == &fair_sched_class) {
        printk(KERN_INFO "LKM_SCHED:PID %d is using the fair scheduler class.\n", pid);
    } else if (task->sched_class == &rt_sched_class) {
        printk(KERN_INFO "LKM_SCHED:PID %d is using the real-time scheduler class.\n", pid);
    } else if (task->sched_class == &idle_sched_class) {
        printk(KERN_INFO "LKM_SCHED:PID %d is using the idle scheduler class.\n", pid);
    } else if (task->sched_class == &dl_sched_class) {
        printk(KERN_INFO "LKM_SCHED:PID %d is using the deadline scheduler class.\n", pid);
    } else {
        printk(KERN_INFO "LKM_SCHED:PID %d is using an unknown scheduler class.\n", pid);
    }

    return 0;
}

static void __exit sched_class_exit(void) {
    printk(KERN_INFO "LKM_SCHED:Scheduler class module unloaded.\n");
}

module_init(sched_class_init);
module_exit(sched_class_exit);
