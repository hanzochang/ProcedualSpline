// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SpawnableActor.generated.h"

UENUM(BlueprintType)
enum class ESpawnableActorPlacementType : uint8
{
    EACH_POINT  UMETA(DisplayName = "EachPoint")
};

USTRUCT(BlueprintType)
struct FSpawnableActor
{
	GENERATED_BODY()

public:

};