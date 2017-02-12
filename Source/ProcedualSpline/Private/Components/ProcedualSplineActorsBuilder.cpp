// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplineActorsBuilder.h"

void UProcedualSplineActorsBuilder::Initialize()
{
}

void UProcedualSplineActorsBuilder::LoadDebugGrid()
{
	//static ConstructorHelpers::FObjectFinder<UBlueprint> DebugGridClassFinder( TEXT( "Blueprint'/Game/BluePrint/B_DebugGrid_01.B_DebugGrid_01'" ) );

	//if (DebugGridClassFinder.Succeeded())
	//{
	//	WhatToSpawn = (UClass*)DebugGridClassFinder.Object->GeneratedClass;
	//}
}

void UProcedualSplineActorsBuilder::SetDebugGridsEachSplinePoints(
	TSubclassOf<class AActor> WhatToSpawn,
	int PointNum
)
{
	FVector Location = { 0.0, 0.0, 0.0 };
	FRotator Rotation = { 0.0, 0.0, 0.0 };
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Owner;
	AActor* const SpawningObject = GetWorld()->SpawnActor<AActor>(WhatToSpawn,
		Spline->GetLocationAtSplinePoint(PointNum, ESplineCoordinateSpace::Type::Local), 
		Spline->GetRotationAtSplinePoint(PointNum, ESplineCoordinateSpace::Type::Local),
		SpawnParams);

	SpawningObject->Destroy();

}