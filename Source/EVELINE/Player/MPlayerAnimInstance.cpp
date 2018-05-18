// Fill out your copyright notice in the Description page of Project Settings.

#include "MPlayerAnimInstance.h"
#include "MPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMPlayerAnimInstance::UpdateAnimationProporties()
{
	AMPlayerCharacter* Player = Cast<AMPlayerCharacter>(TryGetPawnOwner());
	if (Player)
	{
		bIsFalling = Player->GetMovementComponent()->IsFalling();
		bIsSprinting = Player->GetPressedSprint();
		//MovementSpeed = Player->GetVelocity().Size();
		//Direction = CalculateDirection(Player->GetVelocity(), Player->GetControlRotation());
		bHasGun = Player->HasGun();
	}
}

