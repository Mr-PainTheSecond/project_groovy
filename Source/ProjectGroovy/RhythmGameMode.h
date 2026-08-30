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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song");
		FString audienceSongTitle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song");
		FString dollSongTitle;

public:
	ARhythmGameMode();

	UAudioComponent* getCurrentSong();

	UFUNCTION(BlueprintCallable, Category = "Mode Select")
		AKeyModeData* getModeData();
	UFUNCTION(BlueprintCallable, Category = "Mode Select")
		void initializeModeData();
	UFUNCTION(BlueprintCallable, Category = "Audio Management")
		void createAudioImporter();
	/*Checks whether player can swap modes/teleport. Can generally
	happen until the player goes into audience mode after completing the
	doll track*/
	UFUNCTION(BlueprintCallable, Category = "Teleporting")
		bool canTeleport();

	UFUNCTION(BlueprintCallable, Category = "Flag Management")
		void swapActiveModes(bool manualSwap);

		void swapAudioTrack(AKeyModeData* stopping, AKeyModeData* starting);

	UFUNCTION(BlueprintCallable, Category = "Pausing")
		void PauseGameEvent();
		
		int getMaxAudienceScore();

		int getMaxDollScore();

		void countdownEnd();
};
