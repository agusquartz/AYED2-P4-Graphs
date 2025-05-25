#ifndef QUEUE_H
#define QUEUE_H

#include "Scenario.h"
#include <stdbool.h>

/**
 * A FIFO queue of sites for BFS exploration.
 */
typedef struct {
    Site *elements;
    int capacity;
    int count;
    int head;
    int tail;
} Queue;

/**
 * Creates a new queue with the given capacity.
 *
 * @param capacity The capacity of the queue.
 * @return A pointer to the new queue, or NULL if memory allocation fails.
 */
Queue* createQueue(int capacity);

/**
 * Checks if the queue is empty.
 *
 * @param queue The queue to check.
 * @return True if the queue is empty, false otherwise.
 */
bool isQueueEmpty(Queue* queue);

/**
 * Enqueues a site into the queue.
 *
 * @param queue The queue to enqueue the site into.
 * @param site The site to enqueue.
 */
void enQueue(Queue* queue, Site site);

/**
 * Dequeues a site from the queue.
 *
 * @param queue The queue to dequeue the site from.
 * @return The dequeued site, or negative coordinates if the queue is NULL or empty.
 */
Site deQueue(Queue* queue);

/**
 * Frees the memory allocated for a queue.
 *
 * @param queue The queue to free.
 */
void freeQueue(Queue* queue);

#endif // QUEUE_H 