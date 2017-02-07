// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplinePointBuilder.h"


// Sets default values for this component's properties
UProcedualSplinePointBuilder::UProcedualSplinePointBuilder()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UProcedualSplinePointBuilder::Init()
{

}


// Called when the game starts
void UProcedualSplinePointBuilder::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UProcedualSplinePointBuilder::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

