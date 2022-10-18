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
	// ���� �ν��� ���� ��, ���� �������� �÷��̾ �ν��� �ִٸ� ������ �Ž��� Ų��
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

	// ���� �ν��ۿ� ���� ��, ���� �������� �÷��̾ �ν��� �ְ� �Ž��� �����ִٸ� �Ž��� ����
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