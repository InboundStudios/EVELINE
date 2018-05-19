// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "EVELINE.generated.h"


USTRUCT(BlueprintType)
struct FBackpackItem
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
		class AWeaponBase* Weapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
		int32 Slot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Items)
		bool bIsSelected;
	inline bool operator==(const FBackpackItem& f) const
	{
		return Weapon == f.Weapon;
	}
};
UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	AT_Bullets UMETA(DisplayName = "Bullets"),

};