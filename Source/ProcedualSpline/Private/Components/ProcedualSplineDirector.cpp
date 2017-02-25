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

	testFlag = true;

    Owner = GetOwner();
}

void UProcedualSplineDirector::CreateInitialSpline()
{
	// 例外処理を書く。Builderがなかった場合 
	int32 counter = 0;
	FSpawnedSplineUnit PreviousSpawnedSplineUnit;
	float CurrentLength = 0;
	FVector StartPoint = FVector{ 0,0,0 };

	Entity.RearmostNextSpawnableCounter = 0; // TODO 要確認

	for (int32 i = 0; i < Entity.DisplayableSplineUnitSum(); i++)
	{
		CurrentLength = Spline->GetSplineLength();
		counter = i % SplineUnits.Num();
		
		FSplineUnit SplineUnit = SplineUnits[counter];
		FSpawnedSplineUnit SpawnedSplineUnit = FSpawnedSplineUnit::GenerateSpawnedSplineUnit(SplineUnit);

		ProcedualSplinePointBuilder->AssignPointsToSpline(Spline, SpawnedSplineUnit, StartPoint);
		ProcedualSplineActorsBuilder->SpawnActors(Owner, Spline, SpawnedSplineUnit);

		SpawnedSplineUnit.DeriveNextSpawnPoint(PreviousSpawnedSplineUnit);
		SpawnedSplineUnit.Length = Spline->GetSplineLength() - CurrentLength;
		StartPoint = SpawnedSplineUnit.NextSpawnPoint;

		SpawnedSplineUnits.Push(SpawnedSplineUnit);
		PreviousSpawnedSplineUnit = SpawnedSplineUnit;
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(SpawnedSplineUnit.Length)); }

		Entity.TopmostNextSpawnableCounter = i;
	}

	RefreshEntityParameters();

	//for (FSpawnedSplineUnit SpawnedSplineUnit : SpawnedSplineUnits)
	//{
	//	SpawnedSplineUnit.Destroy();
	//}
}

void UProcedualSplineDirector::CheckProcedualSplineEntity(float CurrentLength)
{
	if (CurrentLength >= Entity.TopRefreshSplineLength && testFlag) {
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Do Refresh")); }

		// 1.過去のポイントを消す ProcedualSplinePointBuilder->DestroyPoints();
		// 2.過去のアクターを消す ProcedualSplineActorsBuilder->DestroyActors();
		// 3.次のSplineUnitを特定する
		// 4.次のポイントを生成する ProcedualSplinePointBuilder->AssignPointsToSpline(Spline, SpawnedSplineUnit, StartPoint);
		// 5.次のポイントのオブジェクトを配置する ProcedualSplineActorsBuilder->SpawnActors(Owner, Spline, SpawnedSplineUnit);
		// 6.RefreshEntityParameters();

		// 1はあとでやるむずい
		// 1.過去のポイントを消す ProcedualSplinePointBuilder->DestroyPoints();
		// 2.過去のアクターを消す ProcedualSplineActorsBuilder->DestroyActors();
		DeleteFirstSpawnedSplineUnit();

		// 3.次のSplineUnitを特定する
		int32 i = Entity.TopmostNextSpawnableCounter;
		int32 counter = i % SplineUnits.Num();
		FSplineUnit SplineUnit = SplineUnits[counter];
		FSpawnedSplineUnit SpawnedSplineUnit = FSpawnedSplineUnit::GenerateSpawnedSplineUnit(SplineUnit);

		ProcedualSplinePointBuilder->AssignPointsToSpline(Spline, SpawnedSplineUnit, SpawnedSplineUnits.Last().NextSpawnPoint);
		ProcedualSplineActorsBuilder->SpawnActors(Owner, Spline, SpawnedSplineUnit);

		SpawnedSplineUnit.DeriveNextSpawnPoint(SpawnedSplineUnits.Top());
		SpawnedSplineUnit.Length = Spline->GetSplineLength() - CurrentLength;
		SpawnedSplineUnits.Push(SpawnedSplineUnit);

		Entity.TopmostNextSpawnableCounter = i + 1;

		RefreshEntityParameters();
		//testFlag = false;
	}
	else {
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Still..")); }
	}
}

/*
** private
*/

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

void UProcedualSplineDirector::DeleteFirstSpawnedSplineUnit()
{
	// TODO 不要なStructをメモリからどう消すか？調査とdebugで監視
	FSpawnedSplineUnit *FirstSpawnedSplineUnit = &SpawnedSplineUnits[0];
	SpawnedSplineUnits.RemoveAt(0);
	FirstSpawnedSplineUnit->Destroy();
}
