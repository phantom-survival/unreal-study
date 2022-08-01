// Copyright Epic Games, Inc. All Rights Reserved.


#include "StudyCharacterGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AStudyCharacterGameModeBase::BeginPlay() {
	Super::BeginPlay();

	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidget);
	CurrentWidget->AddToViewport();

}

