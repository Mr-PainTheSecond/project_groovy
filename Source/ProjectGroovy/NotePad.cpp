// Fill out your copyright notice in the Description page of Project Settings.


#include "NotePad.h"

// Sets default values
ANotePad::ANotePad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentTime = -1.0f;

}

// Called when the game starts or when spawned
void ANotePad::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANotePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (currentTime != -1.0f) {
		currentTime += DeltaTime;
	}

}

void ANotePad::testTime() {
	if (currentTime != -1.0f) {
		float timeDifference = targetTime - currentTime;
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Expected Time: %f"), targetTime));
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Expected Time: %f"), currentTime));
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Time Difference: %f"), timeDifference));
	}
	
	currentTime = 0.0f;
}

void ANotePad::setTargetTime(int BPM) {
	// Given current BPM, calculates time in seconds. it is expected for one beat to take
	targetTime = (1.0f / (float)(BPM)) * 60.0f;
}

