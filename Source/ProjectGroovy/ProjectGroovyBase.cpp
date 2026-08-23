// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectGroovyBase.h"



/*Ensures all the properties have some initial value*/
AProjectGroovyBase::AProjectGroovyBase() {
	PrimaryActorTick.bCanEverTick = true;

	gameState = (EAllGameStates::start);
	score = 0;
	rank = TEXT("E");
	dangerLevel = EDangerLevels::noDanger;

	audienceHealth = 0.5f;
	audienceBar = NULL;

	dollHealth = 1.0f;
	dollBar = NULL;
	scoreByDoll = 0;
	scoreByAudience = 0;
	dollComplete = false;

	wrongAudienceDanger = NULL;
	drainAudienceDanger = NULL;
	wrongDollDanger = NULL;
	drainDollDanger = NULL;

	playingSFX = NULL;
}

void AProjectGroovyBase::handleDangerSFX() {
	static bool audienceDanger = false;
	static bool dollDanger = false;


	if (audienceDanger && audienceHealth >= 0.25f) audienceDanger = false;
	if (dollDanger && dollHealth >= 0.25f) dollDanger = false;

	// SFX have already been handled
	if (audienceDanger && dollDanger) return;

	// Player's danger has recently increased
	if (!audienceDanger && audienceHealth < 0.25f) {
		audienceDanger = true;

		// If SFX already playing, don't play at all
		if (playingSFX != NULL) return;

		// It was due to making a mistake in audience
		if (gameState == EAllGameStates::sideAudience && wrongAudienceDanger != NULL) {
			playingSFX = UGroovyUtilities::loadAndPlay(GetWorld(), wrongAudienceDanger);
		}
		else if (drainAudienceDanger != NULL) {
			playingSFX = UGroovyUtilities::loadAndPlay(GetWorld(), drainAudienceDanger);
		}
	}
	else if (!dollDanger && dollHealth < 0.25f) {
		dollDanger = true;

		if (playingSFX != NULL) return;

		if (gameState == EAllGameStates::sideDoll && wrongDollDanger != NULL) {
			playingSFX = UGroovyUtilities::loadAndPlay(GetWorld(), wrongDollDanger, 3.0f);
		}
		else if (drainDollDanger != NULL) {
			playingSFX = UGroovyUtilities::loadAndPlay(GetWorld(), drainDollDanger);
		}
	}


}

void AProjectGroovyBase::updateDangerLevel() {
	// If doll is already finished, never counts towards danger level
	if (audienceHealth < 0.25f && (dollHealth < 0.25f && !dollComplete)) {
		dangerLevel = EDangerLevels::doubleDanger;
	}
	// One of them are below 1/4, one danger
	else if (audienceHealth < 0.25f || (dollHealth < 0.25f && !dollComplete)) {
		dangerLevel = EDangerLevels::singleDanger;
	}
	else {
		dangerLevel = EDangerLevels::noDanger;
	}

	handleDangerSFX();
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


	updateDangerLevel();
}

void AProjectGroovyBase::handleDeath() {
	// Upon Death, stop the song!!!
	/*ARhythmGameMode* gameMode = (ARhythmGameMode*)UGameplayStatics::GetGameMode(GetWorld());

	UAudioComponent* currentSong = gameMode->getCurrentSong();

	currentSong->Stop();*/

	gameState = (EAllGameStates::gameOver);
}


void AProjectGroovyBase::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);

	ARhythmPlayer* player = (ARhythmPlayer*)UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// The SFX finished plaing, destroy it.
	if (playingSFX != NULL && !(playingSFX->IsPlaying())) {
		playingSFX->DestroyComponent();
		playingSFX = NULL;
	}

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

	updateDangerLevel();
}

void AProjectGroovyBase::setGameState(EAllGameStates state) {
	gameState = state;
}

bool AProjectGroovyBase::isDollComplete() {
	return dollComplete;
}