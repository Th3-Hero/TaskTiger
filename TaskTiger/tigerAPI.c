#include "user.h"
#include "date.h"

#include "tigerAPI.h"

#define TIGER_HUNGER_INC 15
#define TIGER_HUNGER_DEC 20
#define POINT_COST 20

Tiger CreateTiger() {
	Tiger newTiger;

	newTiger.hunger = 100;
	newTiger.lastChecked = getCurrentDate();
	newTiger.lastFed = getCurrentDate();
}

void FeedTiger(User* user)
{
	// If user has enough points, feed tiger
	if (user->points >= POINT_COST) {
		user->points -= POINT_COST;
		user->tiger.hunger += TIGER_HUNGER_INC;
	}
}

void UpdateTigerHunger(Tiger* tiger) {
	// If last checked on today, don't update
	if (dateDifference(tiger->lastChecked, getCurrentDate()) == 0) return;

	if (dateDifference(tiger->lastFed, getCurrentDate()) == 1)
		tiger->hunger -= TIGER_HUNGER_DEC;

	// decrease hunger by last date fed
	for (int i = 0; i < 4; i++) {
		if (dateDifference(tiger->lastFed, getCurrentDate()) == i)
			tiger->hunger -= TIGER_HUNGER_DEC * i;
	}

	// Make sure hunger doesn't go negative
	if (tiger->hunger < 0) tiger->hunger = 0;

	if (dateDifference(tiger->lastFed, getCurrentDate()) >= 5)
		tiger->hunger = 0;
}

int GetTigerHunger(Tiger* tiger) {
	UpdateTigerHunger(tiger);

	return tiger->hunger;
}

void DetermineTigerMood(User* user) {
	Tiger* tiger = &(user->tiger);

	UpdateTigerHunger(tiger);

	tiger->lastChecked = getCurrentDate();

	if (tiger->hunger >= 75) {
		tiger->tigerMood = HAPPY;
	}
	else if (tiger->hunger >= 25) {
		tiger->tigerMood = HUNGRY;
	}
	else {
		tiger->tigerMood = SAD;
	}
}