// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UObject/Object.h"
#include "Kismet/GameplayStatics.h"
#include "Teleporter.h"
#include "Components/AudioComponent.h"
#include "MusicNote.h"
#include "GroovyUtilities.h"
#include "KeyModeData.generated.h"



UENUM(BlueprintType)
enum class EAllGameStates : uint8 {
	start,
	sideAudience,
	sideDoll,
	gameWon,
	gameOver
};

/**
 * 
 */
 /*A class which simply contains all components which vary
 between the two notepads*/
UCLASS()
class PROJECTGROOVY_API AKeyModeData: public AActor {
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mode")
		EAllGameStates gameState;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Progress")
		int totalQuarterBeats;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Progress")
		int currentQuarterBeats;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song")
		UAudioComponent* song;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anchor")
		float timeStamp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song")
		int noteIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song")
		int BPM;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
		float health;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song")
		TArray<FString> noteList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Notes")
		TArray<AMusicNote*> noteObjects;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Notes")
		TArray<AMusicNote*> beingPlayed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anchor")
		ATeleporter* anchor;
public:
	AKeyModeData();

	bool active;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Flags")
		bool initialized;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void swapLocation();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void swapActive();



	UFUNCTION(BlueprintCallable, Category = "Scoring")
		void ScoreNotes(FKey input);

	bool getActive();

	void PauseAudio();
	UFUNCTION(BlueprintCallable, Category = "Audio Management", DisplayName = "Unpause Audio")
		void UnPauseAudio();

	UAudioComponent* getSong();


	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void setMajorAtrributes(bool activeness, EAllGameStates state, UAudioComponent* USong, TArray<FString> TNoteList, TArray<ATeleporter*> TTele);
private:
	TArray<FKey> validKeys;
};
