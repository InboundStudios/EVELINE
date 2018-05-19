// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTaskMeleeEnemyAttack.h"
#include "EVELINE.h"
#include "AI/Controllers/BaseAIController.h"
#include "AI/Characters/MeleeEnemyCharacterBase.h"
#include "AI/Characters/BaseEnemyCharacter.h"
#include "Player/MPlayerCharacter.h"


EBTNodeResult::Type UBTTaskMeleeEnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	ABaseAIController* AICon = Cast<ABaseAIController>(OwnerComp.GetAIOwner());

	if (AICon)
	{
		ABaseEnemyCharacter* Char = Cast<ABaseEnemyCharacter>(AICon->GetPawn());
		AMPlayerCharacter* MainChar = Cast<AMPlayerCharacter>(AICon->GetCurrentTarget());
		

		if ((Char && MainChar &&MainChar->IsAlive()))
		{
			Char->Attack();
		}
		else
		{
			AICon->UnPossess();
			return EBTNodeResult::Aborted;
		}

	}
	return EBTNodeResult::Succeeded;
}

