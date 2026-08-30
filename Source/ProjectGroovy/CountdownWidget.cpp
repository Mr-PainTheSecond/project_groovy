// Fill out your copyright notice in the Description page of Project Settings.


#include "CountdownWidget.h"

void UCountdownWidget::StartTimer() {
	startTime = clock();
	active = true;
	stage = 2;
}

int UCountdownWidget::UpdateStage() {
	if (!active) return -1;

	clock_t currentTime = clock();
	// Convert clock cycles into ms. before subtracting and comparing.
	if ((currentTime) - (startTime) > 150) {
		stage--;

		startTime = clock();

		if (stage == -1) {
			ARhythmGameMode* mode = (ARhythmGameMode*)UGameplayStatics::GetGameMode(GetWorld());

			mode->countdownEnd();

			active = false;
		}
	}

	return stage;
}
