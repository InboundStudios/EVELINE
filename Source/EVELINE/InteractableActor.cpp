// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableActor.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AInteractableActor::OnInteract_Implementation(AActor* Caller)
{
	UE_LOG(LogTemp, Warning, TEXT("USE"));
}
void AInteractableActor::OnBeginFocus_Implementation()
{
	StaticMesh->SetRenderCustomDepth(true);
}
void AInteractableActor::OnEndFocus_Implementation()
{
	StaticMesh->SetRenderCustomDepth(false);
}

