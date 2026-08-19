// Fill out your copyright notice in the Description page of Project Settings.


#include "NewspaperBase.h"

UNewspaperBase::UNewspaperBase() {
	allText = NULL;

	TArray<FString>* test = (TArray<FString>*)malloc(sizeof(TArray<FString>) * 20);

	if (test == NULL) {
		RequestEngineExit("Test failed due to malloc");
	}

	/*UGroovyUtilities::free2DTArray(allText, 20);*/
}


void UNewspaperBase::BeginDestroy() {
	Super::BeginDestroy();

	/*UGroovyUtilities::free2DTArray(allText, newsBody.Num());*/
}

void UNewspaperBase::initializeEntries(int bodyCount, TArray<int> possibleText) {

}