// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}
void AWeaponBase::OnBeginFocus_Implementation()
{
	StaticMesh->SetRenderCustomDepth(true);
	WeaponMesh->SetRenderCustomDepth(true);
}
void AWeaponBase::OnEndFocus_Implementation()
{
	StaticMesh->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);
}
void AWeaponBase::StartFire_Implementation()
{

}
void AWeaponBase::StopFire_Implementation()
{

}
