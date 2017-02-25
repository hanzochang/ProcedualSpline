// Fill out your copyright notice in the Description page of Project Settings.

#include "ProcedualSpline.h"
#include "AssignedSplineUnitPoint.h"

FAssignedSplineUnitPoint FAssignedSplineUnitPoint::GenerateAssignedSplineUnitPoint(USplineComponent *Spline, int32 PointNumber)
{
	FAssignedSplineUnitPoint AssignedSplineUnitPoint;
	AssignedSplineUnitPoint.Location = Spline->GetLocationAtSplinePoint(PointNumber, ESplineCoordinateSpace::Type::Local);
	AssignedSplineUnitPoint.Direction = Spline->GetDirectionAtSplinePoint(PointNumber, ESplineCoordinateSpace::Type::Local);
	AssignedSplineUnitPoint.Rotation = Spline->GetRotationAtSplinePoint(PointNumber, ESplineCoordinateSpace::Type::Local);
	//AssignedSplineUnitPoint.Index = Spline->

	return AssignedSplineUnitPoint;
}
