// Fill out your copyright notice in the Description page of Project Settings.

#include "MPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

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

