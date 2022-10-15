// Fill out your copyright notice in the Description page of Project Settings.


#include "BushActor.h"
#include "ParentPlayer.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABushActor::ABushActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh
	BushMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = BushMesh;
	ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh_Mesh(TEXT("StaticMesh'/Game/__Woong/Meshes/SM_GrassFull.SM_GrassFull'"));
	BushMesh->SetStaticMesh(Mesh_Mesh.Object);
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
	AParentPlayer* OverlapPlayer = Cast<AParentPlayer>(OtherActor);

	if (OverlapPlayer != nullptr)
	{
		OverlapPlayer->GetMesh()->SetRenderCustomDepth(true);
		OverlapPlayer->GetMesh()->SetOnlyOwnerSee(true);
		OverlapPlayer->IsHide = true;
	}

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, OverlapPlayer->GetFName().ToString());

	UE_LOG(LogTemp, Log, TEXT("%s"), OverlapPlayer->IsHide ? TEXT("true" : TEXT("false")));
}

void ABushActor::MeshUnVisible(AActor* OverlappedActor, AActor* OtherActor)
{
	// ParentPlayer에 형변환해서 맞으면 매쉬 visible
	AParentPlayer* OverlapPlayer = Cast<AParentPlayer>(OtherActor);

	if (OverlapPlayer != nullptr)
	{
		OverlapPlayer->GetMesh()->SetRenderCustomDepth(false);
		OverlapPlayer->GetMesh()->SetOnlyOwnerSee(false);
		OverlapPlayer->IsHide = false;
	}

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, OverlapPlayer->GetFName().ToString());

	UE_LOG(LogTemp, Log, TEXT("%s"), OverlapPlayer->IsHide ? TEXT("true" : TEXT("false")));
}
