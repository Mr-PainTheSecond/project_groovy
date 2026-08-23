// Fill out your copyright notice in the Description page of Project Settings.


#include "GroovyUtilities.h"

/*Returns a % b, but taking negative numbers into
account and keeping them at uniform distance in
the transition from positive to negative*/
int UGroovyUtilities::properMod(int a, int b) {
	if (a >= 0) return a % b;

	int absA = abs(a) % b;

	return (b - absA) % b;
}

bool UGroovyUtilities::IncludesKey(TArray<FKey> keys, FKey key) {
	FText pressedText = UKismetInputLibrary::Key_GetDisplayName(key);

	for (int a = 0; a < keys.Num(); a++) {
		// If true,we found match 
		if (MatchingKey(keys[a], key)) return true;
	}

	return false;
}

UAudioComponent* UGroovyUtilities::loadAndPlay(UWorld* world, USoundBase* sound, float noiseMult) {
	UAudioComponent* newAudio = UGameplayStatics::CreateSound2D(world, sound, noiseMult);
	
	newAudio->Play();

	return newAudio;
}

/*Determines whether two keys are the same by comparing
their display names*/
bool UGroovyUtilities::MatchingKey(FKey keyA, FKey keyB) {
	FText textA = UKismetInputLibrary::Key_GetDisplayName(keyA);
	FText textB = UKismetInputLibrary::Key_GetDisplayName(keyB);

	return textA.EqualTo(textB);
}

void UGroovyUtilities::free2DTArray(TArray<FString>** array, int size) {
	if (array == NULL) return;

	for (int a = 0; a < size; a++) {
		array[a]->Empty();
	}

	free(array);
}