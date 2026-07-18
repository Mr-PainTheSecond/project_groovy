// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicNote.h"

// Sets default values
AMusicNote::AMusicNote()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	quarterBeat = 0;
	noteIndex = 0;
	active = true;
}

// Called when the game starts or when spawned
void AMusicNote::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMusicNote::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMusicNote::NoteScore_Implementation() {
	UKismetSystemLibrary::PrintString(GetWorld(), "We are in C++ :|");
}
