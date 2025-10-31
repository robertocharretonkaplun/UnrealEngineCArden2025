// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIC_NPC.generated.h"

/**
 * 
 */
UCLASS()
class EUCARDEN_API AAIC_NPC : public AAIController
{
	GENERATED_BODY()
	
public:
		// Sets default values for this character's properties
	explicit AAIC_NPC(FObjectInitializer const & ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;
};
