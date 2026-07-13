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

	gameState = (uint8)(EAllGameStates::gameOver);
}