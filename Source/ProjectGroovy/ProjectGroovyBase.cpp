// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGroovyBase.h"



/*Ensures all the properties have some initial value*/
AProjectGroovyBase::AProjectGroovyBase() {
	gameState = (uint8)(EAllGameStates::start);
	health = 0.5f;
	audienceBar = NULL;
}



void AProjectGroovyBase::changeHealth(float healthChange) {
	health += healthChange;

	// Capped at one
	if (health > 1.0f) {
		health = 1.0f;
	}

	if (health < 0.0f) {
		health = 0.0f;
		handleDeath();
	}

	if (audienceBar == NULL) RequestEngineExit("Audience Bar reference is still null");

	//// Updates the health in the user widget
	audienceBar->SetPercent(health);

}

void AProjectGroovyBase::handleDeath() {
	// Upon Death, stop the song!!!
	ARhythmGameMode* gameMode = (ARhythmGameMode*)UGameplayStatics::GetGameMode(GetWorld());

	UAudioComponent* currentSong = gameMode->getCurrentSong();

	currentSong->Stop();

<<<<<<< Updated upstream
	gameState = (uint8)(EAllGameStates::gameOver);
=======
	gameState = (EAllGameStates::gameOver);
}

void AProjectGroovyBase::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	ARhythmPlayer* player = (ARhythmPlayer*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// Don't drain health if paused
	if (player->paused) return;

	// Doll's health slowly drains while on audience
	if (gameState == EAllGameStates::sideAudience && !dollComplete) {
		dollHealth -= (1.0f / 40.0f) * DeltaSeconds;

		if (dollHealth < 0.0f) {
			dollHealth = 0.0f;
			handleDeath();
		}

		dollBar->SetPercent(dollHealth);
	}
	// Audience health drains quickers while on doll
	else if (gameState == EAllGameStates::sideDoll && !dollComplete) {
		audienceHealth -= (1.0f / 15.0f) * DeltaSeconds;

		if (audienceHealth < 0.0f) {
			audienceHealth = 0.0f;
			handleDeath();
		}

		audienceBar->SetPercent(audienceHealth);
	}
}

void AProjectGroovyBase::setGameState(EAllGameStates state) {
	gameState = state;
}

bool AProjectGroovyBase::isDollComplete() {
	return dollComplete;
>>>>>>> Stashed changes
}