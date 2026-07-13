// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "KeyModeData.generated.h"

/**
 * 
 */
 /*A class which simply contains all components which vary
 between the two notepads*/
UCLASS()
class PROJECTGROOVY_API AKeyModeData: public AActor {
	GENERATED_BODY()
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song")
		bool isAudience;
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

	void setActive();

	bool getActive();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void setMajorAtrributes(bool activeness, bool BAudience, UAudioComponent* USong, TArray<FString> TNoteList);
};
