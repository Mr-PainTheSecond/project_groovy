// Fill out your copyright notice in the Description page of Project Settings.


#include "NewspaperBase.h"

UNewspaperBase::UNewspaperBase() {
	allText = NULL;



	/*UGroovyUtilities::free2DTArray(allText, 20);*/
}


void UNewspaperBase::BeginDestroy() {
	Super::BeginDestroy();

	/*UGroovyUtilities::free2DTArray(allText, newsBody.Num());*/
}

void UNewspaperBase::initializeEntries(int bodyCount, TArray<int> possibleText) {

}
