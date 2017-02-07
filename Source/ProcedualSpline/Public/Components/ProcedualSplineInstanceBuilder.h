// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SplineUnit.h"
#include "Components/SplineComponent.h"
#include "ProcedualSplineInstanceBuilder.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDUALSPLINE_API UProcedualSplineInstanceBuilder : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnyWhere)
	float TotalSplineUnitLength;

	UPROPERTY(VisibleAnyWhere)
	float CurrentSplineUnitLength;

	UPROPERTY(VisibleAnyWhere)
	int32 CurrentToSplineUnitNum;

	UPROPERTY(VisibleAnyWhere)
	int32 PrevSplineUnitPointStartNum;

	UPROPERTY(VisibleAnyWhere)
	int32 PrevSplineUnitPointEndNum;

	// ìØéûÇ…ï\é¶â¬î\Ç»SplineUnitÇÃç≈ëÂêîÇê›íËÇ∑ÇÈ
	UPROPERTY(VisibleAnyWhere)
	TArray<float> DisplayableSplineUnitLengths;

	UPROPERTY(VisibleAnyWhere)
	int32 DisplayableSplineUnitLimit;

	UPROPERTY(VisibleAnyWhere)
	float DisplayableSplineUnitLength;

public:	
	UProcedualSplineInstanceBuilder();

	void Init(USplineComponent *Spline, TArray<FSplineUnit> &SplineUnits);

	void AssignSplinePointsFromSplineUnit(USplineComponent *Spline,
		TArray<FVector> &SplinePoints,
		TArray<FSplineUnit> &SplineUnits);

private:

	void AssignSplinePoints(USplineComponent *Spline,
		TArray<FVector> &SplinePoints,
		TArray<FSplineUnit> &SplineUnits,
		int32 counter,
		FVector &StartPoint
	);

	float GetCurrentSplineUnitLength(
		USplineComponent *Spline,
		int32 PointStartNumber,
		int32 PointEndNumber
	);

	float GetGeneratedSplineLength(
		USplineComponent *Spline,
		int32 EdgeSplineUnitStartSplineNum
	);

	void SetDisplayableSplineUnitLength();
	
};
