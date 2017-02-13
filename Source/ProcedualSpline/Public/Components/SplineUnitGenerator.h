// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "SplineUnit.h"
#include "SpawnableActor.h"
#include "SplineUnitGenerator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDUALSPLINE_API USplineUnitGenerator : public UActorComponent
{
	GENERATED_BODY()

public:	
	USplineUnitGenerator();
	TArray<FSplineUnit> GenerateSplineUnits(FString Path);

private:
	void ParseJsonAndGenerateSplineUnits(TArray<FSplineUnit> &SplineUnits, TSharedPtr<FJsonObject> JsonObject);

	ESplineUnit ParseWaveType(TSharedPtr<FJsonObject> json);
	FVector ParseDistance(TSharedPtr<FJsonObject> json);
	FVector ParseVertexVector(TSharedPtr<FJsonObject> json);
	FString JsonFullPath(FString Path);
	TArray<FSpawnableActor> USplineUnitGenerator::ParseSpawnableActors(TSharedPtr<FJsonObject> json);
};
