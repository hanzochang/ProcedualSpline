// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "SpawnableActor.h"

// Unreal C++内で生成するための疑似コンストラクタ
FSpawnableActor FSpawnableActor::GenerateSpawnableActor(
	ESpawnableActorPlacementType PlacementType,
	TSubclassOf<class AActor> WhatToSpawn
)
{
	FSpawnableActor SpawnableActor;
	SpawnableActor.PlacementType = PlacementType;
	SpawnableActor.WhatToSpawn = WhatToSpawn;

	return SpawnableActor;
}
