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

	BushMesh->OnComponentBeginOverlap.AddDynamic(this, &ABushActor::MeshVisible);
	BushMesh->OnComponentEndOverlap.AddDynamic(this, &ABushActor::MeshUnVisible);
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

// Bush In
void ABushActor::MeshVisible(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AParentPlayer* OverlapPlayer = Cast<AParentPlayer>(OtherActor);

	if (OverlapPlayer != nullptr)
	{
		if (BushMesh->IsOverlappingComponent(OverlapPlayer->GetCapsuleComponent()) == true)
		{
			OverlapPlayer->GetMesh()->SetRenderCustomDepth(true);
			OverlapPlayer->GetMesh()->SetOnlyOwnerSee(true);
			OverlapPlayer->InBush = true;
		}
	}
}

// Bush Out
void ABushActor::MeshUnVisible(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndext)
{
	AParentPlayer* OverlapPlayer = Cast<AParentPlayer>(OtherActor);

	if (OverlapPlayer != nullptr)
	{
		if (BushMesh->IsOverlappingComponent(OverlapPlayer->GetCapsuleComponent()) == false)
		{
			OverlapPlayer->GetMesh()->SetRenderCustomDepth(false);
			OverlapPlayer->GetMesh()->SetOnlyOwnerSee(false);
			OverlapPlayer->InBush = false;
			
		}
	}
}
