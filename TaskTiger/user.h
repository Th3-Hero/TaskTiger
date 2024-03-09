#pragma once

#include <stdbool.h>

#define MAX_PASSWORD_LENGTH 64

typedef enum TigerStatus {
	GRUMPY,
	STRESSED,
	ANXIOUS,
	HUNGRY,
	SAD,
	HAPPY
} TigerStatus;


typedef struct User {
	char passward[MAX_PASSWORD_LENGTH];
	int points;
	TigerStatus tigerStatus;
} User;


User createUser(const char* password, int points, TigerStatus tigerStatus);

bool equalUser(User, User);

User copyUser(User);

bool CopyUserInPlace(User* dest, User src);




void printTigerStatus(TigerStatus);
void printTigerStatusU(User);


void debugPrintUser(User);