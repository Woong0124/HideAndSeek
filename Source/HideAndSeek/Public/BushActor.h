// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BushActor.generated.h"

UCLASS()
class HIDEANDSEEK_API ABushActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABushActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* BushMesh;

	// Overlapping ParentPlayer Array
	UPROPERTY()
		TArray<AActor*> OverlapParentPlayerArr;

	// When the end overlap
	UFUNCTION()
		virtual void MeshUnVisible(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndext);

	// Bush In Player 
	UFUNCTION(NetMulticast, Reliable)
		void BushInServer(AParentPlayer* Player);
		void BushInServer_Implementation(AParentPlayer* Player);

	// Bush Out Player
	UFUNCTION(NetMulticast, Reliable)
		void BushOutServer(AParentPlayer* Player);
		void BushOutServer_Implementation(AParentPlayer* Player);
};
