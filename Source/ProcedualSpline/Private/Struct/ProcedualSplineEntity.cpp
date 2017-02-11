// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplineEntity.h"

FProcedualSplineEntity::FProcedualSplineEntity(int32 UnitLimit)
{
	TotalSplineUnitLength = 0;
	CurrentSplineUnitLength = 0;
	CurrentToSplineUnitNum = 0;

	PrevSplineUnitPointStartNum = 0;
	PrevSplineUnitPointEndNum = 0;

	DisplayableSplineUnitLength = 0;

	DisplayableSplineUnitLimit = 0;

	DisplayableSplineUnitLimit = UnitLimit;
}

FString FProcedualSplineEntity::ToDebugString()
{
	FString Result;
	Result =
		"TotalSplineUnitLength: " + FString::SanitizeFloat(TotalSplineUnitLength) + "  |   "  +
		"CurrentSplineUnitLength: " + FString::SanitizeFloat(CurrentSplineUnitLength) + "  |   "  +
		"CurrentToSplineUnitNum: " + FString::FromInt(CurrentToSplineUnitNum) + "  |   "  +
		"PrevSplineUnitPointStartNum: " + FString::FromInt(PrevSplineUnitPointStartNum) + "  |   "  +
		"PrevSplineUnitPointEndNum: " + FString::FromInt(PrevSplineUnitPointEndNum) + "  |   "  +
		"DisplayableSplineUnitLimit: " + FString::FromInt(DisplayableSplineUnitLimit) + "  |   "  +
		"DisplayableSplineUnitLength: " + FString::SanitizeFloat(DisplayableSplineUnitLength);

	return Result;
}
