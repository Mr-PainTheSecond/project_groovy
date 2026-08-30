// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "RhythmGameMode.h"
#include <time.h>
#include "CountdownWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGROOVY_API UCountdownWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	bool active;

	clock_t startTime;

	int stage;

public:
	UFUNCTION(BlueprintCallable, Category = "Timer")
		void StartTimer();

	UFUNCTION(BlueprintCallable, Category = "Timer")
		int UpdateStage();
};
