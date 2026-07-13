// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "NotePad.h"
#include "KeyModeData.h"
#include "RhythmGameMode.generated.h"

/**
 * 
 */


UCLASS()
class PROJECTGROOVY_API ARhythmGameMode : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song")
		UAudioComponent* playingSong;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modes")
		AKeyModeData* audienceMode;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Modes")
		AKeyModeData* dollMode;

		bool initialized;
public:
	ARhythmGameMode();

	UAudioComponent* getCurrentSong();

	UFUNCTION(BlueprintCallable, Category = "Mode Select")
		AKeyModeData* getModeData();
	UFUNCTION(BlueprintCallable, Category = "Mode Select")
		void initializeModeData();

};
