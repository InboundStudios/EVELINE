// Fill out your copyright notice in the Description page of Project Settings.

#include "MPlayerController.h"
#include "MPlayerCharacter.h"
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
	else if (PlayerRef)
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
	else if (PlayerRef)
	{
		PlayerRef->SetPressedSprint(false);
		PlayerRef->GetCharacterMovement()->MaxWalkSpeed = PlayerRef->GetWalkSpeed();
	}
}