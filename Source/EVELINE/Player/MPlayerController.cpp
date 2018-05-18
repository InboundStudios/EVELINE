// Fill out your copyright notice in the Description page of Project Settings.

#include "MPlayerController.h"
#include "MPlayerCharacter.h"
#include "Interfaces/Interactable.h"
#include "Actors/WeaponBase.h"
#include "GameFramework/CharacterMovementComponent.h"

void AMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAxis("MoveForward", this, &AMPlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &AMPlayerController::MoveRight);
		InputComponent->BindAxis("Turn", this, &AMPlayerController::AddYawInput);
		InputComponent->BindAxis("LookUp", this, &AMPlayerController::AddPitchInput);
		InputComponent->BindAction("Jump",IE_Pressed, this, &AMPlayerController::StartJump);
		InputComponent->BindAction("Jump", IE_Released, this, &AMPlayerController::StopJump);
		InputComponent->BindAction("Sprint", IE_Pressed, this, &AMPlayerController::StartSprint);
		InputComponent->BindAction("Sprint", IE_Released, this, &AMPlayerController::StopSprint);
		InputComponent->BindAction("Use", IE_Pressed, this, &AMPlayerController::Use);
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMPlayerController::StartFire);
		InputComponent->BindAction("Fire", IE_Released, this, &AMPlayerController::StopFire);
	}
}

void AMPlayerController::MoveForward(float Value)
{
	if (!PlayerRef)
	{
		PlayerRef = Cast<AMPlayerCharacter>(GetPawn());
	}
	else
	{
		if (Value != 0.0f)
		{
			const FRotator Rotation = GetControlRotation();
			const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

			PlayerRef->AddMovementInput(Direction, Value);
		}
	}


}

void AMPlayerController::MoveRight(float Value)
{
	if (!PlayerRef)
	{
		PlayerRef = Cast<AMPlayerCharacter>(GetPawn());
	
	}
	else
	{
		if (Value != 0.0f)
		{

			FRotator Rotation = GetControlRotation();
			PlayerRef->GetCharacterMovement();
			if (PlayerRef->GetCharacterMovement()->IsMovingOnGround() || PlayerRef->GetCharacterMovement()->IsFalling())
			{
				Rotation.Pitch = 0.0f;
			}

			const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
			PlayerRef->AddMovementInput(Direction, Value);
		}
	}

}
void AMPlayerController::StartJump()
{
	if (!PlayerRef)
	{
		PlayerRef = Cast<AMPlayerCharacter>(GetPawn());

	}
	else
	{
		if (PlayerRef->GetCharacterMovement()->IsMovingOnGround())
		{
			PlayerRef->SetPressedJump(true);
			PlayerRef->GetCharacterMovement()->DoJump(true);
		}
	}
}
void AMPlayerController::StopJump()
{
	if (!PlayerRef)
	{
		PlayerRef = Cast<AMPlayerCharacter>(GetPawn());

	}
	else
	{
		PlayerRef->SetPressedJump(false);
	}
}
void AMPlayerController::StartSprint()
{
	if (!PlayerRef)
	{
		PlayerRef = Cast<AMPlayerCharacter>(GetPawn());
	}
	else
	{
		PlayerRef->SetPressedSprint(true);
		PlayerRef->GetCharacterMovement()->MaxWalkSpeed = PlayerRef->GetRunSpeed();
	}
}
void AMPlayerController::StopSprint()
{
	if (!PlayerRef)
	{
		PlayerRef = Cast<AMPlayerCharacter>(GetPawn());

	}
	else
	{
		PlayerRef->SetPressedSprint(false);
		PlayerRef->GetCharacterMovement()->MaxWalkSpeed = PlayerRef->GetWalkSpeed();
	}
}
void AMPlayerController::Use()
{
	
	if (!PlayerRef)
	{
		PlayerRef = Cast<AMPlayerCharacter>(GetPawn());
	}
	else
	{
		AActor* InteractableActor = PlayerRef->FindFocusedActor();
		IInteractable* Interactable = Cast<IInteractable>(InteractableActor);
		if (Interactable)
		{
			
			Interactable->Execute_OnInteract(InteractableActor, PlayerRef);
		}
	}
}
void AMPlayerController::StartFire()
{
	if (!PlayerRef)
	{
		PlayerRef = Cast<AMPlayerCharacter>(GetPawn());
	}
	else
	{
		if (PlayerRef->GetCurrentWeapon())
		{
			PlayerRef->GetCurrentWeapon()->StartFire();
		}
	}
}
void AMPlayerController::StopFire()
{
	if (!PlayerRef)
	{
		PlayerRef = Cast<AMPlayerCharacter>(GetPawn());
	}
	else
	{
		if (PlayerRef->GetCurrentWeapon())
		{
			PlayerRef->GetCurrentWeapon()->StopFire();
		}
	}
}