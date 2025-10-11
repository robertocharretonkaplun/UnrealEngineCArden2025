// Fill out your copyright notice in the Description page of Project Settings.


#include "TransformModifier.h"

// Sets default values
ATransformModifier::ATransformModifier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATransformModifier::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	DrawDSphere();
}

// Called when the game starts or when spawned
void ATransformModifier::BeginPlay()
{
	Super::BeginPlay();
	// Vincular al Actor seleccionado con el transform
	if (TargetActor) {
		NewTransform = TargetActor->GetActorTransform();
	}
	else {
		TargetActor = nullptr;
	}
	// Inicializar el índice de la posición actual
	if (Positions.Num() > 0) {
		MoveToNextPosition();
	}
}

// Called every frame
void ATransformModifier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ModifyTargetTransform(DeltaTime);
}

void ATransformModifier::ModifyTargetTransform(float DeltaTime)
{
	//if (TargetActor) {
	//	TargetActor->SetActorTransform(NewTransform);
	//}

	if (Positions.Num() == 0) {
		return;
	}
	FVector CurrentPosition = TargetActor->GetActorLocation();
	FVector TargetPosition = Positions[CurrentPositionIndex];

	// Move Towards the target position
	FVector Direction = (TargetPosition - CurrentPosition).GetSafeNormal();
	FVector NewPosition = CurrentPosition + Direction * 100 * DeltaTime;

	TargetActor->SetActorLocation(NewPosition);

	// Check if we are close enough to the target position to consider we reached it
	if (FVector::Dist(NewPosition, TargetPosition) < 10.0f) {
		CurrentPositionIndex++;
		ChangeMaterial();
		if (CurrentPositionIndex >= Positions.Num()) {
			CurrentPositionIndex = 0; // Reset to the first position
		}
	}
}

void ATransformModifier::MoveToNextPosition()
{
	if (TargetActor && Positions.IsValidIndex(CurrentPositionIndex)) {
		FVector TargetPosition = Positions[CurrentPositionIndex];
		TargetActor->SetActorLocation(TargetPosition);
	}
}

void ATransformModifier::ChangeMaterial()
{
}

void ATransformModifier::DrawDSphere() const
{
	for(const FVector& Position : Positions) {
		DrawDebugSphere(
			GetWorld(),
			Position,
			50.0f, // Radius
			12, // Segments
			FColor::Red,
			false, // Persistent (will stay for a while)
			-1.0f, // Lifetime (negative means persistent)
			0, // Depth Priority
			5.0f // Thickness
		);
	}
}

