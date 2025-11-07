#include "BTTask_PatrolPath.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "GameFramework/Pawn.h"
#include "TimerManager.h"
#include "AIBehaviorComponent.h"   
#include "PathModule.h"       

UBTTask_PatrolPath::UBTTask_PatrolPath()
{
	NodeName = TEXT("Patrol Path (PointConfigs)");
	bCreateNodeInstance = true; // mantiene estado por ejecución
}

EBTNodeResult::Type 
UBTTask_PatrolPath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* /*NodeMemory*/)
{
	OwnerBTWeak = &OwnerComp;

	AICon = OwnerComp.GetAIOwner();
	if (!AICon) return EBTNodeResult::Failed;

	ControlledPawn = AICon->GetPawn();
	if (!ControlledPawn) return EBTNodeResult::Failed;

	BehaviorComp = ControlledPawn->FindComponentByClass<UAIBehaviorComponent>();
	if (!BehaviorComp) return EBTNodeResult::Failed;

	if (BehaviorComp->PointConfigs.Num() == 0) return EBTNodeResult::Failed;

	// Tomar las claves (APathModule*) del mapa
	Keys.Reset();
	BehaviorComp->PointConfigs.GenerateKeyArray(Keys);

	// Sanear nulos
	Keys.RemoveAll([](APathModule* M) { return !IsValid(M); });
	if (Keys.Num() == 0) return EBTNodeResult::Failed;

	CurrentIndex = (StartIndex >= 0) ? (StartIndex % Keys.Num()) : 0;

	StartCycle();
	return EBTNodeResult::InProgress;
}

void 
UBTTask_PatrolPath::StartCycle()
{
	MoveToCurrent();
}

void 
UBTTask_PatrolPath::MoveToCurrent()
{
	// Validaciones mínimas
	if (!AICon || Keys.Num() == 0)
	{
		if (auto* BT = OwnerBTWeak.Get()) { FinishLatentTask(*BT, EBTNodeResult::Failed); }
		return;
	}

	APathModule* Target = Keys[CurrentIndex];
	if (!IsValid(Target))
	{
		if (auto* BT = OwnerBTWeak.Get()) { FinishLatentTask(*BT, EBTNodeResult::Failed); }
		return;
	}

	const FVector Dest = Target->GetActorLocation();

	FAIMoveRequest Req;
	Req.SetGoalLocation(Dest);
	Req.SetAcceptanceRadius(AcceptanceRadius);
	Req.SetReachTestIncludesAgentRadius(true);
	Req.SetUsePathfinding(true);   
	Req.SetAllowPartialPath(true);

	FNavPathSharedPtr OutPath;
	AICon->MoveTo(Req, &OutPath);

	if (UPathFollowingComponent* PFC = AICon->GetPathFollowingComponent())
	{
		// quitar bind previo si lo hubiera
		if (MoveFinishedHandle.IsValid())
		{
			PFC->OnRequestFinished.Remove(MoveFinishedHandle);
			MoveFinishedHandle.Reset();
		}

		// ¡OJO! No pasar &OwnerComp como payload. Usar OwnerBTWeak dentro del handler.
		MoveFinishedHandle = PFC->OnRequestFinished.AddUObject(
			this, &UBTTask_PatrolPath::HandleMoveFinished);
	}
}

void 
UBTTask_PatrolPath::HandleMoveFinished(FAIRequestID /*RequestID*/, 
																			 const FPathFollowingResult& Result)
{
	UBehaviorTreeComponent* BT = OwnerBTWeak.Get();
	if (!BT) return;

	if (!Result.IsSuccess())
	{
		ClearDelegatesAndTimers();
		FinishLatentTask(*BT, EBTNodeResult::Failed);
		return;
	}

	// Buscar WaitTime en el mapa del BehaviorComp
	APathModule* CurrentModule = Keys[CurrentIndex];
	float WaitTime = MinWaitSeconds;

	if (BehaviorComp && CurrentModule)
	{
		if (const FPathConfig* Cfg = BehaviorComp->PointConfigs.Find(CurrentModule))
		{
			WaitTime = FMath::Max(Cfg->WaitTime, MinWaitSeconds);
		}
	}

	if (UWorld* World = BT->GetWorld())
	{
		World->GetTimerManager().SetTimer(
			WaitTimerHandle,
			this, &UBTTask_PatrolPath::OnEndWait,
			WaitTime,
			false
		);
	}
	else
	{
		FinishLatentTask(*BT, EBTNodeResult::Failed);
	}
}

void 
UBTTask_PatrolPath::OnEndWait()
{
	UBehaviorTreeComponent* BT = OwnerBTWeak.Get();
	if (!BT) return;

	// avanzar índice y wrap
	++CurrentIndex;
	if (CurrentIndex >= Keys.Num())
	{
		if (bLoop) CurrentIndex = 0;
		else
		{
			ClearDelegatesAndTimers();
			FinishLatentTask(*BT, EBTNodeResult::Succeeded);
			return;
		}
	}

	MoveToCurrent();
}

EBTNodeResult::Type 
UBTTask_PatrolPath::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* /*NodeMemory*/)
{
	ClearDelegatesAndTimers();
	if (AICon) AICon->StopMovement();
	return EBTNodeResult::Aborted;
}

void 
UBTTask_PatrolPath::ClearDelegatesAndTimers()
{
	if (AICon)
	{
		if (UPathFollowingComponent* PFC = AICon->GetPathFollowingComponent())
		{
			if (MoveFinishedHandle.IsValid())
			{
				PFC->OnRequestFinished.Remove(MoveFinishedHandle);
				MoveFinishedHandle.Reset();
			}
		}
	}

	if (UBehaviorTreeComponent* BT = OwnerBTWeak.Get())
	{
		if (UWorld* World = BT->GetWorld())
		{
			World->GetTimerManager().ClearTimer(WaitTimerHandle);
		}
	}
}
