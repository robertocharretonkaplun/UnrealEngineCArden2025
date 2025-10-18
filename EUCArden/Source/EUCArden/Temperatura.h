// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Temperatura.generated.h"

UCLASS()
class EUCARDEN_API ATemperatura : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATemperatura();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Metodo para obtener la temperatura en Farenheit
	UFUNCTION(BlueprintCallable, Category = "Temperatura")
	float GetTemperatureFarenheit() const;

	UFUNCTION(BlueprintCallable, Category = "Temperatura")
	float CalculateTemperatureDifference(float Temp1, float Temp2);

	UFUNCTION(BlueprintPure, Category = "Temperatura")
	static float CalculateStaticTemperatureDifference(float Temp1, float Temp2);

	UFUNCTION(BlueprintPure, Category = "Temperatura")
	static float ConvertKelvinToCelsius(float Kelvin);

	UFUNCTION(BlueprintPure, Category = "Temperatura")
	static float CalculateAvarageTemperature(float Temp1, float Temp2);

	// Evento para checar temperatura
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Temperatura")
	void OnTemperatureChecked(float CurrentTemperature);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Función para obtener la temperatura actual en Celsius
	UPROPERTY(BlueprintReadWrite, EditAnyWhere, Category = "Temperatura")
	float TemperatureCelcius;
};
