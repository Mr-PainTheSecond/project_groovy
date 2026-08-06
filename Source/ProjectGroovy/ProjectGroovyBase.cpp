// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGroovyBase.h"



/*Ensures all the properties have some initial value*/
AProjectGroovyBase::AProjectGroovyBase() {
	gameState = (EAllGameStates::start);
	audienceHealth = 0.5f;
	audienceBar = NULL;

	dollHealth = 1.0f;
	dollBar = NULL;
}



void AProjectGroovyBase::changeHealth(float healthChange, EAllGameStates state) {
	float health;
	UProgressBar* bar;

	if (EAllGameStates::sideAudience == state) {
		health = audienceHealth;
		bar = audienceBar;
	}
	else if (EAllGameStates::sideDoll == state) {
		health = dollHealth;
		bar = dollBar;
	}
	else {
		return;
	}


	health += healthChange;

	// Capped at one
	if (health > 1.0f) {
		health = 1.0f;
	}

	if (health < 0.0f) {
		health = 0.0f;
		handleDeath();
	}

	if (bar == NULL) RequestEngineExit("Audience Bar reference is still null");

	// Updates the health in the user widget
	bar->SetPercent(health);


	if (EAllGameStates::sideAudience == state) {
		audienceHealth = health;
	}
	else {
		dollHealth = health;
	}

}

void AProjectGroovyBase::handleDeath() {
	// Upon Death, stop the song!!!
	/*ARhythmGameMode* gameMode = (ARhythmGameMode*)UGameplayStatics::GetGameMode(GetWorld());

	UAudioComponent* currentSong = gameMode->getCurrentSong();

	currentSong->Stop();*/

	gameState = (EAllGameStates::gameOver);
}

void AProjectGroovyBase::setGameState(EAllGameStates state) {
	gameState = state;
}