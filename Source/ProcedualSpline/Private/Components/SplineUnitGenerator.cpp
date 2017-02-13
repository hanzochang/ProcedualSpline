// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "SplineUnitGenerator.h"


// Sets default values for this component's properties
USplineUnitGenerator::USplineUnitGenerator()
{
}

TArray<FSplineUnit> USplineUnitGenerator::GenerateSplineUnits(FString Path)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonFullPath(Path));
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	TArray<FSplineUnit> SplineUnits;

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Deserialize"));
		}

		ParseJsonAndGenerateSplineUnits(SplineUnits, JsonObject);
	}
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Not Deserialize"));
		}
	}

	return SplineUnits;
}


/*
* Private
*/

void USplineUnitGenerator::ParseJsonAndGenerateSplineUnits(TArray<FSplineUnit> &SplineUnits, TSharedPtr<FJsonObject> JsonObject)
{
	FVector PrevEndPoint = FVector{ 0,0,0 };
	TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField(TEXT("SplineUnits"));

	for (int32 i = 0; i < objArray.Num(); i++)
	{
		TSharedPtr<FJsonValue> value = objArray[i];
		TSharedPtr<FJsonObject> json = value->AsObject();

		ESplineUnit WaveType = ParseWaveType(json);
		FVector Distance = ParseDistance(json);
		FVector VertexVector = ParseVertexVector(json);
		float WaveCycleCount = json->GetNumberField(TEXT("WaveCycleCount"));
		int32 Density = json->GetNumberField(TEXT("Density"));
		float Msec = json->GetNumberField(TEXT("Msec"));

		TArray<FSpawnableActor> SpawnableActors;


		FSplineUnit SplineUnit = FSplineUnit::GenerateSplineUnit(
			WaveType,
			Distance,
			PrevEndPoint,
			VertexVector,
			WaveCycleCount,
			Density,
			Msec
		);

		PrevEndPoint = SplineUnit.StartLocation + SplineUnit.Distance;
		SplineUnits.Push(SplineUnit);
	}
}

// これは構造体でやる仕事
ESplineUnit USplineUnitGenerator::ParseWaveType(TSharedPtr<FJsonObject> json)
{
	FString WaveTypeStr = json->GetStringField(TEXT("WaveType"));
	ESplineUnit WaveType;

	if (WaveTypeStr == "WAVE_LINEAR")
	{
		WaveType = ESplineUnit::WAVE_LINEAR;
	}
	else if (WaveTypeStr == "WAVE_SIN")
	{
		WaveType = ESplineUnit::WAVE_SIN;
	}
	else if (WaveTypeStr == "WAVE_TRIANGLE")
	{
		WaveType = ESplineUnit::WAVE_TRIANGLE;
	}
	else
	{
		WaveType = ESplineUnit::WAVE_LINEAR;
	}

	return WaveType;
}

FVector USplineUnitGenerator::ParseDistance(TSharedPtr<FJsonObject> json)
{
	TArray<FString> DistanceJson;
	json->TryGetStringArrayField(TEXT("Distance"), DistanceJson);
	FVector Distance = FVector{ FCString::Atof(*DistanceJson[0]),
								FCString::Atof(*DistanceJson[1]),
								FCString::Atof(*DistanceJson[2]) };
	return Distance;
}

FVector USplineUnitGenerator::ParseVertexVector(TSharedPtr<FJsonObject> json)
{
	TArray<FString> VertexVectorJson;
	json->TryGetStringArrayField(TEXT("VertexVector"), VertexVectorJson);
	FVector VertexVector = FVector{ FCString::Atof(*VertexVectorJson[0]),
									FCString::Atof(*VertexVectorJson[1]), 
									FCString::Atof(*VertexVectorJson[2]) };
	return VertexVector;
}

FString USplineUnitGenerator::JsonFullPath(FString Path)
{
	FString FullPath = FPaths::GameContentDir();
	FullPath += Path;
	FString JsonStr;
	FFileHelper::LoadFileToString(JsonStr, *FullPath);

	return JsonStr;
}

TArray<FSpawnableActor> USplineUnitGenerator::ParseSpawnableActors(TSharedPtr<FJsonObject> json)
{
	TArray<FSpawnableActor> SpawnableActors;
	TArray<TSharedPtr<FJsonValue>> childArray = json->GetArrayField(TEXT("SpawnableActors"));
	if (childArray.Num() > 0)
	{
		if (GEngine) { GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Go")); }
		for (int32 i = 0; i < childArray.Num(); i++) {
			TSharedPtr<FJsonValue> childValue = childArray[i];
			TSharedPtr<FJsonObject> childJson = childValue->AsObject();

			FString ActorsReference = childJson->GetStringField(TEXT("ActorsReference"));
			FString PlacementType = childJson->GetStringField(TEXT("PlacementType"));

			// TODO 次はここを動的にして、内部構造体内部で適宜振り分ける
			//static ConstructorHelpers::FObjectFinder<UBlueprint> ActorFinder("Blueprint'/Game/BluePrint/B_DebugGrid_01.B_DebugGrid_01'"ActorsReference);
			static ConstructorHelpers::FObjectFinder<UBlueprint> ActorFinder( TEXT("Blueprint'/Game/BluePrint/B_DebugGrid_01.B_DebugGrid_01'"));
			if (ActorFinder.Succeeded())
			{
				TSubclassOf<class AActor> WhatToSpawn = (UClass*)ActorFinder.Object->GeneratedClass;
				FSpawnableActor SpawnableActor = FSpawnableActor::GenerateSpawnableActor(ESpawnableActorPlacementType::EACH_POINT, WhatToSpawn);
				SpawnableActors.Push(SpawnableActor);
			}
		}
	}

	return SpawnableActors;
}
