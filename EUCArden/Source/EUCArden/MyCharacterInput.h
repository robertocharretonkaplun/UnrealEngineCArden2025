#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"          // Para FInputActionValue
#include "MyCharacterInput.generated.h"

// Forward declarations
class UInputAction;
class UInputMappingContext;
class UEnhancedInputComponent;

UCLASS()
class EUCARDEN_API AMyCharacterInput : public ACharacter
{
  GENERATED_BODY()

public:
  AMyCharacterInput();

protected:
  virtual void BeginPlay() override;

public:
  virtual void Tick(float DeltaTime) override;
  virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

  void Interact(const FInputActionValue& Value);

private:
  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
  UInputMappingContext* DefaultMappingContext = nullptr;

  UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
  UInputAction* InteractAction = nullptr;
};
