// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SplineUnit.h"
#include "SplineUnitGenerator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDUALSPLINE_API USplineUnitGenerator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USplineUnitGenerator();

	static TArray<FSplineUnit> ParseJsonAndAssignSplineUnits(FString Path);
};
