// Fill out your copyright notice in the Description page of Project Settings.


#include "BushComponent.h"
#include "ParentPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerState.h"

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

void UBushComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// 내가 부쉬에 있을 때, 나와 오버랩된 플레이어가 부쉬에 있다면 상대방의 매쉬를 킨다
	if (MyOwner->InBush == true)
	{
		GetOverlappingActors(OverlapParentPlayerArr, AParentPlayer::StaticClass());

		for (auto OverlapActor : OverlapParentPlayerArr)
		{
			AParentPlayer* OverlapPlayer = Cast<AParentPlayer>(OverlapActor);
			if (OverlapPlayer != nullptr && OverlapPlayer != MyOwner)
			{
				if (OverlapPlayer->GetMesh()->bOnlyOwnerSee == true)
				{
					OverlapPlayer->GetMesh()->SetOnlyOwnerSee(false);
				}
			}
		}
	}

	// 내가 부쉬밖에 있을 때, 나와 오버랩된 플레이어가 부쉬에 있고 매쉬가 켜저있다면 매쉬를 끈다
	if (MyOwner->InBush == false)
	{
		GetOverlappingActors(OverlapParentPlayerArr, AParentPlayer::StaticClass());

		for (auto OverlapActor : OverlapParentPlayerArr)
		{
			AParentPlayer* OverlapPlayer = Cast<AParentPlayer>(OverlapActor);
			if (OverlapPlayer != nullptr && OverlapPlayer != MyOwner)
			{
				if (OverlapPlayer->InBush == true && OverlapPlayer->GetMesh()->bOnlyOwnerSee == false)
				{
					OverlapPlayer->GetMesh()->SetOnlyOwnerSee(true);
				}
			}
		}
	}
}