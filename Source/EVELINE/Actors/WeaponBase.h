// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "InteractableActor.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class EVELINE_API AWeaponBase : public AInteractableActor
{
	GENERATED_BODY()
public:
	AWeaponBase();
	virtual void OnBeginFocus_Implementation() override;
	virtual void OnEndFocus_Implementation() override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Fire)
		void StartFire();
	virtual void StartFire_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Fire)
		void StopFire();
	virtual void StopFire_Implementation();
	UFUNCTION(BlueprintPure,Category=Mesh)
		FORCEINLINE USkeletalMeshComponent* GetWeaponMesh() const
	{
		return WeaponMesh;
	}
	UFUNCTION(BlueprintPure,Category=Stats)
		inline float GetBaseDamage() const
	{
		return BaseDamage;
	}
protected:
	UPROPERTY(EditDefaultsOnly, Category = Stats)
		float BaseDamage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* WeaponMesh;
	
	
	
};
