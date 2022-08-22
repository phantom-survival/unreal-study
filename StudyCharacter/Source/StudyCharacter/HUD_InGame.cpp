// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD_InGame.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

AHUD_InGame::AHUD_InGame()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ui(TEXT("/Game/_My/UI/HUD"));
	if (ui.Succeeded())
	{
		uiBPClass = ui.Class;
	}
}

void AHUD_InGame::BeginPlay()
{
	Super::BeginPlay();

	//viewport에 ui만들기
	if (uiBPClass)
	{
		uiWidget = CreateWidget<UUserWidget>(GetWorld(), uiBPClass);
		if (uiWidget)
		{
			uiWidget->AddToViewport();
		}
	}
}
