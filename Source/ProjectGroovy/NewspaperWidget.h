// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/MultiLineEditableTextBox.h"
#include "GroovyUtilities.h"
#include "NewspaperWidget.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EBodyText : uint8 {
	audiencePerformance,
	resultsTransition,
	dollPerformance
};

UENUM(BlueprintType)
enum class ERanks : uint8 {
	E,
	D,
	C,
	B,
	A,
	S,
	SP UMETA(DisplayName = "S+"),
	SPP UMETA(DisplayName = "S++"),
	NA UMETA(DisplayName = "N/A")
};

#ifndef NEWSPAPER_WIDGET_H_
#define NEWSPAPER_WIDGET_H_

#define BODY_COUNT 3
#define RANK_COUNT 9

const FString victoryMessages[BODY_COUNT][RANK_COUNT]{
	// Comments on performance (audience)
	{TEXT("After years of fame, age has caught up to our local musician. Tonight's performance of our legendary musician was a sign that they should have retired while the iron was hot. They have been invited to the Great Red Carpet, which really speaks to how despite everything, they were once one of the greats."),
	TEXT("After years of fame, age has caught up to our local musician. Tonight's performance of our legendary musician was a sign that they should have retired while the iron was hot. They have been invited to the Great Red Carpet, which really speaks to how despite everything, they were once one of the greats."),
	TEXT("The new local musician's first concert was, to be sincere, very mediocre. But it was one of the best I have ever seen from a newbie. They have been invited to the Great Red Carpet, so that tells me that I am not the only one who sees potential in them."),
	TEXT("The Legendary local musican has delivered yet another concert from the heavens. But, this was definetely their weakest outing. But, even their worst is still good, which just speaks of their raw skill. They have been invited to the Great Red Carpet, which I am pretty out of all concerts it was for this one."),
	TEXT("Local musician has begun their international tour right in their hometown, and they have stepped up their game! Their skill and the production overall have gone way up, it was great! They have been invited into the Great Read Carpet, so I am proud to say our hometown musician has made into the big leagues."),
	TEXT("The performance tonight tells me one thing: Our local musician is winning a Grammy! I had high expectations, but I was blown away by how insane tonight's perforamcne was. They were invited into the Great Red Carpet, but we all know that their big night is in February."),
	TEXT("I am officially now dating our local musician! After wathcing their performance tonight, I was so swept away by the beautiful notes that graced my ears that I had to ask for a date, and they said yes! They were inivted into the Great Red Carpet, so I have started to look for something good to wear when I attend with them."),
	TEXT("Jesus Christ has returned. Tonight's performance for our \"local musician\" was so divine, I realized it could have not come from any mere mortal, but from the Son of God. They were invited to the Great Red Carpet, but soon the world will knows: Jesus Christ has returned to play sick guitar riffs!"),
	TEXT("Somehow, the local musician did not finish a song without getting fired. Police suspect bad programming or game modding as possible suspects. Your choices don't matter, so local musician still goes to the Great Red Carpet.")},
	// Transition list
	{"Hello"},
	// Doll Comments
	{TEXT("\"The performance was terrible. So much wrong, So Incompentent. I want to take their soul, and put it in the darkest depths of hell. But they fuffilled their pact. They will live. They may not be so lucky next time. Analysis:\""),
	TEXT("\"El número del concierto estaba un poco mal. He estado criticando música desde el Siglo XVI, y no es la peor cosa que ha escuhado, ni cerca, pero yo reconozco un mal número cuando lo veo. Pero voy a decir esto: Nunca me dio ganas de agregar al sufrimiento de esto mundo. Y eso requiere almenos un nivel de competencia. Este mi análisis oficial que publique ha este periodico: \""),
	TEXT("\"Pretty Mid tbh -_-\""),
	TEXT("\"Hey guys! It's me, [REDACTED]! And welcome to another review! Today's performance was real solid, and I am not being paid to said that, LOL. If I were to rank it, I would give it a B, but that's ultimately up to the experts uwu. Here are the experts (that's me!) analysis: \""),
	TEXT("\"As I ruthelessly killed the workers of The New Puppet Post, and punched them again and again with my fists, I thought of your performance tonight. The best aspects, were a masterpiece. They energized me. The flaws? Unignorable. They angered me. That energy and anger fueled me as I took more souls from this world as I have for centuries. Here is the analysis I conjured in the meanwhile: \""),
	TEXT("\"Since July 4th, 1826, my soul has been damned to a doll. An agonizing experience, all my agency has been stripped away, my sins have been damned again and again and have damned the country I built throughout this history. But hearing performances as beautiful as tonight's, it shows me that there is saving grace in my torment. This is the analysis which I wrote upon.\""),
	TEXT("\"Wow\""),
	TEXT("\"help me...\"")}
};

#endif // NEWSPAPER_WIDGET_H_

UCLASS()
class PROJECTGROOVY_API UNewspaperWidget : public UUserWidget
{
	GENERATED_BODY()
	


public:

	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void StartMemory();

	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void initializeEntries(int bodyCount, TArray<int> possibleText);

	UFUNCTION(BlueprintCallable, Category = "Deconstruction")
		void FreeMemory();

	UFUNCTION(BlueprintCallable, Category = "News Entries")
		FString getVictoryMessage(EBodyText bodyAsset, ERanks earnedRank);
protected:
	UPROPERTY(BlueprintReadWrite, Category = "Contents")
	TArray<UMultiLineEditableTextBox*> newsBody;

	TArray<FString>** allText;


};
