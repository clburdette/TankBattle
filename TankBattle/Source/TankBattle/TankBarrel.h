// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKBATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float);
private:
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 20.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevation = 20.0f;
	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevation = 0.0f;	
};
