#ifndef _WORK_QUEUE_IMPL_H_
#define _WORK_QUEUE_IMPL_H_

#include "WorkQueue.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void *WorkQueueImplMalloc(size_t size);
void WorkQueueImplFree(void *ptr);

void *WorkQueueImplQueueCreate(const char *name, int16_t size, int16_t count);
void WorkQueueImplQueueDestroy(void *queue);
int32_t WorkQueueImplQueuePush(void *queue, void *data, int32_t timeout);
int32_t WorkQueueImplQueuePop(void *queue, void *data, int32_t timeout);

typedef void *(*WorkQueueImplThreadFunc)(void *argv);

typedef struct WorkQueueImplThreadAttr
{
    const char *name;   // name of the thread
    uint32_t stackSize;   // size of stack
    uint8_t priority;     // initial thread priority
    uint8_t reserved1;    // reserved1 (must be 0)
    uint16_t reserved2;   // reserved2 (must be 0)
} WorkQueueImplThreadAttr;

void *WorkQueueImplThreadCreate(WorkQueueImplThreadFunc entry, void *argv, const WorkQueueImplThreadAttr *attr);

#endif // !_WORK_QUEUE_IMPL_H_
