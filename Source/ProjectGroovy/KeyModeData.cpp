// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyModeData.h"

AKeyModeData::AKeyModeData() {
	//  We don't need the tick event
	PrimaryActorTick.bCanEverTick = false;
	// Placeholder values
	song = NULL;
	noteList = {};
	noteObjects = {};
	beingPlayed = {};
	gameState = (EAllGameStates::start);
	active = true;

	// Actual starting values
	noteIndex = 0;
	totalQuarterBeats = 0;
	health = 0.5f;

	// Our list of what the user can press
	validKeys.Add(FKey("D"));
	validKeys.Add(FKey("F"));
	validKeys.Add(FKey("G"));
	validKeys.Add(FKey("H"));
}

/*Active getter*/
bool AKeyModeData::getActive() {
	return active;
}

/*Active setter*/
void AKeyModeData::swapActive() {
	active = !active;
}



void AKeyModeData::ScoreNotes(FKey input) {
	// If it isn't part of the keys, don't bother
	if (!UGroovyUtilities::IncludesKey(validKeys, input)) return;

	int theQuarterBeat = -1;

	TArray<AMusicNote*> potentiallyWrong;
	bool validNoteFound = false;
	for (int a = 0; a < noteObjects.Num(); a++) {
		AMusicNote* currentNote = noteObjects[a];

		// If true: Officially, the player fucked up
		if (theQuarterBeat != -1 && currentNote->quarterBeat != theQuarterBeat) {
			break;
		}

		// Fixes a problem with some of the earlier notes
		currentNote->noteKey = validKeys[currentNote->noteIndex];

		// We found a valid key, we can score it as so
		if (UGroovyUtilities::MatchingKey(input, currentNote->noteKey)) {
			validNoteFound = true;

			currentNote->NoteScore();

			noteObjects.Remove(currentNote);
			// For notes that need to be held. Blueprint will discard that don't need to be held
			beingPlayed.Add(currentNote);
			break;
		}
		//
		else {
			// If here, 2 scenarios: Player hit wrong note, or the input is for another valid note
			if (theQuarterBeat == -1) {
				theQuarterBeat = currentNote->quarterBeat;
			}

			potentiallyWrong.Add(currentNote);

		}
	}

	// If no good note, then we will "score" them as wrong, and remove them.
	if (!validNoteFound) {
		for (int a = 0; a < potentiallyWrong.Num(); a++) {
			potentiallyWrong[a]->NoteScore();

			noteObjects.Remove(potentiallyWrong[a]);
		}
	}
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