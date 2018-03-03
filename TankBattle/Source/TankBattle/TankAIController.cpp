// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = GetAIControlledTank();
	auto playerControlledTank = GetPlayerControlledTank();
	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller not possessing player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller possessing %s"), *controlledTank->GetName());
	}
	if (!playerControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found no player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controller found player tank %s"), *playerControlledTank->GetName());
	}
	
}
ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank* ATankAIController::GetPlayerControlledTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
	{
		PlayerPawn = nullptr;
	}
	return Cast<ATank>(PlayerPawn);
}
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetAIControlledTank()->AimAt(GetPlayerControlledTank()->GetActorLocation());






}


