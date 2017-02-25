// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplineDirector.h"

void UProcedualSplineDirector::Initialize(
	USplineComponent *InSpline,
	TArray<FSplineUnit> &InSplineUnits,
	TArray<FSpawnedSplineUnit> &InSpawnedSplineUnits,
	FProcedualSplineEntity &InEntity,
	UProcedualSplinePointBuilder *InProcedualSplinePointBuilder,
	UProcedualSplineActorsBuilder *InProcedualSplineActorsBuilder
)
{
	Spline = InSpline;
	SplineUnits = InSplineUnits;
	InSpawnedSplineUnits = InSpawnedSplineUnits;
	Entity = InEntity;
	ProcedualSplinePointBuilder = InProcedualSplinePointBuilder;
	ProcedualSplineActorsBuilder = InProcedualSplineActorsBuilder;
	PointsIndex = 0;

    Owner = GetOwner();
}

void UProcedualSplineDirector::CreateInitialSpline()
{
	// ��O�����������BBuilder���Ȃ������ꍇ 
	int32 counter = 0;
	FSpawnedSplineUnit PreviousSpawnedSplineUnit;
	float CurrentLength = 0;
	FVector StartPoint = FVector{ 0,0,0 };

	Entity.RearmostNextSpawnableCounter = 0; // TODO �v�m�F

	for (int32 i = 0; i < Entity.DisplayableSplineUnitSum(); i++)
	{
		CurrentLength = Spline->GetSplineLength();
		counter = i % SplineUnits.Num();
		
		FSplineUnit SplineUnit = SplineUnits[counter];
		FSpawnedSplineUnit SpawnedSplineUnit = FSpawnedSplineUnit::GenerateSpawnedSplineUnit(SplineUnit);

		ProcedualSplinePointBuilder->AssignPointsToSpline(Spline, SpawnedSplineUnit, StartPoint, PointsIndex);
		ProcedualSplineActorsBuilder->SpawnActors(Owner, Spline, SpawnedSplineUnit);

		SpawnedSplineUnit.DeriveNextSpawnPoint(PreviousSpawnedSplineUnit);
		SpawnedSplineUnit.Length = Spline->GetSplineLength() - CurrentLength;
		StartPoint = SpawnedSplineUnit.NextSpawnPoint;

		SpawnedSplineUnits.Push(SpawnedSplineUnit);
		PreviousSpawnedSplineUnit = SpawnedSplineUnit;
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(SpawnedSplineUnit.Length)); }
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Black, FString::FromInt(PointsIndex)); }

		Entity.TopmostNextSpawnableCounter = i;
	}
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 100.f, FColor::Green, Spline->GetLocationAtSplinePoint(100, ESplineCoordinateSpace::Local).ToString() ); }

	RefreshEntityParameters();

	//for (FSpawnedSplineUnit SpawnedSplineUnit : SpawnedSplineUnits)
	//{
	//	SpawnedSplineUnit.Destroy();
	//}
}

void UProcedualSplineDirector::CheckProcedualSplineEntity(float CurrentLength)
{
	if (CurrentLength >= Entity.TopRefreshSplineLength) {
		//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Do Refresh")); }

		//int32 i = Entity.TopmostNextSpawnableCounter;
		//int32 counter = i % SplineUnits.Num();

		//FSplineUnit SplineUnit = SplineUnits[counter];
		//FSpawnedSplineUnit SpawnedSplineUnit = FSpawnedSplineUnit::GenerateSpawnedSplineUnit(SplineUnit);

		//ProcedualSplinePointBuilder->AssignPointsToSpline(Spline, SpawnedSplineUnit, SpawnedSplineUnits.Last().NextSpawnPoint);
		//ProcedualSplineActorsBuilder->SpawnActors(Owner, Spline, SpawnedSplineUnit);
		//Entity.TopmostNextSpawnableCounter = i;

		// �ߋ��̃|�C���g������ ProcedualSplinePointBuilder->DestroyPoints();
		// �ߋ��̃A�N�^�[������ ProcedualSplineActorsBuilder->DestroyActors();
		// ����SplineUnit����肷��
		// ���̃|�C���g�𐶐����� ProcedualSplinePointBuilder->AssignPointsToSpline(Spline, SpawnedSplineUnit, StartPoint);
		// ���̃|�C���g�̃I�u�W�F�N�g��z�u���� ProcedualSplineActorsBuilder->SpawnActors(Owner, Spline, SpawnedSplineUnit);
		// RefreshEntityParameters();
	}
	else {
		//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Still..")); }
	}
}

void UProcedualSplineDirector::RefreshEntityParameters()
{
	float SplineLength = 0;
	for (int32 i = 0; i < SpawnedSplineUnits.Num(); i++)
	{
		float number = i + 1;

		if (number == Entity.DisplayableSplineUnitBuffer)
		{
			Entity.RearRefreshSplineLength = SplineLength + SpawnedSplineUnits[i].Length / 2;
		}
		else if (number == (Entity.DisplayableSplineUnitBuffer + 1 + 1))
		{
			Entity.TopRefreshSplineLength = SplineLength + SpawnedSplineUnits[i].Length / 2;
		}

		SplineLength += SpawnedSplineUnits[i].Length;
	}

	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::SanitizeFloat(SplineLength)); }
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, FString::SanitizeFloat(Entity.RearRefreshSplineLength)); }
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, FString::SanitizeFloat(Entity.TopRefreshSplineLength)); }

}
