// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller_StartMenu.h"
#include "BasicCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

AController_StartMenu::AController_StartMenu()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> ui(TEXT("/Game/_My/UI/HUD"));
	if (ui.Succeeded())
	{
		uiGameBPClass = ui.Class;
	}

	if (uiGameBPClass)
	{
		uiGameWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameBPClass);
		if (uiGameWidget)
		{
			uiGameWidget->AddToViewport();
		}
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> gamemenuUI(TEXT("/Game/_My/UI/GameMenu_BP"));
	static ConstructorHelpers::FClassFinder<UUserWidget> DieUI(TEXT("/Game/_My/UI/HUD_Die"));
	if (gamemenuUI.Succeeded())
	{
		uiGameMenuBPClass = gamemenuUI.Class;
	}
	if (DieUI.Succeeded())
	{
		uiGameDieBPClass = DieUI.Class;
	}
}

void AController_StartMenu::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	InputComponent->BindAction("ShowGameMenu", IE_Pressed, this, &AController_StartMenu::ShowGameMenu);
	InputComponent->BindAction("Attack", IE_Pressed, this, &AController_StartMenu::WeaponAttack);
}

void AController_StartMenu::ShowGameMenu()
{
	uiGameMenuWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameMenuBPClass);
	if (uiGameMenuWidget)
	{
		uiGameMenuWidget->AddToViewport();
	}

}

void AController_StartMenu::WeaponAttack()
{
	ABasicCharacter* MyPlayer = Cast<ABasicCharacter>(GetPawn());
	MyPlayer->Attack_Melee();
}

void AController_StartMenu::ShowDieUI()
{
	if (uiGameBPClass)
	{
		uiGameDieWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameDieBPClass);
		if (uiGameDieWidget)
		{
			uiGameDieWidget->AddToViewport();
		}
	}
}
