// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Interactable.generated.h"
/**
 * 
 */
UINTERFACE(BlueprintType)
class EVELINE_API UInteractable : public UInterface
{
	 GENERATED_BODY()
};

class EVELINE_API IInteractable
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interact)
		void OnInteract(AActor* Caller);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interact)
		void OnBeginFocus();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Interact)
		void OnEndFocus();
};
