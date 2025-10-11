// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformActor.h"
#include "Components/BoxComponent.h"
// Sets default values
APlatformActor::APlatformActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and set up the static mesh component
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	
	// Initialize variables
	MovementSpeed = 100.0f;	
	MovementAmplitud = 500.0f;
	bMovingRight = true;
	
	// Establecer Collisiones
	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	CollisionComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetBoxExtent(FVector(1.0f, 1.0f, 1.0f));
	CollisionComponent->SetCollisionProfileName("BlockAllDynamic");
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, 
																												 &APlatformActor::OnOverlapBegin);
}

// Called when the game starts or when spawned
void APlatformActor::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
	ChangeMaterial(DefaultMaterial);	
}

// Called every frame
void APlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentLocation = GetActorLocation();
	float DeltaMovement = MovementSpeed * DeltaTime;

	// Validar el movimiento en la direccion deseada
	if (bMovingRight)
	{
		CurrentLocation.Y += DeltaMovement;
		if (CurrentLocation.Y >= InitialLocation.Y + MovementAmplitud)
		{
			bMovingRight = false;
		}
	}
	else
	{
		CurrentLocation.Y -= DeltaMovement;
		if (CurrentLocation.Y <= InitialLocation.Y - MovementAmplitud)
		{
			bMovingRight = true;
		}
	}
	SetActorLocation(CurrentLocation);

	//DrawDebugLine(GetWorld(), 
	//							InitialLocation, 
	//							CurrentLocation, 
	//							FColor::Green, 
	//							false, 
	//							-1.0f, 
	//							0, 
	//							5.0f);

	DrawDebugLine(GetWorld(), 
		InitialLocation - FVector(0, MovementAmplitud, 0), 
		InitialLocation + FVector(0, MovementAmplitud, 0), FColor::Yellow, false, -1, 0, 2);

}

void 
APlatformActor::ChangeMaterial(UMaterialInterface* NewMaterial) {
	if (NewMaterial && MeshComponent) {
		MeshComponent->SetMaterial(0, NewMaterial);
	}
}

void 
APlatformActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, 
															 AActor* OtherActor, 
															 UPrimitiveComponent* OtherComp, 
															 int32 OtherBodyIndex, 
															 bool bFromSweep, 
															 const FHitResult& SweepResult) {
	if (OtherActor && (OtherActor != this) && OtherComp) {
		Destroy();
	}

}

