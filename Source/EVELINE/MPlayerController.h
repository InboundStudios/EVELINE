// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EVELINE_API AMPlayerController : public APlayerController
{
	GENERATED_BODY()
	void SetupInputComponent() override;
private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void StartJump();
	void StopJump();
	void StartSprint();
	void StopSprint();
	class AMPlayerCharacter* PlayerRef;
	
	
};
