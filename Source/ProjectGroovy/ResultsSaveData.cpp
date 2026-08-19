// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultsSaveData.h"



FString calculateRank(int score, int maxScore) {


	if (score >= (maxScore * 0.97)) return TEXT("S++");
	if (score >= (maxScore * 0.95)) return TEXT("S+");
	if (score >= (maxScore * 0.9)) return TEXT("S");
	if (score >= (maxScore * 0.7)) return TEXT("A");
	if (score >= (maxScore * 0.6)) return TEXT("B");
	if (score >= (maxScore * 0.5)) return TEXT("C");
	if (score >= (maxScore * 0.4)) return TEXT("D");
	
	return TEXT("E");
}

void UResultsSaveData::writeAndSave(AProjectGroovyBase* theData, ARhythmGameMode* gameMode) {

	if (theData == NULL) {
		RequestEngineExit("Could not find the ProjectGroovyBase actor to save data from");
		return;
	}

	score = theData->score;
	audienceScore = theData->scoreByAudience;
	dollScore = theData->scoreByDoll;

	highestAudienceStreak = theData->highestAudienceStreak;
	highestDollStreak = theData->highestDollStreak;
	highestStreak = theData->highestStreak;

	highestOverallStreak = highestAudienceStreak;

	if (highestDollStreak > highestOverallStreak) {
		highestOverallStreak = highestDollStreak;
	}

	if (highestStreak > highestOverallStreak) {
		highestOverallStreak = highestStreak;
	}


	audienceRank = calculateRank(audienceScore, gameMode->getMaxAudienceScore());

	dollComplete = theData->dollComplete;

	audienceSongTitle = gameMode->audienceSongTitle;
	dollSongTitle = gameMode->dollSongTitle;

	// Only displays an actual rank for doll if it was finished
	if (dollComplete) {
		dollRank = calculateRank(dollScore, gameMode->getMaxDollScore());
	}
	else {
		dollRank = TEXT("N/A");
	}

	UGameplayStatics::SaveGameToSlot(this, "results", 0);
}
