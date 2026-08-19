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
protected:
	UPROPERTY(BlueprintReadWrite, Category = "Contents")
	TArray<UMultiLineEditableTextBox*> newsBody;

	TArray<FString>** allText;


};
