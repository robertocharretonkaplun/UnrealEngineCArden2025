#include "MyCharacterInput.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputTriggers.h"

AMyCharacterInput::AMyCharacterInput()
{
  PrimaryActorTick.bCanEverTick = true;
}

void AMyCharacterInput::BeginPlay()
{
  Super::BeginPlay();

  if (APlayerController* PC = Cast<APlayerController>(GetController()))
  {
    if (ULocalPlayer* LP = PC->GetLocalPlayer())
    {
      if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
      {
        if (DefaultMappingContext)
        {
          Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
        else
        {
          UE_LOG(LogTemp, Warning, TEXT("DefaultMappingContext no asignado en %s"), *GetName());
        }
      }
    }
  }
}

void AMyCharacterInput::Tick(float DeltaTime)
{
  Super::Tick(DeltaTime);
}

void AMyCharacterInput::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
  Super::SetupPlayerInputComponent(PlayerInputComponent);

  if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
  {
    if (InteractAction)
    {
      EIC->BindAction(InteractAction, ETriggerEvent::Started, this, &AMyCharacterInput::Interact);
      EIC->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMyCharacterInput::Interact);
    }
    else
    {
      UE_LOG(LogTemp, Warning, TEXT("InteractAction no asignado en %s"), *GetName());
    }
  }
  else
  {
    UE_LOG(LogTemp, Error, TEXT("Failed to find Enhanced Input component on %s"), *GetName());
  }
}

void AMyCharacterInput::Interact(const FInputActionValue& Value)
{
  UE_LOG(LogTemp, Log, TEXT("Interact!"));
  GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Interact!"));
}
