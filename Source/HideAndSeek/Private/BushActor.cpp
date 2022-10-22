// Fill out your copyright notice in the Description page of Project Settings.


#include "BushActor.h"
#include "ParentPlayer.h"
#include "Components/CapsuleComponent.h"

#define BushStaticMesh "StaticMesh'/Game/__Woong/Meshes/SM_GrassFull.SM_GrassFull'"
#define SetCollisionName "OverlapAllDynamic"

// Sets default values
ABushActor::ABushActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Mesh Setting
	BushMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = BushMesh;
	ConstructorHelpers::FObjectFinder<UStaticMesh> BushMesh_Mesh(TEXT(BushStaticMesh));
	BushMesh->SetStaticMesh(BushMesh_Mesh.Object);
	BushMesh->SetCollisionProfileName(SetCollisionName);

	// EndOverlap Delegate
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

	// 오버랩된 ParentPlayer가 있다면 해당 캐릭터를 BushIn상태로 만듬
	GetOverlappingActors(OverlapParentPlayerArr, AParentPlayer::StaticClass());
	for (auto OverlapActor : OverlapParentPlayerArr)
	{
		AParentPlayer* OverlapPlayer = Cast<AParentPlayer>(OverlapActor);

		if (OverlapPlayer != nullptr)
		{
			if (BushMesh->IsOverlappingComponent(OverlapPlayer->GetCapsuleComponent()) == true)
			{
				OverlapPlayer->GetMesh()->SetRenderCustomDepth(true);
				BushInServer(OverlapPlayer);
			}
		}
	}
}

void ABushActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


}

// ParentPlayer가 EndOverlap 되었을 때 캐릭터를 Bush Out 상태로 만듬
void ABushActor::MeshUnVisible(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndext)
{
	AParentPlayer* OverlapPlayer = Cast<AParentPlayer>(OtherActor);

	if (OverlapPlayer != nullptr)
	{
		if (BushMesh->IsOverlappingComponent(OverlapPlayer->GetCapsuleComponent()) == false)
		{
			OverlapPlayer->GetMesh()->SetRenderCustomDepth(false);
			BushOutServer(OverlapPlayer);
			
		}
	}
}

// 모든 클라이언트에서 매쉬를 끈다
void ABushActor::BushInServer_Implementation(AParentPlayer* Player)
{
	Player->InBush = true;
	Player->GetMesh()->SetOnlyOwnerSee(true);
}

// 모든 클라이언트에서 매쉬를 켠다
void ABushActor::BushOutServer_Implementation(AParentPlayer* Player)
{
	Player->InBush = false;
	Player->GetMesh()->SetOnlyOwnerSee(false);
}
