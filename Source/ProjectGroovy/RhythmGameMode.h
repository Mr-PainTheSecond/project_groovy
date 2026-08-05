// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "KeyModeData.h"
#include "NotePad.h"
#include "ProjectGroovyBase.h"
#include "RuntimeAudioImporterLibrary.h"
#include "RuntimeAudioImporterTypes.h"
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio Management")
		URuntimeAudioImporterLibrary* audioImporter;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Audio Management")
		UAudioComponent* audioBuffer;
public:
	ARhythmGameMode();

	UAudioComponent* getCurrentSong();

	UFUNCTION(BlueprintCallable, Category = "Mode Select")
	AKeyModeData* getModeData();
	UFUNCTION(BlueprintCallable, Category = "Mode Select")
	void initializeModeData();
	UFUNCTION(BlueprintCallable, Category = "Audio Management")
	void createAudioImporter();

	UFUNCTION(BlueprintCallable, Category = "Flag Management")
		void swapActiveModes();
};
