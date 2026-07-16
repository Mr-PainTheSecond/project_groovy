// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "KeyModeData.generated.h"



UENUM(BlueprintType)
enum class EAllGameStates : uint8 {
	start,
	sideAudience,
	sideGremlin,
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song")
		UAudioComponent* song;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song")
		int noteIndex;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
		float health;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song")
		TArray<FString> noteList;
	bool active;
public:
	AKeyModeData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void swapActive();

	bool getActive();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void setMajorAtrributes(bool activeness, EAllGameStates state, UAudioComponent* USong, TArray<FString> TNoteList);
};
