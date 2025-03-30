#include <linux/sched.h>
#include <linux/list.h>
#include "sched.h"
#include <linux/printk.h>

#define pr_debug_yat(fmt, ...) pr_debug("YAT: " fmt, ##__VA_ARGS__)

// // 定义新调度器的运行队列
// struct yat_rq {
//     struct list_head tasks; // 任务链表
//     int nr_running;         // 正在运行的任务数
// };

// 初始化运行队列
void init_yat_rq(struct yat_rq *yat_rq) {
    printk(KERN_EMERG "=======================================init yat rq===================================\n");
    INIT_LIST_HEAD(&yat_rq->tasks);
    yat_rq->nr_running = 0;
}

// 将任务加入队列
static void enqueue_task_yat(struct rq *rq, struct task_struct *p, int flags) {
    printk(KERN_EMERG "====================================enqueue_task_ya======================================\n");
    struct yat_rq *yat_rq = &rq->yat;
    if (!yat_rq) {
        pr_err("enqueue_task_yat: yat_rq is NULL\n");
        return;
    }
    pr_debug_yat("enqueue_task_yat: Adding task %p to rq %p\n", p, rq);
    INIT_LIST_HEAD(&p->run_list); // 初始化任务的 run_list
    list_add_tail(&p->run_list, &yat_rq->tasks); // 假设任务结构体中有 run_list 字段
    yat_rq->nr_running++;
}

// 将任务移出队列
static void dequeue_task_yat(struct rq *rq, struct task_struct *p, int flags) {
    printk(KERN_EMERG "====================================dequeue_task_yat======================================\n");
    struct yat_rq *yat_rq = &rq->yat;
    if (!yat_rq) {
        pr_err("dequeue_task_yat: yat_rq is NULL\n");
        return;
    }
    list_del_init(&p->run_list);
    yat_rq->nr_running--;
}

// 选择下一个任务
static struct task_struct *pick_next_task_yat(struct rq *rq) {
    printk(KERN_EMERG "====================================pick_next_task_yat======================================\n");
    struct yat_rq *yat_rq = &rq->yat;
    if (list_empty(&yat_rq->tasks))
        return NULL; // 没有任务可运行

    struct task_struct *next = list_first_entry(&yat_rq->tasks, struct task_struct, run_list);
    list_rotate_left(&yat_rq->tasks); // 轮转链表
    return next;
}

static void set_next_task_yat(struct rq *rq, struct task_struct *p, bool first) {
    printk(KERN_EMERG "====================================set_next_task_yat======================================\n");
    // TODO: 如果需要，可以添加逻辑
}

// 时间片到期处理
static void task_tick_yat(struct rq *rq, struct task_struct *p, int queued) {
    printk(KERN_EMERG "====================================task_tick_yat======================================\n");
    // TODO: 实现时间片到期逻辑
}

// 定义调度类
DEFINE_SCHED_CLASS(yat) = {
    .enqueue_task       = enqueue_task_yat,
    .dequeue_task       = dequeue_task_yat,
    .pick_next_task     = pick_next_task_yat,
    .set_next_task      = set_next_task_yat, // TODO: 实现设置当前任务逻辑
    .task_tick          = task_tick_yat,
};