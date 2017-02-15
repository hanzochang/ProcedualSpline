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

    // 同時表示可能なSplineUnitの数
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 DisplayableSplineUnitNumber;

    // 現在表示を許可されている先頭のSplineUnitの数
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 TopmostSplineUnitNumber;

    // 現在表示を許可されている先頭のSplineUnitの数
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 RearmostSplineUnitNumber;

    // 次のPointBuilder/AssetsBuilderの起動ポイント
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	float TopRefreshSplineLength;

    // 戻る場合のPointBuilder/AssetsBuilderの起動ポイント
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	float RearRefreshSplineLength;

};