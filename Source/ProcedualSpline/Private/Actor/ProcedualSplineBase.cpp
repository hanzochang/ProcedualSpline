// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplineBase.h"


// Sets default values
AProcedualSplineBase::AProcedualSplineBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SplineUnitGenerator = CreateDefaultSubobject<USplineUnitGenerator>(FName("SplineUnitGenerator"));
}

// Called when the game starts or when spawned
void AProcedualSplineBase::BeginPlay()
{
	Super::BeginPlay();
	
}