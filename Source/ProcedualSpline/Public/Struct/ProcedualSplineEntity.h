// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProcedualSplineEntity.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FProcedualSplineEntity
{
    GENERATED_BODY()

public:
	FProcedualSplineEntity(int32 UnitLimit = 1);
	FString ToDebugString();

	float TotalSplineUnitLength;
	float CurrentSplineUnitLength;
	int32 CurrentToSplineUnitNum;

	int32 PrevSplineUnitPointStartNum;
	int32 PrevSplineUnitPointEndNum;

	TArray<float> DisplayableSplineUnitLengths;
	int32 DisplayableSplineUnitLimit;
	float DisplayableSplineUnitLength;
};