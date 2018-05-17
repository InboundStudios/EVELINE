// Fill out your copyright notice in the Description page of Project Settings.

#include "MPlayerCharacter.h"
#include "MPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/World.h"
#include "Interactable.h"

// Sets default values
AMPlayerCharacter::AMPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	TPSCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPSCamera"));
	TPSCamera->AttachToComponent(CameraBoom, FAttachmentTransformRules::KeepWorldTransform);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

// Called when the game starts or when spawned
void AMPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Controller && Controller->IsLocalController())
	{
		
		HandleHighlight();
	}
}

// Called to bind functionality to input
void AMPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AMPlayerCharacter::SetPressedJump(const bool& Value)
{
	bPressedJump = Value;
}
void AMPlayerCharacter::SetPressedSprint(const bool& Value)
{
	bPressedSprint = Value;
}
void AMPlayerCharacter::HandleHighlight()
{
	AActor* UsableActor = FindFocusedActor();
	IInteractable* Usable = Cast<IInteractable>(UsableActor);
	if (FocusedInterface != Usable)
	{
		if (FocusedInterface)
		{
			FocusedInterface->Execute_OnEndFocus(FocusedActor);
		}
		bHasNewFocus = true;
	}
	FocusedInterface = Usable;
	FocusedActor = UsableActor;
	if (Usable)
	{
		if (bHasNewFocus)
		{
			Usable->Execute_OnBeginFocus(UsableActor);
			bHasNewFocus = false;
		}
	}
}
AActor* AMPlayerCharacter::FindFocusedActor()
{
	FVector CamLoc;
	FRotator CamRot;

	if (Controller == nullptr)
		return nullptr;

	Controller->GetPlayerViewPoint(CamLoc, CamRot);
	const FVector TraceStart = CamLoc;
	const FVector Direction = CamRot.Vector();
	const FVector TraceEnd = TraceStart + (Direction * InteractionDistance);

	FCollisionQueryParams TraceParams(TEXT("TraceUsableActor"), true, this);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = false;

	/* Not tracing complex uses the rough collision instead making tiny objects easier to select. */
	TraceParams.bTraceComplex = false;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, TraceParams);

	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f);
	
	return Hit.GetActor();
}