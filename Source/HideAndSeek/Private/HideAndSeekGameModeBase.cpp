// Copyright Epic Games, Inc. All Rights Reserved.


#include "HideAndSeekGameModeBase.h"
#include "ParentPlayer.h"

AHideAndSeekGameModeBase::AHideAndSeekGameModeBase()
{
	DefaultPawnClass = AParentPlayer::StaticClass();
}

void AHideAndSeekGameModeBase::BeginPlay()
{

}