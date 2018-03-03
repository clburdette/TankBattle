// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankTurret.h"

void UTankTurret::YawTurret(float RelativeSpeed)
{
	auto ClampedSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	auto YawChange = ClampedSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewYaw = RelativeRotation.Yaw + YawChange;
	SetRelativeRotation(FRotator(0, NewYaw, 0));
	//UE_LOG(LogTemp, Warning, TEXT("YawChange %f"), YawChange);
	//UE_LOG(LogTemp, Warning, TEXT("NewYaw %f"), NewYaw);
}


