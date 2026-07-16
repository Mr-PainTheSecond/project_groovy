// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GroovyUtilities.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGROOVY_API UGroovyUtilities : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Math")
		static int properMod(int a, int b);
};
