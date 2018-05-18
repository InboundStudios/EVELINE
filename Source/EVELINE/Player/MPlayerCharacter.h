// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Classes/Camera/CameraComponent.h"
#include "EVELINE.h"
#include "MPlayerCharacter.generated.h"

UCLASS()
class EVELINE_API AMPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintPure,Category=CharacterMovement)
		inline bool GetPressedJump() const
	{
		return bPressedJump;
	}
	UFUNCTION(BlueprintPure, Category = CharacterMovement)
		inline bool GetPressedSprint() const
	{
		return bPressedSprint;
	}
	UFUNCTION(BlueprintPure, Category = CharacterMovement)
		inline float GetWalkSpeed() const
	{
		return WalkSpeed;
	}
	UFUNCTION(BlueprintPure, Category = CharacterMovement)
		inline float GetRunSpeed() const
	{
		return RunSpeed;
	}
	UFUNCTION(BlueprintPure, Category = Items)
		FORCEINLINE AWeaponBase* GetCurrentWeapon() const
	{
		return CurrentWeapon;
	}
	UFUNCTION(BlueprintPure, Category = Items)
		inline bool HasGun() const
	{
		return bHasGun;
	}
	UFUNCTION(BlueprintCallable, Category = CharacterMovement)
		void SetPressedJump(const bool& Value);
	UFUNCTION(BlueprintCallable, Category = CharacterMovement)
		void SetPressedSprint(const bool& Value);
	AActor* FindFocusedActor();
	void AddToInventory(class AWeaponBase* NewWeapon, int32 Slot);
	int32 SetWeaponSlot(class AWeaponBase* Weapon);
private:
	void EquipWeapon(class AWeaponBase* WeaponToEquip, int32 Slot);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* TPSCamera;
	bool bPressedJump = false;
	bool bPressedSprint = false;
	UPROPERTY(EditDefaultsOnly, Category = CharacterMovement, meta = (AllowPrivateAccess = "true"))
		float WalkSpeed=300.0f;
	UPROPERTY(EditDefaultsOnly, Category = CharacterMovement, meta = (AllowPrivateAccess = "true"))
		float RunSpeed=600.0f;
	UPROPERTY(EditDefaultsOnly, Category = CharacterMovement, meta = (AllowPrivateAccess = "true"))
		float InteractionDistance=1000.0f;

	void HandleHighlight();
	
	class IInteractable* FocusedInterface;
	AActor* FocusedActor;
	bool bHasNewFocus;
	TArray<FBackpackItem> Backpack;
	class AWeaponBase* CurrentWeapon;
	int32 CurrentSlot;
	bool bHasGun;

};
