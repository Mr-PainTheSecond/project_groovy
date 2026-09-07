// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "NotePad.generated.h"

UCLASS()
class PROJECTGROOVY_API ANotePad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANotePad();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float targetTime;

	float currentTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "BPM Testing")
		void setTargetTime(int BPM);
	UFUNCTION(BlueprintCallable, Category = "BPM Testing")
		void testTime();
};
