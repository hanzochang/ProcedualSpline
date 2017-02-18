// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplineActorsBuilder.h"

void UProcedualSplineActorsBuilder::Initialize(USplineComponent* OwnerSpline)
{
	Owner = GetOwner();
	Spline = OwnerSpline;
}

void UProcedualSplineActorsBuilder::SpawnActors(TArray<FSplineUnit> &SplineUnits, int PointNum)
{
	// TODO SplineUnitごとにどうやってスポーンさせる？
	FSplineUnit SplineUnit = SplineUnits[0];
	for (auto i = 0; i < Spline->GetNumberOfSplinePoints(); i++) {
		if (Owner && Spline) {
			for(FSpawnableActor SpawnableActor : SplineUnit.SpawnableActors)
			{
				FVector Location = { 0.0, 0.0, 0.0 };
				FRotator Rotation = { 0.0, 0.0, 0.0 };
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = Owner;
				AActor* const SpawningObject = GetWorld()->SpawnActor<AActor>(SpawnableActor.WhatToSpawn,
					Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::Type::Local), 
					Spline->GetRotationAtSplinePoint(i, ESplineCoordinateSpace::Type::Local),
					SpawnParams);
			}

		}
		else {
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("UProedualSplineActorsBuilder aren't initialized"));
			}
		}
	}
}