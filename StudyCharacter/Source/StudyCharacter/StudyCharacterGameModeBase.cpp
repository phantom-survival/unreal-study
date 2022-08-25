// Copyright Epic Games, Inc. All Rights Reserved.


#include "StudyCharacterGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD_HUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Controller_StartMenu.h"

AStudyCharacterGameModeBase::AStudyCharacterGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> player(TEXT("/Game/_My/MyTestCharacter_BP"));
	if (player.Succeeded())
	{
		DefaultPawnClass = player.Class;
	}

	HUDClass = AGameHUD_HUD::StaticClass();
	PlayerControllerClass = AController_StartMenu::StaticClass();
}

void AStudyCharacterGameModeBase::BeginPlay() 
{
	Super::BeginPlay();
}
