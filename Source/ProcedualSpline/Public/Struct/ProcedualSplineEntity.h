// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProcedualSplineEntity.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FProcedualSplineEntity
{
    GENERATED_BODY()

public:
	FProcedualSplineEntity(int32 UnitLimit = 1);
	FString ToDebugString();

	TArray<TArray<AActor*>> SpawnActors;

	float TotalSplineUnitLength;
	float CurrentSplineUnitLength;
	int32 CurrentToSplineUnitNum;
	int32 PrevSplineUnitPointStartNum;
	int32 PrevSplineUnitPointEndNum;
	TArray<float> DisplayableSplineUnitLengths;
	int32 DisplayableSplineUnitLimit;
	float DisplayableSplineUnitLength;

    // �����\���\��SplineUnit�̐�
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 DisplayableSplineUnitNumber;

    // ���ݕ\����������Ă���擪��SplineUnit�̐�
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 TopmostSplineUnitNumber;

    // ���ݕ\����������Ă���擪��SplineUnit�̐�
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 RearmostSplineUnitNumber;

    // ����PointBuilder/AssetsBuilder�̋N���|�C���g
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	float TopRefreshSplineLength;

    // �߂�ꍇ��PointBuilder/AssetsBuilder�̋N���|�C���g
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	float RearRefreshSplineLength;

};