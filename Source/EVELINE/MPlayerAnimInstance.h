// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class EVELINE_API UMPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
private:
	UPROPERTY( BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool bIsSprinting;
	UPROPERTY( BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool bIsFalling;
	UPROPERTY( BlueprintReadWrite,meta=(AllowPrivateAccess="true"))
		float Direction;
	UPROPERTY( BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float MovementSpeed;
	UFUNCTION(BlueprintCallable, Category = AnimationUpdates)
		void UpdateAnimationProporties();
	
	
	
};
