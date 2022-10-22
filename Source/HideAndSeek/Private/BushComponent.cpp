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

// ĳ���� ��Ʈ�ѷ��� �޾� ���� ���ʸ� ���Ѵ�
// ���� ���ʰ� �ν��� �ִٸ� ���� ���ʿ� �������� ��� ĳ���͵��� �Ž��� �ڱ� Ŭ���̾�Ʈ������ �Ѱ������ν� ���� �� �� �ְ� ���ش�
// ���� ���ʰ� �ν����� �����ְ� �������� ������ �ν��� �ִ� ���¶�� ��� ĳ���͵��� �Ž��� ���� �� �� ���� ���ش�
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