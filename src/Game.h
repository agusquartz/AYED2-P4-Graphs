#pragma once
#ifndef DEFINE_GAME_H
#define DEFINE_GAME_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "Scenario.h"
#define MAX_LINE_LENGTH 80

/**
 * Represents the data for the police's strategy.
 */
typedef struct _PoliceData {
	int** distances;
	int scenarioSize;
}PoliceData;

/**
 * Represents the data for the bandit's strategy.
 */
typedef struct _BanditData {
	int** distances;
	int scenarioSize;
} BanditData;

/**
 * Represents the game state.
 */
typedef struct _Game {
	Scenario* scenario;
	char POLICE;
	char BANDIT;
	int N; // Size of the scenario
	Site policeSite; // Current position of the police
	Site banditSite; // Current position of the bandit
	PoliceData* policeData; // Data for the police's strategy
	BanditData* banditData; // Data for the bandit's strategy
}Game;

Game* createGame(char* fileName);
void destroyGame(Game* g);
Site getPoliceSite(Game* g);
Site getBanditSite(Game* g);
Scenario* getScenario(Game* g);
void printGame(Game* g);
void playGame(Game* g);

PoliceData* createPoliceData(Game* g);
void destroyPoliceData(PoliceData* r);

BanditData* createBanditData(Game* g);
void destroyBanditData(BanditData* r);

#endif