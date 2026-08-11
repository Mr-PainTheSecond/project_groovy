// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "KeyModeData.h"
#include "Components/AudioComponent.h"
#include "GameFramework/CheatManager.h"
#include "Components/ProgressBar.h"
#include "ProjectGroovyBase.generated.h"

#define WIDGET_AMOUNT 3

/**
 * 
 */



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
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
		EAllGameStates gameState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float audienceHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float dollHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar")
		UProgressBar* audienceBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health Bar")
		UProgressBar* dollBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
		int scoreByDoll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Completion")
		bool dollComplete;
private:
	void handleDeath();

	virtual void Tick(float DeltaSeconds) override;
};
