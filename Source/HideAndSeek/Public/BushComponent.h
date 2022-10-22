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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Get Owner
	UPROPERTY()
		class AParentPlayer* MyOwner;

	// Overlapping ParentPlayer Array
	UPROPERTY()
		TArray<AActor*> OverlapParentPlayerArr;

	// Running mesh settings on the client
	UFUNCTION(Client, Reliable)
		void SetBushOwnerSee();
		void SetBushOwnerSee_Implementation();
};
