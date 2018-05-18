// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "SideArmWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class EVELINE_API ASideArmWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
public:
	virtual void StartFire_Implementation() override;
	virtual void StopFire_Implementation() override;
	virtual void OnInteract_Implementation(AActor* Caller) override;

	void DealDamage();
	virtual void Tick(float DeltaTime) override;
	void SetIsAttacking(bool Value);
private:
	bool bIsAttacking = false;
	UPROPERTY(EditDefaultsOnly,Category=Setup)
		FName LowerSphereSocket;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		FName UpperSphereSocket;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float AttackRaycastRadius = 15.0f;
};
