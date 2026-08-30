// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmGameMode.h"

/*Construct of the game mode*/
ARhythmGameMode::ARhythmGameMode() {

	// Avoiding reading garbage data :)
	playingSong = NULL;
	audienceMode = NULL;
	dollMode = NULL;
	audioImporter = NULL;
	initialized = false;


}

void ARhythmGameMode::createAudioImporter() {
	
	if (audioImporter != NULL) return;

	audioImporter = URuntimeAudioImporterLibrary::CreateRuntimeAudioImporter();

	UKismetSystemLibrary::PrintString(GetWorld(), "We are in C++");


	audioImporter->OnProgressNative.AddWeakLambda(this, [this](int32 Percentage)
		{
			UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Import Progress: %d%%"), Percentage));
	});


	// Trigger this whenever we import a song
	audioImporter->OnResultNative.AddWeakLambda(this, [this](URuntimeAudioImporterLibrary* Importer, UImportedSoundWave* ImportedSoundWave, ERuntimeImportStatus Status) {
		if (Status == ERuntimeImportStatus::SuccessfulImport) {
			UKismetSystemLibrary::PrintString(GetWorld(), "Imported Song!");
			UGameplayStatics::PlaySound2D(GetWorld(), ImportedSoundWave);
		}
		else {
			UKismetSystemLibrary::PrintString(GetWorld(), "Failed to import song");
		}
	});

	audioImporter->ImportAudioFromFile(TEXT("C:/Users/Owner/Music/ProjectGroovy/ProjectGroovy/Content/Songs/MU_Billie.mp3"), ERuntimeAudioFormat::Mp3);
	UKismetSystemLibrary::PrintString(GetWorld(), "File is imported");
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



bool ARhythmGameMode::canTeleport() {
	if (audienceMode == NULL) return false;

	AProjectGroovyBase* theBase = (AProjectGroovyBase*)UGameplayStatics::GetActorOfClass(GetWorld(), AProjectGroovyBase::StaticClass());

	// Do not swap if the player is in countdown
	if (theBase->gameState == EAllGameStates::countdown) return false;

	// Only disallows swaps if player is in audience and already
	return !(audienceMode->active && theBase->isDollComplete());
}

void ARhythmGameMode::countdownEnd() {
	AProjectGroovyBase* theBase = (AProjectGroovyBase*)UGameplayStatics::GetActorOfClass(GetWorld(), AProjectGroovyBase::StaticClass());

	if (audienceMode->active) {
		theBase->setGameState(EAllGameStates::sideAudience);
		audienceMode->UnPauseAudio();
	}
	else {
		theBase->setGameState(EAllGameStates::sideDoll);
		dollMode->UnPauseAudio();
	}


}

void ARhythmGameMode::swapActiveModes(bool manualSwap) {
	if (audienceMode == NULL || dollMode == NULL) RequestEngineExit("One of the modes isn't initialized");

	AProjectGroovyBase* theBase = (AProjectGroovyBase*)UGameplayStatics::GetActorOfClass(GetWorld(), AProjectGroovyBase::StaticClass());

	// Doll is complete, ignore swap.
	if (!canTeleport()) return;

	audienceMode->swapActive();
	dollMode->swapActive();

	// If modes aren't active, we don't change the game state
	if (!(audienceMode->initialized) || !(dollMode->initialized)) {
		return;
	}


	if (audienceMode->active) {
		dollMode->PauseAudio();
		theBase->setGameState(EAllGameStates::sideAudience);
	}
	else {
		audienceMode->PauseAudio();
		theBase->setGameState(EAllGameStates::sideDoll);
	}


	if (manualSwap) {
		theBase->setGameState(EAllGameStates::countdown);
	}

}

void ARhythmGameMode::swapAudioTrack(AKeyModeData* stopping, AKeyModeData* starting) {
	stopping->PauseAudio();

	starting->UnPauseAudio();

	playingSong = starting->getSong();

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

void ARhythmGameMode::PauseGameEvent() {
	AKeyModeData* mode = getModeData();
	ARhythmPlayer* player = (ARhythmPlayer*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (player->paused) {
		mode->PauseAudio();
	}
	else {
		mode->UnPauseAudio();
	}
}

int ARhythmGameMode::getMaxAudienceScore() {
	return audienceMode->highestPossibleScore;
}

int ARhythmGameMode::getMaxDollScore() {
	return dollMode->highestPossibleScore;
}