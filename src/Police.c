#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Police.h"
#include "Queue.h"

#define MAX_NEIGHBORS 8

/**
 * An array of the 8 possible neighboring sites.
 * We placed the diagonals between sides to make police look smarter.
 */
static const Site NEIGHBORS[MAX_NEIGHBORS] = {
	{-1, -1},	/* NORTHWEST */
	{-1, 0},	/* NORTH */
	{-1, 1},	/* NORTHEAST */
	{1, 0},		/* SOUTH */
	{1, -1},	/* SOUTHWEST */
	{0, -1},	/* WEST */
	{1, 1},		/* SOUTHEAST */
	{0, 1}		/* EAST */
};

/**
 * Calculates the shortest path from the police to the bandit using BFS.
 *
 * @param game The current game state.
 */
static void calculateShortestPath(Game* game){
	if (game == NULL || game->policeData == NULL || game->scenario == NULL) return;

	int scenarioSize = game->N;
	PoliceData* policeData = game->policeData;

    /* Initialize distances to -1 (unvisited yet) */
	int i, j;
	for (i = 0; i < scenarioSize; i++){
		for (j = 0; j < scenarioSize; j++){
			policeData->distances[i][j] = -1;
		}
	}

	/* Create a queue for BFS (capacity = scenario size squared, because max number of sites is that)*/
	Queue* queue = createQueue(scenarioSize * scenarioSize);
	if (queue == NULL) {
		fprintf(stderr, "Failed to create queue\n");
		return;
	}

	/* Start BFS from the bandit's position.
	 * Distance is 0 because it's the starting point.
	 * The BFS will do the job reversing the path.
	 */
	Site banditSite = getBanditSite(game);
	policeData->distances[banditSite.i][banditSite.j] = 0;
	enQueue(queue, banditSite);

    /* Loop of BFS algorithm */
	while (!isQueueEmpty(queue)){
		Site currentSite = deQueue(queue);
		int distanceFromBandit = policeData->distances[currentSite.i][currentSite.j];

		/* Explore all 8 possible neighbors */
		int k;
		for (k = 0; k < MAX_NEIGHBORS; k++){
			Site currentNeighbor = (Site){
				currentSite.i + NEIGHBORS[k].i,
				currentSite.j + NEIGHBORS[k].j
			};

			/* Check if the neighbor is within the scenario boundaries */
			if (currentNeighbor.i >= 0 && currentNeighbor.i < scenarioSize && currentNeighbor.j >= 0 && currentNeighbor.j < scenarioSize){
				if (isLegalMoveScenario(game->scenario, currentSite, currentNeighbor) && policeData->distances[currentNeighbor.i][currentNeighbor.j] == -1){
					policeData->distances[currentNeighbor.i][currentNeighbor.j] = distanceFromBandit + 1;
					enQueue(queue, currentNeighbor);
				}
			}
		}
	}

	freeQueue(queue);
}

/**
 * Finds the shortest path from the police to the bandit.
 *
 * @param game The current game state.
 * @param police The current position of the police.
 * @param policeData The police data.
 * @return The next move for the police.
 */
static Site findShortestPath(Game* game, Site police, PoliceData* policeData){
	Site bestMove = (Site) {-1, -1};
	int minDistance = policeData->distances[police.i][police.j];

	int i;
	for (i = 0; i < MAX_NEIGHBORS; i++){
		Site currentNeighbor = (Site){
			police.i + NEIGHBORS[i].i,
			police.j + NEIGHBORS[i].j
		};

		if (currentNeighbor.i >= 0 && currentNeighbor.i < game->N && currentNeighbor.j >= 0 &&  currentNeighbor.j < game->N){
			if (isLegalMoveScenario(game->scenario, police, currentNeighbor)){
				int neighborDistance = policeData->distances[currentNeighbor.i][currentNeighbor.j];
				if (neighborDistance >= 0 && neighborDistance < minDistance){
					minDistance = neighborDistance;
					bestMove = currentNeighbor;
				}
			}
		}
	}

	return bestMove;
}

/* Determines the nex move for the police by moving on step along the shortest
 * path towards the bandit.
 *
 * @param game The current game state.
 * @return The next move for the police, negative coordinates if game is invalid or no move is possible.
 */
Site movePolice(Game* game) {
	Site move;
	move.i = 0;
	move.j = 0;

	if (game) {

		calculateShortestPath(game);

		Site police = getPoliceSite(game);
		PoliceData* policeData = game->policeData;

		if (policeData->distances[police.i][police.j] < 0) return move;

		move = findShortestPath(game, police, policeData);
	}

	return move;
}