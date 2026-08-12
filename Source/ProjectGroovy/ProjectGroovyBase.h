// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "RhythmGameMode.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CheatManager.h"
#include "Components/ProgressBar.h"
#include "RhythmPlayer.h"
#include "ProjectGroovyBase.generated.h"

#define WIDGET_AMOUNT 3

/**
 * 
 */



UENUM(BlueprintType)
enum class EAllGameStates: uint8 {
	start,
	sideAudience,
	sideGremlin,
	gameWon,
	gameOver
};


UCLASS()
class PROJECTGROOVY_API AProjectGroovyBase : public AGameStateBase
{
public:
	GENERATED_BODY()
		AProjectGroovyBase();
	UFUNCTION(BlueprintCallable, Category="Health")
		void changeHealth(float healthChange);

<<<<<<< Updated upstream
=======
		void setGameState(EAllGameStates state);

		bool isDollComplete();


>>>>>>> Stashed changes
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
		uint8 gameState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar")
		UProgressBar* audienceBar;
private:
	void handleDeath();
};
