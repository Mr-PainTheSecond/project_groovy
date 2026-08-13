// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UObject/Object.h"
#include "Kismet/GameplayStatics.h"
#include "Teleporter.h"
#include "Components/AudioComponent.h"
#include "MusicNote.h"
#include "GroovyUtilities.h"
#include "KeyModeData.generated.h"



UENUM(BlueprintType)
enum class EAllGameStates : uint8 {
	start,
	sideAudience,
	sideDoll,
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
	// Game state associated with this mode
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Mode")
		EAllGameStates gameState;
	// Length of the song, based on quarter beats
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Progress")
		int totalQuarterBeats;
	// Progress on the song, based on Quarter Beats
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Progress")
		int currentQuarterBeats;
	// The audio object representing the song
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song")
		UAudioComponent* song;
	// The song's progress, in terms of index (one quarter beat may be taken by 1-4 entries).
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song")
		int noteIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song")
		int BPM;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Health")
		float health;
	// How long health would last, in seconds, if player is at full health.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Timer")
		float maxTimer;
	// Full song data.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Song")
		TArray<FString> noteList;
	// The note actors, ordered by how close they are to the player
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Notes")
		TArray<AMusicNote*> noteObjects;
	// For quarter notes and above, notes being held but haven't been released
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Notes")
		TArray<AMusicNote*> beingPlayed;
	// Where the player teleports to upon swapping modes.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Anchor")
		ATeleporter* anchor;
public:
	AKeyModeData();

	bool active;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Flags")
		bool initialized;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void swapLocation();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void swapActive();



	/*Using key pressed by player, scores the closest active note.
	If 2 notes are equally close, and one of them is right, it will
	score the right one.
	If the note is right, assess how good the note is.*/
	UFUNCTION(BlueprintCallable, Category = "Scoring")
		void ScoreNotes(FKey input);

	UFUNCTION(BlueprintCallable, Category = "Removal")
		void RemoveNote(AMusicNote* note);

	bool getActive();

	UFUNCTION(BlueprintCallable, Category = "Audio Management")
		void PauseAudio();
	UFUNCTION(BlueprintCallable, Category = "Audio Management", DisplayName = "Unpause Audio")
		void UnPauseAudio();

	UAudioComponent* getSong();


	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void setMajorAtrributes(bool activeness, EAllGameStates state, UAudioComponent* USong, TArray<FString> TNoteList, TArray<ATeleporter*> TTele);
private:
	TArray<FKey> validKeys;
};
