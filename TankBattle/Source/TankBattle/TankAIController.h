// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class TANKBATTLE_API ATankAIController : public AAIController
{
	GENERATED_BODY()
private:
	ATank* GetAIControlledTank() const;
	ATank* GetPlayerControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
