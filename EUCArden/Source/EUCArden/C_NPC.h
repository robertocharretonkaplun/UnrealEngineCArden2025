#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviorTree\BehaviorTree.h"
#include "AIBehaviorComponent.h"
#include "C_NPC.generated.h"

UCLASS()
class EUCARDEN_API AC_NPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AC_NPC();

	UBehaviorTree* GetBehaviorTree() const { return  Tree; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* Tree;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAIBehaviorComponent> AIBehaviorComp;
};
