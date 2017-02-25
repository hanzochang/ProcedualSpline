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

    // 現在のSplineUnitからの同時表示可能なバッファ数を規定
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 DisplayableSplineUnitBuffer;

    // 現在表示を許可されている先頭のSplineUnitの数
    //UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	//int32 TopmostSplineUnitNumber;

    // 現在表示を許可されている後ろのSplineUnitの数
    //UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	//int32 RearmostSplineUnitNumber;

	// 次の先端にSpawn可能なcounter番号
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 TopmostNextSpawnableCounter;

	// 次の後端にSpawn可能なcounter番号
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	int32 RearmostNextSpawnableCounter;

    // 次のPointBuilder/AssetsBuilderの起動ポイント
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	float TopRefreshSplineLength;

    // 戻る場合のPointBuilder/AssetsBuilderの起動ポイント
    UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Struct")
	float RearRefreshSplineLength;

public:
	// 同時表示可能なSplineUnitの数合計値
	int32 DisplayableSplineUnitSum();

};