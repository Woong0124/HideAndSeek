// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemActor.h"
#include "ItemBase.h"

#define Spawn01Location 500.f,500.f,50.f
#define Spawn02Location 500.f,-500.f,50.f

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	SpawnScene01 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn01"));
	SpawnScene01->AttachToComponent(RootScene, FAttachmentTransformRules::SnapToTargetIncludingScale);

	SpawnScene02 = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn02"));
	SpawnScene02->AttachToComponent(RootScene, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	// 아이템 스폰될 월드 좌표 설정
	SpawnScene01->SetWorldLocation(FVector(Spawn01Location));
	SpawnScene02->SetWorldLocation(FVector(Spawn02Location));

	GetWorld()->SpawnActor<AItemBase>(AItemBase::StaticClass(), SpawnScene01->GetComponentLocation(), FRotator(0.f, 0.f, 0.f));
	GetWorld()->SpawnActor<AItemBase>(AItemBase::StaticClass(), SpawnScene02->GetComponentLocation(), FRotator(0.f, 0.f, 0.f));
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

