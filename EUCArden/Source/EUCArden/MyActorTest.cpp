// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorTest.h"
#include "Engine/Engine.h"
// Sets default values
AMyActorTest::AMyActorTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyFloatVariable = 50.0f;
	edad = 26;
	esInstructor = true;
	nombre = "Roberto Charreton";
	DemostrateFundamentals();
}

// Called when the game starts or when spawned
void AMyActorTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActorTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActorTest::DemostrateFundamentals() {
	// Operadores Aritmeticos
	int32 sum = edad + 30;
	float product = MyFloatVariable * 2.5f;

	// Estructuras de Control
	if (esInstructor) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("esInstructor is true"));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("esInstructor is false"));
	}

	// Bucles o Ciclos
	for (int32 i = 0; i < 5; i++) {
		FString DEbugMessage = FString::Printf(TEXT("loop interation: %d"), i);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, DEbugMessage);
	}

	// Bucle While
	int32 count = 0;
	while (count < 3) {
		FString WhileMessage = FString::Printf(TEXT("While loop iteration: %d"), count);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Cyan, WhileMessage);
		count++;
	}
}

