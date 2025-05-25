#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "Bandit.h"
#include "Queue.h"

#define MAX_NEIGHBORS 8

static const Site NEIGHBORS[MAX_NEIGHBORS] = {
	{-1, -1}, /* NORTHWEST */
	{-1, 1},  /* NORTHEAST */
	{1, -1},  /* SOUTHWEST */
	{1, 1},   /* SOUTHEAST */
	{-1, 0},  /* NORTH */
	{1, 0},   /* SOUTH */
	{0, -1},  /* WEST */
	{0, 1}    /* EAST */
};

/**
 * Calculates the longest path from the bandit to the police using BFS.
 *
 * @param game The current game state.
 */
static void calculateLongestPath(Game* game) {
	if (game == NULL || game->banditData == NULL || game->scenario == NULL) return;

	int scenarioSize = game->N;
	BanditData* banditData = game->banditData;

	/* Initialize distances to -1 (unvisited yet) */
	int i, j;
	for (i = 0; i < scenarioSize; i++) {
		for (j = 0; j < scenarioSize; j++) {
			banditData->distances[i][j] = -1;
		}
	}

	/* Create a queue for BFS (capacity = scenario size squared, because max number of sites is that)*/
	Queue* queue = createQueue(scenarioSize * scenarioSize);
	if (queue == NULL) {
		fprintf(stderr, "Failed to create queue\n");
		return;
	}

	/* Start BFS from the police's position.
	 * Distance is 0 because it's the starting point.
	 * The BFS will do the job reversing the path.
	 */
	Site policeSite = getPoliceSite(game);
	banditData->distances[policeSite.i][policeSite.j] = 0;
	enQueue(queue, policeSite);

	/* Loop of BFS algorithm */
	while (!isQueueEmpty(queue)) {
		Site currentSite = deQueue(queue);
		int distanceFromPolice = banditData->distances[currentSite.i][currentSite.j];

		/* Explore all 8 possible neighbors */
		int k;
		for (k = 0; k < MAX_NEIGHBORS; k++) {
			Site currentNeighbor = (Site){
				currentSite.i + NEIGHBORS[k].i,
				currentSite.j + NEIGHBORS[k].j
			};

			/* Check if the neighbor is within the scenario boundaries */
			if (currentNeighbor.i >= 0 && currentNeighbor.i < scenarioSize && currentNeighbor.j >= 0 && currentNeighbor.j < scenarioSize) {
				if (isLegalMoveScenario(game->scenario, currentSite, currentNeighbor) && banditData->distances[currentNeighbor.i][currentNeighbor.j] == -1) {
					banditData->distances[currentNeighbor.i][currentNeighbor.j] = distanceFromPolice + 1;
					enQueue(queue, currentNeighbor);
				}
			}
		}
	}

	freeQueue(queue);
}

/**
 * Finds the best move for the bandit to escape the police.
 *
 * @param game The current game state.
 * @param bandit The current bandit's position.
 * @param banditData The bandit's data.
 * @return The best move for the bandit.
 */
static Site findLongestPath(Game* game, Site bandit, BanditData* banditData) {
	Site bestMove = (Site) {-1, -1};
	int maxDistance = -1;

	int i;
	for (i = 0; i < MAX_NEIGHBORS; i++) {
		Site currentNeighbor = (Site){
			bandit.i + NEIGHBORS[i].i,
			bandit.j + NEIGHBORS[i].j
		};

		if (currentNeighbor.i >= 0 && currentNeighbor.i < game->N && currentNeighbor.j >= 0 && currentNeighbor.j < game->N) {
			if (isLegalMoveScenario(game->scenario, bandit, currentNeighbor)) {
				int neighborDistance = banditData->distances[currentNeighbor.i][currentNeighbor.j];
				if (neighborDistance > maxDistance) {
					maxDistance = neighborDistance;
					bestMove = currentNeighbor;
				}
			}
		}
	}

	return bestMove;
}

/**
 * Moves the bandit to the best position to escape the police.
 *
 * @param game The current game state.
 * @return The best move for the bandit.
 */
Site moveBandit(Game* game) {
	Site move;
	move.i = 0;
	move.j = 0;

	if (game) {
		calculateLongestPath(game);

		Site bandit = getBanditSite(game);
		BanditData* banditData = game->banditData;

		if (banditData->distances[bandit.i][bandit.j] < 0) return move;

		move = findLongestPath(game, bandit, banditData);
	}

	return move;
}
