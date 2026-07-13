// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmGameMode.h"

/*Construct of the game mode*/
ARhythmGameMode::ARhythmGameMode() {

	// Avoiding reading garbage data :)
	playingSong = NULL;
	audienceMode = NULL;
	dollMode = NULL;
	initialized = false;

}

/*Spawns both instances of the game modes. Isn't
done in the constructor can GetWorld can't be called
in the constructor*/
void ARhythmGameMode::initializeModeData() {
	// Everything is already good to go
	if (initialized) return;
	UWorld* world = GetWorld();
	if (world == NULL) RequestEngineExit("World doesn't exist");
	// Spawn the two mode data actors
	this->audienceMode = (AKeyModeData*)(world->SpawnActor(AKeyModeData::StaticClass()));
	this->dollMode = (AKeyModeData*)(world->SpawnActor(AKeyModeData::StaticClass()));
	if (audienceMode == NULL || dollMode == NULL) RequestEngineExit("Could not make the new mode references");

	initialized = true;
}

/*Getter of the actual song. This function isn't
necessary for Blueprint, so only accessible for
C++*/
UAudioComponent* ARhythmGameMode::getCurrentSong() {
	
	return playingSong;
}

/*Gets the currently active mode data back to
the Blueprint Mode. Called for whenver a new
Notepad is made.*/
AKeyModeData* ARhythmGameMode::getModeData() {
	if (audienceMode->getActive()) {
		return audienceMode;
	}
	else if (dollMode->getActive()) {
		return dollMode;
	}
	else {
		return NULL;
	}
}