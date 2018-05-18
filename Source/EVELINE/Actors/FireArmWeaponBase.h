// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "WeaponBase.h"
#include "Particles/ParticleSystemComponent.h"
#include "FireArmWeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class EVELINE_API AFireArmWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
public:
	AFireArmWeaponBase();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void OnInteract_Implementation(AActor* Caller) override;
	virtual void StartFire_Implementation() override;
	virtual void StopFire_Implementation() override;
	void AddAmmo(float Amount);
	void SetAmmo(float Amount);
	void Reload();
	void SpawnFireEffect();
	void SpawnImpactEffect(const FHitResult& Hit);
	virtual void DoFire();
	void DealDamage(const FHitResult& Hit);
	UFUNCTION(BlueprintPure,Category=Stats)
		inline bool HasFullAmmo() const {
		return CurrentAmmo == MaxAmmo ? true : false;
	}
	UFUNCTION(BlueprintPure, Category = Stats)
		inline float GetMaxAmmo() const {
		return MaxAmmo;
	}
	UFUNCTION(BlueprintPure, Category = Stats)
		inline float GetCurrentAmmo() const {
		return CurrentAmmo;
	}
	UFUNCTION(BlueprintPure, Category = Stats)
		inline float GetClipSize() const {
		return ClipSize;
	}
	UFUNCTION(BlueprintPure, Category = Stats)
		inline float GetMaxClipSize() const {
		return MaxClipSize;
	}
	UFUNCTION(BlueprintPure, Category = Stats)
		inline float GetFireRate() const {
		return FireRate;
	}
	UFUNCTION(BlueprintPure, Category = Stats)
		inline float GetMaxRange() const {
		return MaxRange;
	}
protected:
	
	FVector CalcSpread();
	void SpawnBullet();
	void IncreaseSpread(float Value);
	FVector AimDir();
	UPROPERTY(EditDefaultsOnly,Category=Setup,meta=(AllowPrivateAccess="true"))
		bool bSpawnFull = true;
	UPROPERTY(EditDefaultsOnly,Category=Setup, meta = (AllowPrivateAccess = "true"))
		FName MuzzleSocketName;
	UPROPERTY(EditDefaultsOnly, Category = Setup, meta = (AllowPrivateAccess = "true"))
		bool bUsesProjectile;
	UPROPERTY(EditDefaultsOnly, Category = Setu, meta = (AllowPrivateAccess = "true"))
		bool bCanReload;
	UPROPERTY(EditDefaultsOnly,Category=Setup, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ABullet> BulletClass;
private:
	UPROPERTY(EditDefaultsOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
		float MaxAmmo = 0;
		float ClipSize;
	UPROPERTY(EditDefaultsOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
		float MaxClipSize;
	/*       Spread     */
		float Spread;
	UPROPERTY(EditDefaultsOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
		float MinSpread;
	UPROPERTY(EditDefaultsOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
		float MaxSpread;
	UPROPERTY(EditDefaultsOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
		float SpreadIncreaseSpeed;
	UPROPERTY(EditDefaultsOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
		float SpreadDecreaseSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
		float FireRate;
	UPROPERTY(EditDefaultsOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
		float MaxRange;
	UPROPERTY(EditDefaultsOnly, Category = Setup, meta = (AllowPrivateAccess = "true"))
		UParticleSystem* ShotEffect;
	UPROPERTY(EditDefaultsOnly, Category = Setup, meta = (AllowPrivateAccess = "true"))
		USoundWave* ShotSound;
	UPROPERTY(EditDefaultsOnly, Category = Setup, meta = (AllowPrivateAccess = "true"))
		UParticleSystem* ImpactEffect;
	UPROPERTY(EditDefaultsOnly, Category = Setup, meta = (AllowPrivateAccess = "true"))
		USoundWave* ImpactSound;
	

	bool bIsFiring;
	float CurrentAmmo;

	FTimerHandle BeamEffectTimerHandle;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
		float MaxBeamEffectTime;
	UParticleSystemComponent* BeamEffect;
	FCollisionQueryParams TraceParams;
	FTimerHandle FireRateHandle;
	
};
