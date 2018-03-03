// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class TANKBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:
	ATank* GetPlayerControlledTank() const;
	void AimAtCrosshairs();
	bool GetSightRayHitLocation(FVector&) const;
	bool GetLookDirection(const FVector2D&, FVector&) const;
	bool GetLookVectorHitLocation(const FVector&, FVector&) const;
	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;
};
