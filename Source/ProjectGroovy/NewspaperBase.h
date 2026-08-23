// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WidgetBlueprint.h"
#include "Components/MultiLineEditableTextBox.h"
#include "GroovyUtilities.h"

#include "NewspaperBase.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTGROOVY_API UNewspaperBase : public UWidgetBlueprint
{
	GENERATED_BODY()
		UNewspaperBase();

		
public:
	virtual void BeginDestroy() override;


	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void initializeEntries(int bodyCount, TArray<int> possibleText);
protected:
	UPROPERTY(BlueprintReadWrite, Category = "Contents")
		TArray<UMultiLineEditableTextBox*> newsBody;

		TArray<FString>* allText;
	
};