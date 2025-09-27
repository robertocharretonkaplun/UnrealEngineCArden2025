// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle.h"

// Sets default values
AVehicle::AVehicle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VehicleColor = FColor::White;
	Speed = 100.0f;
}

// Called when the game starts or when spawned
void AVehicle::BeginPlay()
{
	Super::BeginPlay();
	Move();
}

// Called every frame
void AVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVehicle::Move()
{
	// Implement movement logic here
	UE_LOG(LogTemp, Warning, TEXT("The vehicle is moving at speed: %f"), Speed);
}