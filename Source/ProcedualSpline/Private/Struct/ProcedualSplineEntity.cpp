// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplineEntity.h"

FProcedualSplineEntity::FProcedualSplineEntity(int32 UnitLimit)
{
	//TotalSplineUnitLength = 0;
	//CurrentSplineUnitLength = 0;
	//CurrentToSplineUnitNum = 0;
	//PrevSplineUnitPointStartNum = 0;
	//PrevSplineUnitPointEndNum = 0;
	//DisplayableSplineUnitLength = 0;
	//DisplayableSplineUnitLimit = 0;
	//DisplayableSplineUnitLimit = UnitLimit;

	DisplayableSplineUnitBuffer = UnitLimit;
	TopmostSplineUnitNumber = 0;
	RearmostSplineUnitNumber = 0;
	TopRefreshSplineLength = 0;
	RearRefreshSplineLength = 0;
}

FString FProcedualSplineEntity::ToDebugString()
{
	FString Result;
	Result =
		"DisplayableSplineUnitBuffer: " + FString::FromInt(DisplayableSplineUnitBuffer) + "  |   " +
		"TopmostSplineUnitNumber: " + FString::FromInt(TopmostSplineUnitNumber) + "  |   " +
		"RearmostSplineUnitNumber: " + FString::FromInt(RearmostSplineUnitNumber) + "  |   " +
		"TopRefreshSplineLength: " + FString::SanitizeFloat(TopRefreshSplineLength) + "  |   " +
		"RearRefreshSplineLength: " + FString::SanitizeFloat(RearRefreshSplineLength);

	return Result;
}

int32 FProcedualSplineEntity::DisplayableSplineUnitSum()
{
	return (DisplayableSplineUnitBuffer * 2) + 1;
}
