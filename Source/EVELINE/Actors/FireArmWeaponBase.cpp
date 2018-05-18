// Fill out your copyright notice in the Description page of Project Settings.

#include "FireArmWeaponBase.h"
#include "Player/MPlayerCharacter.h"
#include "Bullet.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

AFireArmWeaponBase::AFireArmWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
	TraceParams = FCollisionQueryParams(FName(TEXT("HitscanTrace")), true, this);
	Spread = MinSpread;
	if (FMath::Fmod(CurrentAmmo, MaxClipSize) == 0)
		ClipSize = MaxClipSize;
	else
		ClipSize = FMath::Fmod(CurrentAmmo, MaxClipSize);

}
void AFireArmWeaponBase::Tick(float DeltaTime)
{
	if (!bIsFiring)
	{
		if (Spread - SpreadDecreaseSpeed >= MinSpread)
			Spread -= SpreadDecreaseSpeed;
	}

}

void AFireArmWeaponBase::BeginPlay() {
	Super::BeginPlay();
	if (bSpawnFull) CurrentAmmo = MaxAmmo;
	else CurrentAmmo = 0;

	Reload();
}
void AFireArmWeaponBase::AddAmmo(float Amount) {
	CurrentAmmo = FMath::Clamp(CurrentAmmo + Amount, CurrentAmmo, MaxAmmo);
}

void AFireArmWeaponBase::SetAmmo(float Amount) {
	CurrentAmmo = Amount;
}
void AFireArmWeaponBase::DealDamage(const FHitResult& Hit) {
	if (Hit.GetActor()) {
		float DealtDamage = BaseDamage;
		FVector ShotDir = GetActorLocation() - Hit.ImpactPoint;

		FPointDamageEvent DamageEvent;
		DamageEvent.Damage = DealtDamage;
		DamageEvent.HitInfo = Hit;
		DamageEvent.ShotDirection = ShotDir;
		DamageEvent.ShotDirection.Normalize();
		ACharacter* Char = Cast<ACharacter>(GetOwner());
		if (Char)
		{
			Hit.GetActor()->TakeDamage(DealtDamage, DamageEvent, Char->GetController(), this);
		}
		AMPlayerCharacter* Player = Cast<AMPlayerCharacter>(Char);
		//if (Player)
			//Player->Spot_On();
	}
}
void AFireArmWeaponBase::StartFire_Implementation() {
	if (ClipSize > 0) {

		bIsFiring = true;
		DoFire();
		float TimerDelay = FireRate > 0 ? 1 / (FireRate*0.01667) : FApp::GetDeltaTime();

		if (!FireRateHandle.IsValid())
			GetWorld()->GetTimerManager().SetTimer(FireRateHandle, this, &AWeaponBase::StartFire, TimerDelay, true);

	}
	else {
		StopFire();
		UE_LOG(LogTemp, Warning, TEXT("ClipSize Error"));
	}
}
void AFireArmWeaponBase::StopFire_Implementation() {

	bIsFiring = false;
	GetWorld()->GetTimerManager().ClearTimer(FireRateHandle);
	FireRateHandle.Invalidate();

}
void AFireArmWeaponBase::DoFire() {
	if (GetOwner())
	{
		FHitResult Hit(ForceInit);
		FVector Start = WeaponMesh->GetSocketLocation(MuzzleSocketName);
		FVector End = Start + (AimDir()*MaxRange);

		GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Pawn, TraceParams);

		UE_LOG(LogTemp, Warning, TEXT("Fire!"));

		if (Spread < MaxSpread)
			IncreaseSpread(SpreadIncreaseSpeed);
		ClipSize--;

		SpawnFireEffect();

		if (bUsesProjectile)
		{
			SpawnBullet();
		}
		else
		{	
			if (Hit.GetActor()) {
				UE_LOG(LogTemp, Warning, TEXT("Hit! %s"), *Hit.GetActor()->GetName());
				DealDamage(Hit);
				SpawnImpactEffect(Hit);
			}
		}
	}
}
FVector AFireArmWeaponBase::CalcSpread() {
	ACharacter* Char = Cast<ACharacter>(GetOwner());
	if (Char) {
		FVector Direction = Char->GetActorRotation().Vector();
		float Angle = atan(Spread / 10000);
		return FMath::VRandCone(Direction, Angle);
	}
	else {
		FVector Direction = GetActorRotation().Vector();
		float Angle = atan(Spread / 10000);
		return FMath::VRandCone(Direction, Angle);
	}
}
void AFireArmWeaponBase::SpawnFireEffect() {
	FVector Location = WeaponMesh->GetSocketLocation(MuzzleSocketName);
	FRotator Rotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	UGameplayStatics::SpawnEmitterAttached(ShotEffect, WeaponMesh, MuzzleSocketName, Location, Rotation, EAttachLocation::KeepWorldPosition, true);
	BeamEffect = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShotEffect, Location, Rotation, false);
	ACharacter* Char = Cast<ACharacter>(GetOwner());
	if (BeamEffect&&Char)
	{
		BeamEffect->SetVisibility(true);
		BeamEffect->SetBeamSourcePoint(0, Location + Char->GetControlRotation().Vector() * 500, 0);
		//GetWorld()->GetTimerManager().SetTimer(BeamEffectTimerHandle, this, &AWeaponBase::BeamEffectVisibility, MaxBeamEffectTime, false);


	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ShotSound, Location, Rotation, 1, 1, 0);
}
void AFireArmWeaponBase::SpawnImpactEffect(const FHitResult& Hit) {
	FVector Location = Hit.ImpactPoint;
	FRotator Rotation = Hit.ImpactNormal.Rotation();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Location, Rotation, true);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Location, Rotation, 1, 1, 0);
	if (BeamEffect)
	{

		BeamEffect->SetBeamTargetPoint(0, Location, 0);
		//GetWorld()->GetTimerManager().SetTimer(BeamEffectTimerHandle, this, &AWeaponBase::BeamEffectVisibility, MaxBeamEffectTime, false);
		BeamEffect->SetVisibility(false);
	}
}
void AFireArmWeaponBase::OnInteract_Implementation(AActor* Caller) {
	AMPlayerCharacter* Player = Cast<AMPlayerCharacter>(Caller);
	if (Player) {

		StaticMesh->SetVisibility(false);
		StaticMesh->SetSimulatePhysics(false);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Player->AddToInventory(this, Player->SetWeaponSlot(this));
		


	}
	else
	{
		StaticMesh->SetVisibility(false);
		StaticMesh->SetSimulatePhysics(false);
		StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
void AFireArmWeaponBase::Reload()
{
	if (bCanReload)
	{
		if (CurrentAmmo > 0)
		{
			if (CurrentAmmo - (MaxClipSize - ClipSize) >= 0)
			{
				CurrentAmmo -= (MaxClipSize - ClipSize);
				ClipSize += (MaxClipSize - ClipSize);
			}
			else
			{
				ClipSize += CurrentAmmo;
				CurrentAmmo = 0;
			}
		}
	}

}
void AFireArmWeaponBase::IncreaseSpread(float Value)
{
	Spread += Value;
}
void AFireArmWeaponBase::SpawnBullet()
{

	if (BulletClass)
	{
		FActorSpawnParameters SpawnParams;

		FTransform SpawnTM(WeaponMesh->GetSocketLocation(MuzzleSocketName));

		ABullet* Bullet = Cast<ABullet>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, BulletClass, SpawnTM));
		if (Bullet)
		{
			ACharacter* Char = Cast<ACharacter>(GetOwner());
			if (Char)
				Bullet->Instigator = Char;
			Bullet->SetOwner(this);

			Bullet->InitVelocity(AimDir()*MaxRange);

			UGameplayStatics::FinishSpawningActor(Bullet, SpawnTM);
		}
	}


}
FVector AFireArmWeaponBase::AimDir()
{
	
	if (GetOwner())
	{
		APawn* P = Cast<APawn>(GetOwner());
		return P->GetBaseAimRotation().Vector();
	}
	return{ 0,0,0 };

}


