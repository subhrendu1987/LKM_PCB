#include <linux/module.h>
#include <linux/sched.h>
#include <linux/pid.h>

static int pid = 0;
module_param(pid, int, 0644);
MODULE_PARM_DESC(pid, "The PID of the process");

static int __init print_sched_entity_init(void) {
    struct task_struct *task;
    struct sched_entity *se;
    struct pid *pid_struct;

    if (pid <= 0) {
        pr_err("Invalid PID: %d\n", pid);
        return -EINVAL;
    }

    pid_struct = find_get_pid(pid);
    if (!pid_struct) {
        pr_err("Invalid PID: %d\n", pid);
        return -EINVAL;
    }

    task = pid_task(pid_struct, PIDTYPE_PID);
    if (!task) {
        pr_err("No task for PID: %d\n", pid);
        return -ESRCH;
    }

    se = &task->se;

    pr_info("LKM_PCB:sched_entity for PID %d:\n", pid);
    pr_info("LKM_PCB:Load Weight: %lu\n", se->load.weight);
    pr_info("LKM_PCB:Virtual Runtime: %llu\n", se->vruntime);
    pr_info("LKM_PCB:Execution Start Time: %llu\n", se->exec_start);

    return 0;
}

static void __exit print_sched_entity_exit(void) {
    pr_info("LKM_PCB:Exiting module\n");
}

module_init(print_sched_entity_init);
module_exit(print_sched_entity_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Print struct sched_entity for a PID");
