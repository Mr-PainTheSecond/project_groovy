// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Kismet/KismetInputLibrary.h"
#include "GroovyUtilities.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGROOVY_API UGroovyUtilities : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Math")
		static int properMod(int a, int b);
	UFUNCTION(BlueprintCallable, Category = "Keyboard")
		static bool IncludesKey(TArray<FKey> keys, FKey key);
	UFUNCTION(BlueprintCallable, Category = "Keyboard")
		static bool MatchingKey(FKey keyA, FKey keyB);
public:
	static void free2DTArray(TArray<FString>** array, int size);

	static UAudioComponent* loadAndPlay(UWorld* world, USoundBase* sound, float noiseMult = 1.0f);
};
