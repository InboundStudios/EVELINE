// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "EVELINE.h"
#include "TakeDamage.generated.h"
/**
 * 
 */
UINTERFACE(BlueprintType)
class EVELINE_API UTakeDamage : public UInterface
{
	GENERATED_BODY()
};

class EVELINE_API ITakeDamage
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interact)
		void TakeDamage(EAmmoType AmmoData,float MinDamageModifier,float MaxDamageModifier,float CritDamageModifier,AActor* DamageCauser, struct FHitResult Hit);
	
};