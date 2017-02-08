// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplinePointBuilder.h"

//void UProcedualSplinePointBuilder::Init(USplineComponent *Spline,
//	TArray<FSplineUnit> &SplineUnits)
void UProcedualSplinePointBuilder::Init()
{
	TArray<FVector> SplinePoints;
	FVector StartPoint = FVector{ 0,0,0 };
	int32 EdgeSplineUnitStartSplineNum = 0;
	int32 counter = 0;
//	EdgeSplineUnitStartSplineNum = Spline->GetNumberOfSplinePoints();
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("initialize"));
//  GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(EdgeSplineUnitStartSplineNum));
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::FromInt(counter));

}




