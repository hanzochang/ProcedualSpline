// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "SplineUnit.h"

/**
 * Converts a ESplineUnit to String.
 * 
 * @param	EplineUnit
 * @returns String
 */

FString GetSplineUnitEnumAsString(ESplineUnit EnumValue)
{
  const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ESplineUnit"), true);
  if(!EnumPtr) return FString("Invalid");
 
  return EnumPtr->GetEnumName((int32)EnumValue);
};

/**
 * Converts a FSplineUnit to String.
 * 
 * @param	SplineUnit		SplineUnit members to sanitize
 * @returns String
 */

FString FSplineUnit::ToDebugString()
{
	FString Result;
	Result =
		"UnitVector: " + UnitVector.ToString() + "  |   " +
		"Scalar: " + FString::SanitizeFloat(Scalar) + "  |   " +
		"Density" + FString::FromInt(Density) + "  |   " +
		"CurveUnitVector: " + CurveUnitVector.ToString() + "  |   " +
		"CurveScalar: " + FString::SanitizeFloat(CurveScalar) + "  |   " +
		"WaveFreq: " + FString::FromInt(WaveFreq) + "  |   " +
		"Msec: " + FString::SanitizeFloat(Msec) + "  |   " +
		"loop: " + FString::FromInt(loop);
		//"WaveType: " + WaveType
		//"SpawnableActors: " + SpawnableActors

	return Result;
}

//FVector FSplineUnit::BetweenPoints()
//{
//	return Distance / Density;
//}

// Unreal C++内で生成するための疑似コンストラクタ
FSplineUnit FSplineUnit::GenerateSplineUnit(
		ESplineUnit WaveType,
		FVector UnitVector,
		float Scalar,
		int32 Density,
		FVector CurveUnitVector,
		float CurveScalar,
		float WaveFreq,
		float Msec,
		int32 loop,
		TArray<FSpawnableActor> SpawnableActors
)
{
	FSplineUnit SplineUnit;
	SplineUnit.WaveType = WaveType;
	SplineUnit.UnitVector = UnitVector;
	SplineUnit.Scalar = Scalar;
	SplineUnit.Density = Density;
	SplineUnit.CurveUnitVector = CurveUnitVector;
	SplineUnit.CurveScalar = CurveScalar;
	SplineUnit.WaveFreq = WaveFreq;
	SplineUnit.Msec = Msec;
	SplineUnit.loop = loop;
	SplineUnit.SpawnableActors = SpawnableActors;

	return SplineUnit;
}

// SplineUnitをPointsポインタにSplineUnitの状態に応じてセットする
//TArray<FVector> FSplineUnit::DeriveSplinePointsAddTo(FVector PrevPoint,
//	                                      FVector PrevDirection, FRotator PrevRotation)
//{
//	TArray<FVector> Points;
//
//	switch (WaveType)
//	{
//	case ESplineUnit::WAVE_LINEAR:
//		Points = DeriveWaveLinearPoints(PrevPoint, PrevDirection, PrevRotation);
//		break;
//	case ESplineUnit::WAVE_SIN:
//		Points = DeriveWaveSinPoints(PrevPoint, PrevDirection, PrevRotation);
//		break;
//	case ESplineUnit::WAVE_TRIANGLE:
//		Points = DeriveWaveTrianglePoints(PrevPoint);
//		break;
//	case ESplineUnit::WAVE_SAWTOOTH:
//		break;
//	}
//
//	return Points;
//}

//TArray<FVector> FSplineUnit::DeriveWaveLinearPoints(FVector PrevPoint, FVector PrevDirection, FRotator PrevRotation)
//{
//	TArray<FVector> Points;
//
//	FVector PrevDirectionVertical = FRotator{ 90, 0, 0 }.RotateVector(PrevDirection);
//	PrevDirectionVertical = FVector{ 0, 0, PrevDirectionVertical.Z };
//	FQuat quat = FQuat{ PrevDirectionVertical, FMath::DegreesToRadians(PrevRotation.Yaw) };
//
//	for (auto i = 0; i < Density; i++)
//	{
//		Points.Push(PrevPoint + BetweenPoints() * i);
//		//FVector NextPoint = quat.RotateVector(BetweenPoints());
//		//Points.Push(PrevPoint + NextPoint * i);
//	}
//
//	return Points;
//}
//
//TArray<FVector> FSplineUnit::DeriveWaveSinPoints(FVector PrevPoint, FVector PrevDirection, FRotator PrevRotation)
//{
//	TArray<FVector> Points;
//
//	for (auto i = 0; i < Density; i++)
//	{
//		float VertexBase = FMath::Sin(PI / Density * i * WaveCycleCount);
//		Points.Push(PrevPoint + BetweenPoints() * i + (VertexVector * VertexBase));
//	}
//
//	return Points;
//}
//
//TArray<FVector> FSplineUnit::DeriveWaveTrianglePoints(FVector PrevPoint)
//{
//	TArray<FVector> Points;
//	float Quater = Density / WaveCycleCount;
//
//	for (auto i = 0; i < Density; i++)
//	{
//		// バグあり
//		FVector BasePoint = PrevPoint + BetweenPoints() * i;
//		float NumPerQuater = i / Quater;
//		float NumPerQuaterDecimal = NumPerQuater - FMath::Floor(NumPerQuater);
//		float BranchPoint = FMath::Sin(PI * (i / Quater));
//		float BranchPointPrev = (i != 0 ? FMath::Sin(PI * ((i-1) / Quater)) : 0);
//
//		if (BranchPoint > 0)
//		{
//			if (BranchPoint - BranchPointPrev >= 0)
//			{
//				Points.Push(BasePoint + (VertexVector*2 * (NumPerQuaterDecimal)));
//			}
//			else
//			{
//				Points.Push(BasePoint + (VertexVector*2 - (VertexVector*2 * (NumPerQuaterDecimal))));
//			}
//		}
//		else if (BranchPoint < 0)
//		{
//			if (BranchPoint - BranchPointPrev >= 0)
//			{
//				Points.Push(BasePoint - (VertexVector*2 - (VertexVector*2 * (NumPerQuaterDecimal))));
//			}
//			else
//			{
//				Points.Push(BasePoint - (VertexVector*2 * (NumPerQuaterDecimal)));
//			}
//		}
//		else
//		{
//			Points.Push(BetweenPoints() * i);
//		}
//		
//	}
//
//	return Points;
//}
