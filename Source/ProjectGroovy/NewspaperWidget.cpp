// Fill out your copyright notice in the Description page of Project Settings.


#include "NewspaperWidget.h"

void UNewspaperWidget::StartMemory() {

	allText = NULL;

	TArray<FString>** test = (TArray<FString>**)malloc(sizeof(TArray<FString>*) * 20);

	if (test == NULL) {
		RequestEngineExit("Test failed due to malloc");
	}

	for (int a = 0; a < 20; a++) {
		test[a] = new TArray<FString>();
	}

	UKismetSystemLibrary::PrintString(GetWorld(), TEXT("THIS FUNCTION IS CALLED YAY!!!"));

	UGroovyUtilities::free2DTArray(test, 20);
}

void UNewspaperWidget::initializeEntries(int bodyCount, TArray<int> possibleText) {

}


void UNewspaperWidget::FreeMemory() {
	if (allText == NULL) return;

	UGroovyUtilities::free2DTArray(allText, newsBody.Num());
}