// Fill out your copyright notice in the Description page of Project Settings.


#include "KeyModeData.h"

AKeyModeData::AKeyModeData() {
	//  We don't need the tick event
	PrimaryActorTick.bCanEverTick = false;
	// Placeholder values
	song = NULL;
	BPM = 0;
	noteList = {};
	noteObjects = {};
	beingPlayed = {};
	maxTimer = 0.0f;
	active = true;

	// Actual starting values
	noteIndex = 0;
	totalQuarterBeats = 0;
	gameState = (EAllGameStates::start);
	health = 0.5f;

	// Our list of what the user can press
	validKeys.Add(FKey("D"));
	validKeys.Add(FKey("F"));
	validKeys.Add(FKey("G"));
	validKeys.Add(FKey("H"));

	// Once everything is properly set, can become true
	initialized = false;
}

/*Active getter*/
bool AKeyModeData::getActive() {
	return active;
}

/*Active setter*/
void AKeyModeData::swapActive() {
	active = !active;

	if (active) {
		swapLocation();
	}
}

void AKeyModeData::PauseAudio() {
	if (song == NULL) return;

	song->SetPaused(true);
}

void AKeyModeData::UnPauseAudio() {
	if (song == NULL) return;

	EAudioComponentPlayState playState = song->GetPlayState();


	// If called and song hasn't started, we need to wait until it does start
	if (!(song->IsPlaying())) {
		return;
	}
	else {
		UKismetSystemLibrary::PrintString(GetWorld(), "Unpaused Audio");
		song->SetPaused(false);
	}
}

UAudioComponent* AKeyModeData::getSong() {
	return song;
}

void AKeyModeData::swapLocation() {
	// Downcasted to Actor for methods
	AActor* player = (AActor*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FVector anchorLcoation = anchor->GetActorLocation();

	player->SetActorLocation(anchorLcoation);
}

void AKeyModeData::RemoveNote(AMusicNote* note) {
	noteObjects.Remove(note);
}


void AKeyModeData::ScoreNotes(FKey input) {
	// If it isn't part of the keys, don't bother
	if (!UGroovyUtilities::IncludesKey(validKeys, input)) return;

	UKismetSystemLibrary::PrintString(GetWorld(), "Is a valid key");

	int theQuarterBeat = -1;

	TArray<AMusicNote*> potentiallyWrong = {};
	bool validNoteFound = false;
	for (int a = 0; a < noteObjects.Num(); a++) {
		AMusicNote* currentNote = noteObjects[a];

		if (!(currentNote->active)) {
			continue;
		}

		UKismetSystemLibrary::PrintString(GetWorld(), "Found an active key");

		// If true: Officially, the player fucked up
		if (theQuarterBeat != -1 && currentNote->quarterBeat != theQuarterBeat) {
			break;
		}

		// Fixes a problem with some of the earlier notes
		currentNote->noteKey = validKeys[currentNote->noteIndex];

		// We found a valid key, we can score it as so
		if (UGroovyUtilities::MatchingKey(input, currentNote->noteKey)) {

			UKismetSystemLibrary::PrintString(GetWorld(), "Found a good scoring note");

			currentNote->NoteScore();

			// If scoring didn't deactive it, then it didn't score, so don't remove it.
			if (!(currentNote->active)) {
				validNoteFound = true;
				noteObjects.Remove(currentNote);
				// For notes that need to be held. Blueprint will discard that don't need to be held
				beingPlayed.Add(currentNote);
			}
 
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
		UKismetSystemLibrary::PrintString(GetWorld(), "No valid note was found");

		for (int a = 0; a < potentiallyWrong.Num(); a++) {
			potentiallyWrong[a]->NoteScore();

			if (!(potentiallyWrong[a]->active)) {
				noteObjects.Remove(potentiallyWrong[a]);
			}
		}
	}
}

void AKeyModeData::setMajorAtrributes(bool activeness, EAllGameStates state, UAudioComponent* USong, TArray<FString> TNoteList, TArray<ATeleporter*> TTele) {
	this->gameState = state;
	this->song = USong;
	this->active = activeness;

	for (int a = 0; a < TNoteList.Num(); a++) {
		noteList.Add(TNoteList[a]);
	}

	if (state == EAllGameStates::sideAudience) {
		maxTimer = 15.0f;
	}
	else {
		maxTimer = 45.0f;
	}

	// Decides where the player will teleport upon swapping
	if (gameState == EAllGameStates::sideAudience) {
		if (TTele[0]->isAudience) {
			anchor = TTele[0];
		}
		else {
			anchor = TTele[1];
		}
	}
	else {
		if (TTele[0]->isAudience) {
			anchor = TTele[1];
		}
		else {
			anchor = TTele[0];
		}
	}

}

void AKeyModeData::BeginPlay() {
	Super::BeginPlay();
}

void AKeyModeData::Tick(float deltaTime) {
	Super::Tick(deltaTime);
}