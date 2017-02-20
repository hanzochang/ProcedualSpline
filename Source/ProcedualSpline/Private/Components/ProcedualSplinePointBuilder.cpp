// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplinePointBuilder.h"

void UProcedualSplinePointBuilder::Initialize(FProcedualSplineEntity &Entity,
	USplineComponent *SplineComponent, TArray<FSplineUnit> &SplineUnits)
{
	Spline = SplineComponent;
}

void UProcedualSplinePointBuilder::AssignPointsToSpline(
	FProcedualSplineEntity &Entity, FSpawnedSplineUnit &SpawnedSplineUnit, FVector &StartPoint
)
{
	FVector PrevDirection = Spline->GetDirectionAtSplinePoint(Spline->GetNumberOfSplinePoints(), ESplineCoordinateSpace::Type::Local);
	FRotator PrevRotation  = Spline->GetRotationAtSplinePoint(Spline->GetNumberOfSplinePoints(), ESplineCoordinateSpace::Type::Local);

	// デメテル違反 wrapする
	// というか下記の塊は一括でSpawnedSplineUnitに持っていく
	TArray<FVector> SplinePoints = SpawnedSplineUnit.SplineUnit.DeriveSplinePointsAddTo(StartPoint, PrevDirection, PrevRotation);

	for (FVector SplinePoint : SplinePoints) {
		Spline->AddSplinePoint(SplinePoint, ESplineCoordinateSpace::Type::Local);
		SpawnedSplineUnit.PushAssignedSplineUnitPoints(Spline, Spline->GetNumberOfSplinePoints());
	}
	SpawnedSplineUnit.DeriveNextSpawnPoint();
	// ここまでもってく
}

//void UProcedualSplinePointBuilder::AssignPointsToSpline(
//	FProcedualSplineEntity &Entity, TArray<FSplineUnit> &SplineUnits
//)
//{
//	int32 counter = 0;
//	int32 TopmostSplineNumber = 0;
//	TArray<FVector> SplinePoints;
//	FVector StartPoint = FVector{ 0,0,0 }; //これはガン、SplineStructのほうにいれる
//
//	for (int32 i = 0; i < Entity.DisplayableSplineUnitSum(); i++)
//	{
//		TopmostSplineNumber = Spline->GetNumberOfSplinePoints();
//		counter = i % SplineUnits.Num();
//
//		FVector Direction = Spline->GetDirectionAtSplinePoint(Spline->GetNumberOfSplinePoints(), ESplineCoordinateSpace::Type::Local);
//		FRotator Rotation  = Spline->GetRotationAtSplinePoint(Spline->GetNumberOfSplinePoints(), ESplineCoordinateSpace::Type::Local);
//
//		SplinePoints = SplineUnits[counter].DeriveSplinePointsAddTo(StartPoint, Direction, Rotation);
//		StartPoint = SplineUnits[counter].DeriveNextSplineUnitStartPoint(StartPoint, Direction, Rotation);
//
//		for (FVector SplinePoint : SplinePoints) {
//			Spline->AddSplinePoint(SplinePoint, ESplineCoordinateSpace::Type::Local);
//		}
//
//		// ここでSpawnActorをアサインじゃない？
//	}
//}

//void UProcedualSplinePointBuilder::Initialize(FProcedualSplineEntity &Entity,
//	USplineComponent *Spline,
//	TArray<FSplineUnit> &SplineUnits)
//{
//	TArray<FVector> SplinePoints;
//	FVector StartPoint = FVector{ 0,0,0 };
//	int32 EdgeSplineUnitStartSplineNum = 0;
//	int32 counter = 0;
//
//	for (auto i = 0; i < Entity.DisplayableSplineUnitLimit; i++)
//	{
//		EdgeSplineUnitStartSplineNum = Spline->GetNumberOfSplinePoints();
//		counter += i;
//		if (counter >= SplineUnits.Num()) { counter = 0; }
//
//		AssignSplinePoints(Spline, SplinePoints, SplineUnits, counter, StartPoint);
//		Entity.DisplayableSplineUnitLengths.Push(GetGeneratedSplineLength(Entity, Spline,
//			EdgeSplineUnitStartSplineNum));
//	}
//
//	SetDisplayableSplineUnitLength(Entity);
//}
//
//void UProcedualSplinePointBuilder::AssignSplinePoints(
//	USplineComponent *Spline,
//	TArray<FVector> &SplinePoints,
//	TArray<FSplineUnit> &SplineUnits,
//	int32 counter,
//	FVector &StartPoint
//)
//{
//	SplineUnits[counter].DeriveSplinePointsAddTo(SplinePoints, StartPoint);
//	Spline->SetSplinePoints(SplinePoints, ESplineCoordinateSpace::Type::Local);
//	StartPoint = Spline->GetLocationAtSplinePoint(Spline->GetNumberOfSplinePoints(),
//		ESplineCoordinateSpace::Local);
//}
//
//float UProcedualSplinePointBuilder::GetGeneratedSplineLength(
//	FProcedualSplineEntity &Entity,
//	USplineComponent *Spline,
//	int32 EdgeSplineUnitStartSplineNum
//)
//{
//	Entity.PrevSplineUnitPointStartNum = EdgeSplineUnitStartSplineNum;
//	Entity.PrevSplineUnitPointEndNum = Spline->GetNumberOfSplinePoints() - 1;
//	return GetCurrentSplineUnitLength(Spline, Entity.PrevSplineUnitPointStartNum, Entity.PrevSplineUnitPointEndNum);
//}
//
//float UProcedualSplinePointBuilder::GetCurrentSplineUnitLength(
//	USplineComponent *Spline,
//	int32 PointStartNumber,
//	int32 PointEndNumber
//)
//{
//	float LastLength = Spline->GetDistanceAlongSplineAtSplinePoint(PointEndNumber);
//    float StartLength = Spline->GetDistanceAlongSplineAtSplinePoint(PointStartNumber);
//	return LastLength - StartLength;
//}
//
//void UProcedualSplinePointBuilder::SetDisplayableSplineUnitLength(FProcedualSplineEntity &Entity)
//{
//	for(auto i = 0; i <= Entity.CurrentToSplineUnitNum; i++)
//	{
//		Entity.DisplayableSplineUnitLength += Entity.DisplayableSplineUnitLengths[i];
//	}
//}
