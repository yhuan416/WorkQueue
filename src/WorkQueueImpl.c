#include "WorkQueue.h"
#include "WorkQueueImpl.h"

#include <mqueue.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

struct Queue
{
    char *name;
    mqd_t id;
    int32_t msg_size;
};

void *WorkQueueImplMalloc(size_t size)
{
    return (void *)malloc(size);
}

void WorkQueueImplFree(void *ptr)
{
    free(ptr);
}

void *WorkQueueImplQueueCreate(const char *name, int32_t size, int32_t count)
{
    struct Queue *mq = NULL;
    mqd_t new_mq;
    struct mq_attr attr;

    // Check the parameters
    if (name == NULL || size <= 0 || count <= 0) {
        return -1;
    }

    // Set the queue attributes
    attr.mq_flags = 0;
    attr.mq_maxmsg = count;
    attr.mq_msgsize = size;
    attr.mq_curmsgs = 0;

    // Create the queue
    new_mq = mq_open(name, O_CREAT | O_RDWR, 0644, &attr);
    if (new_mq == (mqd_t) -1) {
        perror("mq_open");
        return -1;
    }

    // Allocate the queue structure
    mq = (struct Queue *)WorkQueueImplMalloc(sizeof(struct Queue));

    // Save the parameters
    mq->id = new_mq;
    mq->name = name;

    return (void *)mq;
}

void WorkQueueImplQueueDestroy(void *queue)
{
    struct Queue *mq = (struct Queue *)queue;

    // Close the queue
    if (mq_close(mq->id) == -1) {
        perror("mq_close");
        return;
    }

    // Delete the queue
    if (mq_unlink(mq->name) == -1) {
        perror("mq_unlink");
        return;
    }
}

int32_t WorkQueueImplQueuePush(void *queue, void *data, int32_t timeout)
{
    struct timespec ts;
    const struct timespec *abs_timeout = NULL;

    struct Queue *mq = (struct Queue *)queue;

    // Check the parameters
    if (data == NULL) {
        return -1;
    }

    if (timeout != (-1)) {
        clock_gettime(CLOCK_REALTIME, &ts);

        ts.tv_sec += timeout / 1000;
        ts.tv_nsec += (timeout % 1000) * 1000;

        abs_timeout = &ts;
    }

    // Send the message
    if (mq_timedsend(mq->id, data, mq->msg_size, 0, abs_timeout) == -1) {
        return -1;
    }

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
