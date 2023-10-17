#include "WorkQueue.h"
#include "WorkQueueImpl.h"


// 创建一个工作队列
WorkQueue *WorkQueueCreate(const char *name, const WorkQueueConfig *config)
{
    WorkQueue *wq = NULL;

    wq = (WorkQueue *)WorkQueueImplMalloc(sizeof(WorkQueue));
    if (wq == NULL) {
        return NULL;
    }

    wq->queue = WorkQueueImplQueueCreate(name, sizeof(void *), config->queueSize);
    if (wq->queue == NULL) {
        WorkQueueImplFree(wq);
        return NULL;
    }

    wq->queueSize = config->queueSize;

    wq->thread = NULL;
    wq->stackSize = config->stackSize;
    wq->priority = config->priority;

    wq->ref = 0;

    return wq;
}

// 启动工作队列
int32_t WorkQueueStart(WorkQueue *wq)
{
    
}

// 停止工作队列(如果当前工作队列已经没有被别的线程引用, 自动销毁)
int32_t WorkQueueRelease(WorkQueue *wq)
{
    if (wq == NULL) {
        return -1;
    }

    return 0;
}

// 添加一个引用, 返回NULL则失败
WorkQueue *WorkQueueReference(WorkQueue *wq)
{
    if (wq == NULL) {
        return NULL;
    }

    wq->ref++;
    return wq;
}

// thread local storage, 获取当前线程的队列
void *WorkQueueGetCurrentQueue(void)
{
    
}
