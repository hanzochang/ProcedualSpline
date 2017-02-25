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

    // ���݂�SplineUnit����̓����\���\�ȃo�b�t�@�����K��
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 DisplayableSplineUnitBuffer;

    // ���ݕ\����������Ă���擪��SplineUnit�̐�
    //UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	//int32 TopmostSplineUnitNumber;

    // ���ݕ\����������Ă������SplineUnit�̐�
    //UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	//int32 RearmostSplineUnitNumber;

	// ���̐�[��Spawn�\��counter�ԍ�
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 TopmostNextSpawnableCounter;

	// ���̌�[��Spawn�\��counter�ԍ�
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 RearmostNextSpawnableCounter;

    // ����PointBuilder/AssetsBuilder�̋N���|�C���g
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	float TopRefreshSplineLength;

    // �߂�ꍇ��PointBuilder/AssetsBuilder�̋N���|�C���g
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	float RearRefreshSplineLength;

public:
	// �����\���\��SplineUnit�̐����v�l
	int32 DisplayableSplineUnitSum();

};