// Fill out your copyright notice in the Description page of Project Settings.


#include "AIC_NPC.h"
#include "C_NPC.h"
// Sets default values for this character's properties

AAIC_NPC::AAIC_NPC(FObjectInitializer const& ObjectInitializer)
{
}

void AAIC_NPC::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if(AC_NPC* const NPC = Cast<AC_NPC>(InPawn))
	{
		if (UBehaviorTree* const tree = NPC->GetBehaviorTree())
		{
			UBlackboardComponent* bloackboard;
			UseBlackboard(tree->BlackboardAsset, bloackboard);
			Blackboard = bloackboard;
			RunBehaviorTree(tree);
		}
	}
}


