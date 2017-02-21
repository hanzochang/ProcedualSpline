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

FSpawnableActor FSpawnableActor::GenerateSpawnableActor(
	FString PlacementType,
	FString WhatToSpawn
)
{
	FSpawnableActor SpawnableActor;
	SpawnableActor.AssignPlacementType(PlacementType);
	SpawnableActor.AssignWhatToSpawn(WhatToSpawn);

	return SpawnableActor;
}


/**
 *  AssignPlacementType From FString
 *
 *  @param [FString] Str
 */
void FSpawnableActor::AssignPlacementType(FString Str)
{
	if (Str == "EACH_POINT")
	{
		PlacementType = ESpawnableActorPlacementType::EACH_POINT;
	}
	else
	{
		PlacementType = ESpawnableActorPlacementType::EACH_POINT;
	}

}

/**
 *  Search blueprint class And load this, and assign WhatToSpawn to this.
 *
 *  @param [FString] Str
 */
void FSpawnableActor::AssignWhatToSpawn(FString Str)
{
	// TODO 調査 staticをつけないことの弊害
	// static ConstructorHelpers::FObjectFinder<UBlueprint> ActorFinder( *Str );
	ConstructorHelpers::FObjectFinder<UBlueprint> ActorFinder = ConstructorHelpers::FObjectFinder<UBlueprint>( *Str );
	if (ActorFinder.Succeeded())
	{
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Succeeded loading Blueprint Class")); }
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Str); }
		WhatToSpawn = (UClass*)ActorFinder.Object->GeneratedClass;

		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, WhatToSpawn->GetName()); }
	}
	else
	{
		// If system cannot load specified blueprint class
		// load alternative actor class and assign to WhatToSpawn.
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Cannot load Blueprint Class")); }
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, Str); }
		static ConstructorHelpers::FObjectFinder<UBlueprint> AlternativeActorFinder( TEXT("Blueprint'/Game/BluePrint/B_DebugGrid_01.B_DebugGrid_01'") );
		if (AlternativeActorFinder.Succeeded())
		{
			WhatToSpawn = (UClass*)AlternativeActorFinder.Object->GeneratedClass;
		}

	}
}
