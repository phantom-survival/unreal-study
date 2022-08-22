// Copyright Epic Games, Inc. All Rights Reserved.


#include "StudyCharacterGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "HUD_InGame.h"

AStudyCharacterGameModeBase::AStudyCharacterGameModeBase()
{
	HUDClass = AHUD_InGame::StaticClass();
	DefaultPawnClass = nullptr;
}

void AStudyCharacterGameModeBase::BeginPlay() {
	Super::BeginPlay();

	//CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	//CurrentWidget->AddToViewport();

	//ChangeUI();
}

void AStudyCharacterGameModeBase::ChangeUI()
{
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetclass);
	CurrentWidget->AddToViewport();
}
