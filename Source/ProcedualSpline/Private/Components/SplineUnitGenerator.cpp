// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "SplineUnitGenerator.h"


// Sets default values for this component's properties
USplineUnitGenerator::USplineUnitGenerator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//bWantsBeginPlay = true;
	//PrimaryComponentTick.bCanEverTick = true;
}

TArray<FSplineUnit> USplineUnitGenerator::ParseJsonAndAssignSplineUnits(FString Path)
{
	TArray<FSplineUnit> SplineUnits;
	FVector PrevEndPoint = FVector{ 0,0,0 };

	FString FullPath = FPaths::GameContentDir();
	FullPath += Path;
	FString JsonStr;
	FFileHelper::LoadFileToString(JsonStr, *FullPath);

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Deserialize"));
		}
		TArray<TSharedPtr<FJsonValue>> objArray = JsonObject->GetArrayField(TEXT("SplineUnits"));

		for (int32 i = 0; i < objArray.Num(); i++)
		{
			TSharedPtr<FJsonValue> value = objArray[i];
			TSharedPtr<FJsonObject> json = value->AsObject();

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

			// TODO Jsonのパラメータ型チェック　Jsonのすべてが正しく存在するか？

			TArray<FString> DistanceJson;
			json->TryGetStringArrayField(TEXT("Distance"), DistanceJson);
			FVector Distance = FVector{ FCString::Atof(*DistanceJson[0]), FCString::Atof(*DistanceJson[1]), FCString::Atof(*DistanceJson[2]) };

			TArray<FString> VertexVectorJson;
			json->TryGetStringArrayField(TEXT("VertexVector"), VertexVectorJson);
			FVector VertexVector = FVector{ FCString::Atof(*VertexVectorJson[0]), FCString::Atof(*VertexVectorJson[1]), FCString::Atof(*VertexVectorJson[2]) };

			float WaveCycleCount = json->GetNumberField(TEXT("WaveCycleCount"));
			int32 Density = json->GetNumberField(TEXT("Density"));
			float Msec = json->GetNumberField(TEXT("Msec"));

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
	else {
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Not Deserialize"));
		}
	}

	return SplineUnits;
}
