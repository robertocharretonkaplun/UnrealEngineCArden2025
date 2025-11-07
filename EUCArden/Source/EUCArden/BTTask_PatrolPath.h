#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PatrolPath.generated.h"

class AAIController;
class APathModule;
class UAIBehaviorComponent;

/**
 * Recorre en orden las claves del PointConfigs (APathModule*) del AIBehaviorComponent.
 * Se mueve al actor, espera WaitTime y pasa al siguiente (loop).
 */
UCLASS()
class EUCARDEN_API UBTTask_PatrolPath : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_PatrolPath();

	/** Radio de aceptación del MoveTo (cm) */
	UPROPERTY(EditAnywhere, Category = "Patrol")
	float AcceptanceRadius = 50.f;

	/** Espera mínima por punto (seg), capea valores muy bajos */
	UPROPERTY(EditAnywhere, Category = "Patrol")
	float MinWaitSeconds = 0.1f;

	/** ¿Repetir al llegar al final? */
	UPROPERTY(EditAnywhere, Category = "Patrol")
	bool bLoop = true;

	/** Índice inicial dentro de las claves */
	UPROPERTY(EditAnywhere, Category = "Patrol")
	int32 StartIndex = 0;

	// BT overrides
	virtual EBTNodeResult::Type 
	ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type 
	AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	// Guardamos refs vivas/seguras para el callback
	UPROPERTY(Transient) TObjectPtr<AAIController> AICon = nullptr;
	UPROPERTY(Transient) TObjectPtr<APawn> ControlledPawn = nullptr;
	UPROPERTY(Transient) TObjectPtr<UAIBehaviorComponent> BehaviorComp = nullptr;

	/** Referencia segura al BT que inició la task (NO pasar &OwnerComp al delegate) */
	TWeakObjectPtr<UBehaviorTreeComponent> OwnerBTWeak;

	/** Claves (puntos) extraídas de PointConfigs: DEBE coincidir con la clave del TMap */
	TArray<APathModule*> Keys;
	int32 CurrentIndex = 0;

	FTimerHandle WaitTimerHandle;
	FDelegateHandle MoveFinishedHandle;

	// Flujo
	void StartCycle();
	void MoveToCurrent();
	void HandleMoveFinished(FAIRequestID RequestID, const struct FPathFollowingResult& Result);
	void OnEndWait();

	// Limpieza
	void ClearDelegatesAndTimers();
};
