// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "InteractableActor.generated.h"

UCLASS()
class EVELINE_API AInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
		FName ItemName;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interact)
		void OnInteract(AActor* Caller);
	virtual void OnInteract_Implementation(AActor* Caller) override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interact)
		void OnBeginFocus();
	virtual void OnBeginFocus_Implementation() override;
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interact)
		void OnEndFocus();
	virtual void OnEndFocus_Implementation() override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* StaticMesh;
	
	
};
