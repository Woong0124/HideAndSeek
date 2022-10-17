// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "BushComponent.generated.h"

/**
 * 
 */
UCLASS()
class HIDEANDSEEK_API UBushComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:
	UBushComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
		class AParentPlayer* MyOwner;

	UPROPERTY()
		TArray<AActor*> PlayerArr;

	UPROPERTY()
		TArray<AActor*> BushArr;

	UFUNCTION()
		void BushInFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void BushOutFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
