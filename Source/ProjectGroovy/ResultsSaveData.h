// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UObject/Object.h"
#include "ProjectGroovyBase.h"
#include "RhythmGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ResultsSaveData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGROOVY_API UResultsSaveData : public USaveGame
{
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Scores")
		int score;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Scores")
		int audienceScore;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Scores")
		int dollScore;
	// Highest streak on notes on audience side (Mistakes on Doll do not reset it).
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Streaks")
		int highestAudienceStreak;
	// Highest streak on notes on doll side (Mistakes on audience do not reset it).
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Streaks")
		int highestDollStreak;
	// Highest streak when treating both songs as one.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Streaks")
		int highestStreak;
	// Highest between the 3 above.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Streaks")
		int highestOverallStreak;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rank")
		FString audienceRank;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Rank")
		FString dollRank;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Doll")
		bool dollComplete;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song");
		FString audienceSongTitle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song");
		FString dollSongTitle;

public:
	UFUNCTION(BlueprintCallable, Category = "Scoring")
		void writeAndSave(AProjectGroovyBase* theData, ARhythmGameMode* gameMode);
};
