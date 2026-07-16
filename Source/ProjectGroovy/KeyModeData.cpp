// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyModeData.h"

AKeyModeData::AKeyModeData() {
	//  We don't need the tick event
	PrimaryActorTick.bCanEverTick = false;
	// Placeholder values
	song = NULL;
	noteList = {};
	gameState = (EAllGameStates::start);
	active = true;

	// Actual starting values
	noteIndex = 0;
	totalQuarterBeats = 0;
	health = 0.5f;
}

/*Active getter*/
bool AKeyModeData::getActive() {
	return active;
}

/*Active setter*/
void AKeyModeData::swapActive() {
	active = !active;
}

void AKeyModeData::setMajorAtrributes(bool activeness, EAllGameStates state, UAudioComponent* USong, TArray<FString> TNoteList) {
	this->gameState = state;
	this->song = USong;
	this->active = activeness;

	for (int a = 0; a < TNoteList.Num(); a++) {
		noteList.Add(TNoteList[a]);
	}
}

void AKeyModeData::BeginPlay() {
	Super::BeginPlay();
}

void AKeyModeData::Tick(float deltaTime) {
	Super::Tick(deltaTime);
}