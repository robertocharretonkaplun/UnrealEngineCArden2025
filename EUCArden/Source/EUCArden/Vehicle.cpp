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
	print();
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

void AVehicle::InitializeVehicle()
{
	Passengers = { 1, 2, 3 };
	Cargo.Add("Boxes", 150.0f);
	Features = { "Air Conditioning", "Sunroof", "GPS" };

	UE_LOG(LogTemp, Warning, TEXT("Vehicle %s initialized."), *VehicleName);
	UE_LOG(LogTemp, Warning, TEXT("Vehicle Data:"));
	for(int32 Passenger : Passengers)
	{
		UE_LOG(LogTemp, Warning, TEXT("Passenger ID: %d"), Passenger);
	}
	for(const TPair<FString, float>& Item : Cargo)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cargo Item: %s, Weight: %f"), *Item.Key, Item.Value);
	}
	for(const FString& Feature : Features)
	{
		UE_LOG(LogTemp, Warning, TEXT("Feature: %s"), *Feature);
	}

}
