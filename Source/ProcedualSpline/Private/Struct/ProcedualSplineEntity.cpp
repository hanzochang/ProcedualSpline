// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplineEntity.h"

FProcedualSplineEntity::FProcedualSplineEntity(int32 UnitLimit)
{
	DisplayableSplineUnitBuffer = UnitLimit;
	TopmostNextSpawnableCounter = 0;
	RearmostNextSpawnableCounter = 0;
	TopRefreshSplineLength = 0;
	RearRefreshSplineLength = 0;
}

FString FProcedualSplineEntity::ToDebugString()
{
	FString Result;
	Result =
		"DisplayableSplineUnitBuffer: " + FString::FromInt(DisplayableSplineUnitBuffer) + "  |   " +
		"TopmostSplineUnitNumber: " + FString::FromInt(TopmostNextSpawnableCounter) + "  |   " +
		"RearmostSplineUnitNumber: " + FString::FromInt(RearmostNextSpawnableCounter) + "  |   " +
		"TopRefreshSplineLength: " + FString::SanitizeFloat(TopRefreshSplineLength) + "  |   " +
		"RearRefreshSplineLength: " + FString::SanitizeFloat(RearRefreshSplineLength);

	return Result;
}

int32 FProcedualSplineEntity::DisplayableSplineUnitSum()
{
	return (DisplayableSplineUnitBuffer * 2) + 1;
}
