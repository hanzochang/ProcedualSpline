// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplineDirector.h"

void UProcedualSplineDirector::Initialize(
	USplineComponent *InSpline,
	TArray<FSplineUnit> &InSplineUnits,
	TArray<FSpawnedSplineUnit> &InSpawnedSplineUnits,
	float &InDeletedSplineLengthsDiff,
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

	DeletedSplineLengthsDiff = InDeletedSplineLengthsDiff;

	testFlag = true;

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
	//float aaa = CurrentLength - DeletedSplineLengthsDiff;
	if ((CurrentLength - DeletedSplineLengthsDiff) >= Entity.TopRefreshSplineLength && testFlag) {
		//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Do Refresh")); }

		// 1.�ߋ��̃|�C���g������ ProcedualSplinePointBuilder->DestroyPoints();
		// 2.�ߋ��̃A�N�^�[������ ProcedualSplineActorsBuilder->DestroyActors();
		// 3.����SplineUnit����肷��
		// 4.���̃|�C���g�𐶐����� ProcedualSplinePointBuilder->AssignPointsToSpline(Spline, SpawnedSplineUnit, StartPoint);
		// 5.���̃|�C���g�̃I�u�W�F�N�g��z�u���� ProcedualSplineActorsBuilder->SpawnActors(Owner, Spline, SpawnedSplineUnit);
		// 6.RefreshEntityParameters();

		// 1�͂��Ƃł��ނ���
		// 1.�ߋ��̃|�C���g������ ProcedualSplinePointBuilder->DestroyPoints();
		// 2.�ߋ��̃A�N�^�[������ ProcedualSplineActorsBuilder->DestroyActors();
		testFlag = false;

		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Orange, TEXT("===============Befor AddingSplinePoint Length!============")); }
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Orange, FString::SanitizeFloat(Spline->GetSplineLength())); }
		// 3.����SplineUnit����肷��
		float aaa = CurrentLength - DeletedSplineLengthsDiff;
		GenerateNextSpawnedSplineUnit(aaa);


		DeleteFirstSpawnedSplineUnit();

		//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Green, FString::SanitizeFloat(aaa)); }
		// 4. �X�v���C�������t���b�V������
		UpdateSpline();

		// 5. Pawn�̈ʒu��z�u���Ȃ���
		RefreshEntityParameters();
		testFlag = true;
	}
	else {
		//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Still..")); }
	}
}

/*
** private
*/

void UProcedualSplineDirector::RefreshEntityParameters()
{
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Orange, TEXT("===============CheckSpawnedSplineUnitsNum============")); }
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Orange, FString::SanitizeFloat(SpawnedSplineUnits.Num())); }
	float SplineLength = 0;
	for (int32 i = 0; i < SpawnedSplineUnits.Num(); i++)
	{
		float number = i + 1;

		if (number == Entity.DisplayableSplineUnitBuffer)
		{
			Entity.RearRefreshSplineLength = SplineLength + (SpawnedSplineUnits[i].Length / 2);
		}
		else if (number == (Entity.DisplayableSplineUnitBuffer + 1 + 1))
		{
			Entity.TopRefreshSplineLength = SplineLength + (SpawnedSplineUnits[i].Length / 2);
		}

		SplineLength += SpawnedSplineUnits[i].Length;

		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Cyan, TEXT("===============SpawnedSplineUnits��Length-------")); }
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Cyan, FString::SanitizeFloat(SpawnedSplineUnits[i].Length)); }
	}
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Green, TEXT("Refreshed!")); }
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Green, FString::SanitizeFloat(Entity.TopRefreshSplineLength)); }
}

void UProcedualSplineDirector::GenerateNextSpawnedSplineUnit(float CurrentLength)
{
	int32 i = Entity.TopmostNextSpawnableCounter;
	int32 counter = i % SplineUnits.Num();
	FSplineUnit SplineUnit = SplineUnits[counter];
	FSpawnedSplineUnit SpawnedSplineUnit = FSpawnedSplineUnit::GenerateSpawnedSplineUnit(SplineUnit);

	float BeforeTotal = Spline->GetSplineLength();
	ProcedualSplinePointBuilder->AssignPointsToSpline(Spline, SpawnedSplineUnit, SpawnedSplineUnits.Last().NextSpawnPoint);
	ProcedualSplineActorsBuilder->SpawnActors(Owner, Spline, SpawnedSplineUnit);

	SpawnedSplineUnit.DeriveNextSpawnPoint(SpawnedSplineUnits.Top());

	// �������L��
	SpawnedSplineUnit.Length = Spline->GetSplineLength() - BeforeTotal;
	SpawnedSplineUnits.Push(SpawnedSplineUnit);

	// ����
    Entity.TopmostNextSpawnableCounter = i + 1;
}

void UProcedualSplineDirector::DeleteFirstSpawnedSplineUnit()
{
	// TODO �s�v��Struct������������ǂ��������H������debug�ŊĎ�
	FSpawnedSplineUnit *FirstSpawnedSplineUnit = &SpawnedSplineUnits[0];

	// �����͕���
	DeletedSplineLengthsDiff += FirstSpawnedSplineUnit->Length;

	FirstSpawnedSplineUnit->Destroy();
	SpawnedSplineUnits.RemoveAt(0);
}

void UProcedualSplineDirector::UpdateSpline()
{
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Black, TEXT("===============BeforeClear..")); }
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Black, FString::SanitizeFloat(Spline->GetNumberOfSplinePoints())); }
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Black, FString::SanitizeFloat(Spline->GetSplineLength())); }
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Blue, TEXT("===============OldSplineLength!============")); }
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Blue, FString::SanitizeFloat(Spline->GetSplineLength())); }
	Spline->ClearSplinePoints();
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Green, TEXT("===============Cleared!============")); }
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Green, FString::SanitizeFloat(Spline->GetNumberOfSplinePoints())); }
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Green, FString::SanitizeFloat(Spline->GetSplineLength())); }
	//Spline->AddSplinePoint(FVector{0,0,0}, ESplineCoordinateSpace::Type::Local);
	//Spline->AddSplinePoint(FVector{0,0,0}, ESplineCoordinateSpace::Type::Local);
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Blue, TEXT("===============AddedOneLocation!============")); }
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Blue, FString::SanitizeFloat(Spline->GetNumberOfSplinePoints())); }
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Blue, FString::SanitizeFloat(Spline->GetSplineLength())); }
	for (FSpawnedSplineUnit SpawnedSplineUnit: SpawnedSplineUnits)
	{
		for (FAssignedSplineUnitPoint AssignedSplineUnitPoint : SpawnedSplineUnit.AssignedSplineUnitPoints)
		{
			Spline->AddSplinePoint(AssignedSplineUnitPoint.Location, ESplineCoordinateSpace::Type::Local);
			//SpawnedSplineUnit.PushAssignedSplineUnitPoints(Spline, Spline->GetNumberOfSplinePoints());
		}
	}
	//if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::SanitizeFloat(Spline->GetNumberOfSplinePoints())); }
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Purple, TEXT("===============NewSplineLength!============")); }
	if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 105.f, FColor::Purple, FString::SanitizeFloat(Spline->GetSplineLength())); }
}
