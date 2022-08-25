// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Controller_StartMenu.generated.h"

/**
 * 
 */
UCLASS()
class STUDYCHARACTER_API AController_StartMenu : public APlayerController
{
	GENERATED_BODY()
	
public:
	AController_StartMenu();

	void ShowGameMenu();
	void ShowInventory();
	void WeaponAttack();
	void ShowDieUI();
	void CloseGameMenu();

protected:
	void SetupInputComponent() override;

private:
	TSubclassOf<class UUserWidget> uiGameBPClass;
	UUserWidget* uiGameWidget;

	TSubclassOf<class UUserWidget> uiGameMenuBPClass;
	UUserWidget* uiGameMenuWidget;

	TSubclassOf<class UUserWidget> uiGameDieBPClass;
	UUserWidget* uiGameDieWidget;
};
