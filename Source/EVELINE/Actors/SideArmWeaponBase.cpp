// Fill out your copyright notice in the Description page of Project Settings.

#include "SideArmWeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Player/MPlayerCharacter.h"

void ASideArmWeaponBase::StartFire_Implementation()
{
	bIsAttacking = true;
}
void ASideArmWeaponBase::StopFire_Implementation()
{
	bIsAttacking = false;
}
void ASideArmWeaponBase::OnInteract_Implementation(AActor* Caller)
{

}
void ASideArmWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsAttacking)
		DealDamage();
}
void ASideArmWeaponBase::DealDamage()
{
	FVector UpperSphereSocketLocation = WeaponMesh->GetSocketLocation(UpperSphereSocket);
	FVector LowerSphereSocketLocation = WeaponMesh->GetSocketLocation(LowerSphereSocket);

	FVector CenterOfRaycast = ((UpperSphereSocketLocation - LowerSphereSocketLocation) / 2) + LowerSphereSocketLocation;
	TArray<FHitResult> HitResults;


	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(AttackRaycastRadius);


	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);


	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	bool bHasHitActors = GetWorld()->SweepMultiByObjectType(HitResults, LowerSphereSocketLocation, UpperSphereSocketLocation, FQuat::Identity, ObjectQueryParams, CollisionShape, CollisionQueryParams);

	if (bHasHitActors)
	{
		for (auto It = HitResults.CreateIterator(); It; It++)
		{
			if ((*It).GetActor()) {
				float DealtDamage = BaseDamage;
				FVector ShotDir = GetActorLocation() - (*It).ImpactPoint;

				FPointDamageEvent DamageEvent;
				DamageEvent.Damage = DealtDamage;
				DamageEvent.HitInfo = *It;
				DamageEvent.ShotDirection = ShotDir;
				DamageEvent.ShotDirection.Normalize();
				ACharacter* Char = Cast<ACharacter>(GetOwner());
				if (Char)
					(*It).GetActor()->TakeDamage(DealtDamage, DamageEvent, Char->GetController(), this);
			}
		}
	}

}
void ASideArmWeaponBase::SetIsAttacking(bool Value)
{
	bIsAttacking = Value;
}

