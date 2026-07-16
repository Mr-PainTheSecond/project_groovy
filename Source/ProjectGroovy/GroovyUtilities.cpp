// Fill out your copyright notice in the Description page of Project Settings.


#include "GroovyUtilities.h"

int UGroovyUtilities::properMod(int a, int b) {
	if (a >= 0) return a % b;

	int absA = abs(a) % b;

	return (b - absA) % b;
}