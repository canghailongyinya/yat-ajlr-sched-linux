#ifndef _LINUX_SCHED_YAT_H
#define _LINUX_SCHED_YAT_H

#ifdef CONFIG_SCHED_CLASS_YAT
#include <linux/llist.h>
#include <linux/sched.h>
static inline int yat_prio(int prio)
{
	printk(KERN_EMERG "====================================yat_prio======================================\n");
	return 0;
}

static inline int yat_task(struct task_struct *p)
{
	printk(KERN_EMERG "====================================yat_task======================================\n");
	return yat_prio(p->prio);
}

// struct yat_dispatch_q {
// };
// struct sched_yat_entity {
//     u64 slice;
// };
#else /* !CONFIG_SCHED_CLASS_YAT */
#endif /* CONFIG_SCHED_CLASS_YAT */
#endif /* _LINUX_SCHED_YAT_H */