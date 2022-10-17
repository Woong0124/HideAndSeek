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

	OnComponentBeginOverlap.AddDynamic(this, &UBushComponent::BushInFunc);
	OnComponentEndOverlap.AddDynamic(this, &UBushComponent::BushOutFunc);
}

void UBushComponent::BeginPlay()
{
	
}

void UBushComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// ���� �ν��� ���� ��, ���� �������� �÷��̾ �ν��� �ִٸ� ������ �Ž��� Ų��
	if (MyOwner->InBush == true)
	{
		GetOverlappingActors(PlayerArr, AParentPlayer::StaticClass());

		for (auto PArr : PlayerArr)
		{
			AParentPlayer* PP = Cast<AParentPlayer>(PArr);
			if (PP != nullptr && PP != MyOwner)
			{
				if (PP->GetMesh()->bOnlyOwnerSee == true)
				{
					PP->GetMesh()->SetOnlyOwnerSee(false);
				}
			}
		}
	}

	// ���� �ν��ۿ� ���� ��, ���� �������� �÷��̾ �ν��� �ְ� �Ž��� �����ִٸ� �Ž��� ����
	if (MyOwner->InBush == false)
	{
		GetOverlappingActors(PlayerArr, AParentPlayer::StaticClass());

		for (auto PArr : PlayerArr)
		{
			AParentPlayer* PP = Cast<AParentPlayer>(PArr);
			if (PP != nullptr && PP != MyOwner)
			{
				if (PP->InBush == true && PP->GetMesh()->bOnlyOwnerSee == false)
				{
					PP->GetMesh()->SetOnlyOwnerSee(true);
				}
			}
		}
	}
}

void UBushComponent::BushInFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AParentPlayer* OverlapActor = Cast<AParentPlayer>(OtherActor);

	//GetOverlappingActors(BushArr, UBushComponent::StaticClass());

	if (OverlapActor != nullptr)
	{
		if (MyOwner->InBush == true && OverlapActor->InBush == true)
		{
			if (OverlapActor->GetMesh()->bOnlyOwnerSee == true)
			{
				OverlapActor->GetMesh()->SetOnlyOwnerSee(false);
			}
		}
	}
}

void UBushComponent::BushOutFunc(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AParentPlayer* OverlapActor = Cast<AParentPlayer>(OtherActor);

	if (OverlapActor != nullptr)
	{
		if (MyOwner->InBush == true && OverlapActor->InBush == true)
		{
			OverlapActor->GetMesh()->SetOnlyOwnerSee(true);
		}

		if (MyOwner->InBush == true && OverlapActor->InBush == false)
		{
			MyOwner->GetMesh()->SetOnlyOwnerSee(true);
		}
	}
}