#include "WorkQueue.h"
#include "WorkQueueImpl.h"

void *WorkQueueImplMalloc(size_t size)
{
    return (void *)malloc(size);
}

void WorkQueueImplFree(void *ptr)
{
    free(ptr);
}

void *WorkQueueImplQueueCreate(const char *name, int16_t size, int16_t count)
{
    return NULL;
}

void WorkQueueImplQueueDestroy(void *queue)
{

}

int32_t WorkQueueImplQueuePush(void *queue, void *data, int32_t timeout)
{
    return 0;
}

int32_t WorkQueueImplQueuePop(void *queue, void *data, int32_t timeout)
{
    return 0;
}

void *WorkQueueImplThreadCreate(WorkQueueImplThreadFunc entry, void *argv, const WorkQueueImplThreadAttr *attr)
{
    return NULL;
}
