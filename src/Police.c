#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdlib.h>
#include "Police.h"

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
static Queue* createQueue(int capacity){
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
static bool isQueueEmpty(Queue* queue){
	return (queue == NULL) || (queue->count == 0);
}

/**
 * Enqueues a site into the queue.
 *
 * @param queue The queue to enqueue the site into.
 * @param site The site to enqueue.
 */
static void enQueue(Queue* queue, Site site){
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
static Site deQueue(Queue* queue){
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
static void freeQueue(Queue* queue){
	if (queue == NULL) return;

	free(queue->elements);
	free(queue);
}


/* Determines the nex move for the police by moving on step along the shortest
 * path towards the bandit.
 *
 * @param game The current game state.
 * @return The next move for the police, negative coordinates if game is invalid or no move is possible.
 */
Site movePolice(Game* game) {
	/*REPLACE THIS WITH YOUR CODE TO GET SHORTEST PATH TO ROGUE*/
	Site move;
	move.i = 0;
	move.j = 0;
	if (game) {
		PoliceData* md = game->policeData;
		Site police = getPoliceSite(game);
		Site bandit = getBanditSite(game);

		// take random legal move
		int n = 0;
		for (int i = 0; i < game->N; i++) {
			for (int j = 0; j < game->N; j++) {
				//Site site = new Site(i, j);
				Site site;
				site.i = i;
				site.j = j;
				if (isLegalMoveScenario(game->scenario, police, site)) {
					n++;
					if (rand() % 1000 <= 1000 / n) {
						move.i = site.i;
						move.j = site.j;
					}
				}
			}
		}
	}
	return move;
}