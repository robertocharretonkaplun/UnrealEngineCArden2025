#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/UserDefinedEnum.h"
#include "PathModule.h"
#include "AIBehaviorComponent.generated.h"

USTRUCT(BlueprintType)
struct FPathConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaitTime = 0.f;
};


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EUCARDEN_API UAIBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAIBehaviorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, 
	FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPCConfig")
	TMap<APathModule*, FPathConfig> PointConfigs;
};
