// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplineDirector.h"


// Sets default values for this component's properties
UProcedualSplineDirector::UProcedualSplineDirector()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UProcedualSplineDirector::Init(USplineComponent *Spline, TArray<FSplineUnit> &SplineUnits,
	                                UProcedualSplineInstanceBuilder *ProcedualSplineInstanceBuilder,
	                                UProcedualSplinePointBuilder *ProcedualSplinePointBuilder)
{
	for (auto SplineUnit : SplineUnits)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, SplineUnit.ToDebugString());

	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("‚Â‚¤‚©‚¾‚º"));
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(Spline->GetNumberOfSplinePoints()));
	ProcedualSplinePointBuilder->Init();
	ProcedualSplineInstanceBuilder->Init(Spline, SplineUnits);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::FromInt(Spline->GetNumberOfSplinePoints()));

	//ProcedualSplineInstanceBuilder = CreateDefaultSubobject<UProcedualSplineInstanceBuilder>(FName("Sl"));
}