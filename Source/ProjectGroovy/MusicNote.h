// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "MusicNote.generated.h"

UCLASS()
class PROJECTGROOVY_API AMusicNote : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMusicNote();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadWrite, Category = "Progress")
		int quarterBeat;
	UPROPERTY(BlueprintReadWrite, Category = "Note Data")
		int noteIndex;
	UPROPERTY(BlueprintReadWrite, Category = "Ending")
		bool lastDoll;
	UPROPERTY(BlueprintReadWrite, Category = "Note Data")
		bool active;
	UPROPERTY(BlueprintReadWrite, Category = "Keyboard")
		FKey noteKey;
		

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Scoring")
		// To be overriden by note blueprint
		void NoteScore();

};
