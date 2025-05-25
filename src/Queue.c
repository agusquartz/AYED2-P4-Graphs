#include "Queue.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Creates a new queue with the given capacity.
 *
 * @param capacity The capacity of the queue.
 * @return A pointer to the new queue, or NULL if memory allocation fails.
 */
Queue* createQueue(int capacity) {
    if (capacity <= 0) return NULL;

    Queue* queue = (Queue*) malloc(sizeof(Queue));
    if (queue == NULL) return NULL;

    queue->elements = (Site*) malloc(capacity * sizeof(Site));
    if (queue->elements == NULL) {
        free(queue);
        return NULL;
    }

    queue->capacity = capacity;
    queue->count = 0;
    queue->head = 0;
    queue->tail = 0;
    return queue;
}

/**
 * Checks if the queue is empty.
 *
 * @param queue The queue to check.
 * @return True if the queue is empty, false otherwise.
 */
bool isQueueEmpty(Queue* queue) {
    return (queue == NULL) || (queue->count == 0);
}

/**
 * Enqueues a site into the queue.
 *
 * @param queue The queue to enqueue the site into.
 * @param site The site to enqueue.
 */
void enQueue(Queue* queue, Site site) {
    if (queue == NULL || queue->count >= queue->capacity) return;

    queue->elements[queue->tail] = site;

    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->count++;
}

/**
 * Dequeues a site from the queue.
 *
 * @param queue The queue to dequeue the site from.
 * @return The dequeued site, or negative coordinates if the queue is NULL or empty.
 */
Site deQueue(Queue* queue) {
    if (queue == NULL) return (Site) {-1, -1};

    Site site = queue->elements[queue->head];

    queue->head = (queue->head + 1) % queue->capacity;
    queue->count--;

    return site;
}

/**
 * Frees the memory allocated for a queue.
 *
 * @param queue The queue to free.
 */
void freeQueue(Queue* queue) {
    if (queue == NULL) return;

    free(queue->elements);
    free(queue);
} 