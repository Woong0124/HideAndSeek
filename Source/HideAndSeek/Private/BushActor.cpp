// Fill out your copyright notice in the Description page of Project Settings.


#include "BushActor.h"

// Sets default values
ABushActor::ABushActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh
	BushMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = BushMesh;
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh_Mesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	BushMesh->SetStaticMesh(Mesh_Mesh.Object);
	ConstructorHelpers::FObjectFinder<UMaterial> MeshMaterial(TEXT("Material'/Game/StarterContent/Props/Materials/M_Bush.M_Bush'"));
	BushMesh->SetMaterial(0, MeshMaterial.Object);
	BushMesh->SetCollisionProfileName("OverlapAllDynamic");

	// Overlap Player Visible On/Off
	OnActorBeginOverlap.AddDynamic(this, &ABushActor::MeshVisible);
	OnActorEndOverlap.AddDynamic(this, &ABushActor::MeshUnVisible);
}

// Called when the game starts or when spawned
void ABushActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABushActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABushActor::MeshVisible(AActor* OverlappedActor, AActor* OtherActor)
{
	// ParentPlayer에 형변환해서 맞으면 매쉬 unvisible
}

void ABushActor::MeshUnVisible(AActor* OverlappedActor, AActor* OtherActor)
{

}
