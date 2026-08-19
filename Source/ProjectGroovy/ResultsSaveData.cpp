// Fill out your copyright notice in the Description page of Project Settings.


#include "ResultsSaveData.h"



ERanks calculateRank(int score, int maxScore) {

	if (score >= (maxScore * 0.97)) return ERanks::SPP;
	if (score >= (maxScore * 0.94)) return ERanks::SP;
	if (score >= (maxScore * 0.9))  return ERanks::S;
	if (score >= (maxScore * 0.7))  return ERanks::A;
	if (score >= (maxScore * 0.6))  return ERanks::B;
	if (score >= (maxScore * 0.5)) return ERanks::C;
	if (score >= (maxScore * 0.4)) return ERanks::D;
	
	return ERanks::E;
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

	dollComplete = theData->dollComplete;

	int audienceMax = gameMode->getMaxAudienceScore();
	int dollMax = gameMode->getMaxDollScore();


	audienceRank = calculateRank(audienceScore, audienceMax);

	// Only displays an actual rank for doll if it was finished
	if (dollComplete) {
		dollRank = calculateRank(dollScore, dollMax);
		// The overall takes the bonus you get upon completing doll into mind.
		int overallMax = audienceMax + (dollMax * 2);

		overallRank = calculateRank(score, overallMax);
	}
	else {
		dollRank = ERanks::NA;
		overallRank = ERanks::NA;
	}

	audienceSongTitle = gameMode->audienceSongTitle;
	dollSongTitle = gameMode->dollSongTitle;

	// Results in "Audience Song X Doll Song"
	FString temp = UKismetStringLibrary::Concat_StrStr(audienceSongTitle, TEXT(" X "));
	crossoverTitle = UKismetStringLibrary::Concat_StrStr(temp, dollSongTitle);

	UGameplayStatics::SaveGameToSlot(this, "results", 0);
}
