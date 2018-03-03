// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto ClampedSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	auto ElevationChange = ClampedSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	auto Elevation = FMath::Clamp(RawNewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}



