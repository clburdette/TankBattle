// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBattle.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	if (!Turret) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Firepoint"));
	bool bOutVelocityReady = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed, false, 0.0f, 0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bOutVelocityReady)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
		MoveTurret(AimDirection);
		auto TankName = GetOwner()->GetName();
		//UE_LOG(LogTemp, Warning, TEXT("%s Aiming at %s"), *TankName, *AimDirection.ToString());
	}
}
void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}
UTankBarrel* UTankAimingComponent::GetBarrel()
{
	return Barrel;
}
void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto BADeltaRotator = AimRotator - BarrelRotator;
	Barrel->Elevate(BADeltaRotator.Pitch);
}
void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}
UTankTurret* UTankAimingComponent::GetTurret()
{
	return Turret;
}
void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimRotator = AimDirection.Rotation();
	auto BADeltaRotator = AimRotator - TurretRotator;
	Turret->YawTurret(BADeltaRotator.Yaw);
	//UE_LOG(LogTemp, Warning, TEXT("TRotator %s"),*TurretRotator.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("ARotator %s"),*AimDirection.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("BARotator%s"),*BADeltaRotator.ToString());
}
