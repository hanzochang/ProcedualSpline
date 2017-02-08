// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "ProcedualSplineDirector.h"

void UProcedualSplineDirector::Initialize(UProcedualSplinePointBuilder *ProcedualSplinePointBuilder)
{
	ProcedualSplinePointBuilder->Init();
}
