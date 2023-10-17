#ifndef _WORK_QUEUE_H_
#define _WORK_QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct WorkQueueConfig
{
    uint32_t stackSize;   // size of stack
    uint16_t queueSize;   // size of the queue
    uint8_t priority;     // thread priority
} WorkQueueConfig;

typedef struct WorkQueue
{
    void *queue; // queue id
    uint16_t queueSize; // size of the queue

    void *thread; // thread id
    uint32_t stackSize;   // size of stack
    uint8_t priority;     // thread priority

    int8_t ref; // reference count
} WorkQueue;

// 创建一个工作队列
WorkQueue *WorkQueueCreate(const char *name, const WorkQueueConfig *config);

// 启动工作队列
int32_t WorkQueueStart(WorkQueue *wq);

// 停止工作队列(如果当前工作队列已经没有被别的线程引用, 自动销毁)
int32_t WorkQueueRelease(WorkQueue *wq);

// 添加一个引用, 返回NULL则失败
WorkQueue *WorkQueueReference(WorkQueue *wq);

// thread local storage, 获取当前线程的队列
void *WorkQueueGetCurrentQueue(void);

#endif // !_WORK_QUEUE_H_
