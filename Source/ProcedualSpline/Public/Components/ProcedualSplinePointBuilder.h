// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ProcedualSplinePointBuilder.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROCEDUALSPLINE_API UProcedualSplinePointBuilder : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProcedualSplinePointBuilder();

	void RegisterComponent();

	void Init();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

};
