// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshairs();
}
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = GetPlayerControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller not possessing player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller possessing %s"), *controlledTank->GetName());
	}
	UE_LOG(LogTemp, Warning, TEXT("Player Controller reporting."));
}
ATank* ATankPlayerController::GetPlayerControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
void ATankPlayerController::AimAtCrosshairs()
{
	if (!GetPlayerControlledTank()) { return; }
	FVector OutHitLocation;
	if (GetSightRayHitLocation(OutHitLocation))
	{
		GetPlayerControlledTank()->AimAt(OutHitLocation);
	}
}
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 VPSizeX, VPSizeY;
	GetViewportSize(VPSizeX, VPSizeY);
	auto ScreenLocation = FVector2D(CrosshairXLocation*VPSizeX, CrosshairYLocation*VPSizeY);
	//UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *ScreenLocation.ToString());
	FVector AimDirection;
	if (GetLookDirection(ScreenLocation, AimDirection))
	{
		GetLookVectorHitLocation(AimDirection, OutHitLocation);
		//UE_LOG(LogTemp, Warning, TEXT("Aim Direction: %s"), *AimDirection.ToString());
	}
	//GetWorld();
	/*GetWorld()->LineTraceSingleByObjectType(

	);*/
	return true;
}
bool ATankPlayerController::GetLookDirection(const FVector2D& ScreenLocation, FVector& AimDirection) const
{
	FVector AimPosition;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, AimPosition, AimDirection);
}
bool ATankPlayerController::GetLookVectorHitLocation(const FVector& Direction, FVector& HitLocation) const
{
	bool hit;
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + Direction * LineTraceRange;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		hit = true;
	}
	else 
	{ 
		HitLocation = FVector(0);
		hit = false; 
	}
	return hit;
}


