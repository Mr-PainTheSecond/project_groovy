// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyModeData.h"

AKeyModeData::AKeyModeData() {
	//  We don't need the tick event
	PrimaryActorTick.bCanEverTick = false;
	// Placeholder values
	song = NULL;
	noteList = {};
	isAudience = false;
	active = true;

	// Actual starting values
	noteIndex = 0;
	health = 0.5f;
}

/*Active getter*/
bool AKeyModeData::getActive() {
	return active;
}

/*Active setter*/
void AKeyModeData::setActive() {
	active = true;
}

void AKeyModeData::setMajorAtrributes(bool activeness, bool BAudience, UAudioComponent* USong, TArray<FString> TNoteList) {
	this->isAudience = BAudience;
	this->song = USong;
	this->noteList = TNoteList;
	this->active = activeness;
}

void AKeyModeData::BeginPlay() {
	Super::BeginPlay();
}

void AKeyModeData::Tick(float deltaTime) {
	Super::Tick(deltaTime);
}