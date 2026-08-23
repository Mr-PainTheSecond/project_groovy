// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "KeyModeData.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CheatManager.h"
#include "Components/ProgressBar.h"
#include "GroovyUtilities.h"
#include "RhythmPlayer.h"
#include "ProjectGroovyBase.generated.h"

#define WIDGET_AMOUNT 3

/**
 * 
 */

UENUM(BlueprintType)
enum class EDangerLevels : uint8 {
	noDanger,
	singleDanger,
	doubleDanger
};


UCLASS()
class PROJECTGROOVY_API AProjectGroovyBase : public AGameStateBase
{
public:
	GENERATED_BODY()
		AProjectGroovyBase();
	UFUNCTION(BlueprintCallable, Category="Health")
		void changeHealth(float healthChange, EAllGameStates state);

		void setGameState(EAllGameStates state);


		bool isDollComplete();
    
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
		EAllGameStates gameState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float audienceHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float dollHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Danger")
		EDangerLevels dangerLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Danger")
		USoundBase* wrongAudienceDanger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Danger")
		USoundBase* drainAudienceDanger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Danger")
		USoundBase* wrongDollDanger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Danger")
		USoundBase* drainDollDanger;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar")
		UProgressBar* audienceBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar")
		UProgressBar* dollBar;
	
	// All Data below will be saved upon song completion
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
		FString rank;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
		int scoreByAudience;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
		int scoreByDoll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
		int score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
		int highestAudienceStreak;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
		int highestDollStreak;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Performance")
		int highestStreak;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Completion")
		bool dollComplete;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SFX")
		UAudioComponent* playingSFX;
private:
	void handleDeath();

	void updateDangerLevel();

	void handleDangerSFX();

	virtual void Tick(float DeltaSeconds) override;
};
