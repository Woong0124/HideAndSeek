// Fill out your copyright notice in the Description page of Project Settings.


#include "BushComponent.h"
#include "ParentPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "HideAndSeekGameModeBase.h"
#include "Kismet/GameplayStatics.h"

UBushComponent::UBushComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SphereRadius = 150.f;
	SetHiddenInGame(true);

	MyOwner = Cast<AParentPlayer>(GetOwner());

	
}

void UBushComponent::BeginPlay()
{

}

void UBushComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	
}

// 캐릭터 컨트롤러를 받아 폰의 오너를 구한다
// 폰의 오너가 부쉬에 있다면 폰의 오너와 오버랩된 모든 캐릭터들의 매쉬를 자기 클라이언트에서만 켜게함으로써 나만 볼 수 있게 해준다
// 폰의 오너가 부쉬에서 나와있고 오버랩된 상대방은 부쉬에 있는 상태라면 상대 캐릭터들의 매쉬를 나는 볼 수 없게 해준다
void UBushComponent::SetBushOwnerSee_Implementation()
{
	AController* GetMyOwner = Cast<AController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	AParentPlayer* Player = Cast<AParentPlayer>(
		GetMyOwner->GetPawn());
	

	if (Player != nullptr)
	{
		if (Player->InBush == true)
		{
			Player->GetOverlappingActors(OverlapParentPlayerArr, AParentPlayer::StaticClass());
			for (auto OverlapActor : OverlapParentPlayerArr)
			{
				AParentPlayer* OverlapPlayer = Cast<AParentPlayer>(OverlapActor);

				if (OverlapPlayer != nullptr && OverlapPlayer != MyOwner &&
					MyOwner->IsOverlappingActor(OverlapPlayer))
				{
					if (OverlapPlayer->GetMesh()->bOnlyOwnerSee == true)
					{
						OverlapPlayer->GetMesh()->bOnlyOwnerSee = false;
					}
				}
			}
		}

		if (Player->InBush == false)
		{
			for (auto OverlapActor : OverlapParentPlayerArr)
			{
				AParentPlayer* OverlapPlayer = Cast<AParentPlayer>(OverlapActor);
				if (OverlapPlayer != nullptr && OverlapPlayer != MyOwner)
				{
					if (OverlapPlayer->InBush == true && OverlapPlayer->GetMesh()->bOnlyOwnerSee == false)
					{
						OverlapPlayer->GetMesh()->bOnlyOwnerSee = true;
					}
				}
			}
		}
	}
}

void UBushComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	SetBushOwnerSee();

}