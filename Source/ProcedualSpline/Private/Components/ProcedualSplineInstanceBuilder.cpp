// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplineInstanceBuilder.h"


// Sets default values for this component's properties
UProcedualSplineInstanceBuilder::UProcedualSplineInstanceBuilder()
{
	//bWantsBeginPlay = true;
	//PrimaryComponentTick.bCanEverTick = true;

	TotalSplineUnitLength = 0;
	CurrentSplineUnitLength = 0;
	CurrentToSplineUnitNum = 0;

	PrevSplineUnitPointStartNum = 0;
	PrevSplineUnitPointEndNum = 0;

	DisplayableSplineUnitLimit = 2;
	DisplayableSplineUnitLength = 0;

}

void UProcedualSplineInstanceBuilder::Init(USplineComponent *Spline, TArray<FSplineUnit> &SplineUnits)
{
	TArray<FVector> SplinePoints;
	FVector StartPoint = FVector{ 0,0,0 };
	int32 EdgeSplineUnitStartSplineNum = 0;
	int32 counter = 0;
	EdgeSplineUnitStartSplineNum = Spline->GetNumberOfSplinePoints();
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("initializeŠ¯—»"));
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(EdgeSplineUnitStartSplineNum));
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::FromInt(counter));

	for (int32 i = 0; i < DisplayableSplineUnitLimit; i++)
	{
		//EdgeSplineUnitStartSplineNum = Spline->GetNumberOfSplinePoints();
		//counter += i;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(i));

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(counter));
		//if (counter >= SplineUnits.Num()) { counter = 0; }
		//if (counter >= SplineUnits.Num()) {  }

		//AssignSplinePoints(Spline, SplinePoints, SplineUnits, counter, StartPoint);
		//DisplayableSplineUnitLengths.Push(GetGeneratedSplineLength(Spline, EdgeSplineUnitStartSplineNum));
	}

	//SetDisplayableSplineUnitLength();
}

void UProcedualSplineInstanceBuilder::AssignSplinePoints(
	USplineComponent *Spline,
	TArray<FVector> &SplinePoints,
	TArray<FSplineUnit> &SplineUnits,
	int32 counter,
	FVector &StartPoint
)
{
	SplineUnits[counter].DeriveSplinePointsAddTo(SplinePoints, StartPoint);
	Spline->SetSplinePoints(SplinePoints, ESplineCoordinateSpace::Type::Local);
	StartPoint = Spline->GetLocationAtSplinePoint(Spline->GetNumberOfSplinePoints(),
		ESplineCoordinateSpace::Local);
}


float UProcedualSplineInstanceBuilder::GetCurrentSplineUnitLength(
	USplineComponent *Spline,
	int32 PointStartNumber,
	int32 PointEndNumber
)
{
	float LastLength = Spline->GetDistanceAlongSplineAtSplinePoint(PointEndNumber);
    float StartLength = Spline->GetDistanceAlongSplineAtSplinePoint(PointStartNumber);
	return LastLength - StartLength;
}

float UProcedualSplineInstanceBuilder::GetGeneratedSplineLength(
	USplineComponent *Spline,
	int32 EdgeSplineUnitStartSplineNum
)
{
	PrevSplineUnitPointStartNum = EdgeSplineUnitStartSplineNum;
	PrevSplineUnitPointEndNum = Spline->GetNumberOfSplinePoints() - 1;
	return GetCurrentSplineUnitLength(Spline, PrevSplineUnitPointStartNum, PrevSplineUnitPointEndNum);
}

void UProcedualSplineInstanceBuilder::SetDisplayableSplineUnitLength()
{
	for(auto i = 0; i <= CurrentToSplineUnitNum; i++)
	{
		DisplayableSplineUnitLength += DisplayableSplineUnitLengths[i];
	}
}