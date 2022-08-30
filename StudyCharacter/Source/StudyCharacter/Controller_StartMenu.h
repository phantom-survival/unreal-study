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
	void ShowShopUI();
	void WeaponAttack();
	void ShowDieUI();
	void CloseGameMenu();

	UFUNCTION(BlueprintCallable, Category = "MyUI")
	void CloseInventory();

	UFUNCTION(BlueprintCallable, Category = "MyUI")
	void CloseShopUI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isShowShopMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isShowInventory;
	
	TSubclassOf<class UUserWidget>uiItemSlotBPClass;
	UUserWidget* uiItemSlotWidget;

protected:
	void SetupInputComponent() override;

private:
	TSubclassOf<class UUserWidget> uiGameBPClass;
	UUserWidget* uiGameWidget;

	TSubclassOf<class UUserWidget> uiGameMenuBPClass;
	UUserWidget* uiGameMenuWidget;

	TSubclassOf<class UUserWidget> uiGameDieBPClass;
	UUserWidget* uiGameDieWidget;

	TSubclassOf<class UUserWidget> uiGameInventoryBPClass;
	UUserWidget* uiGameInventoryWidget;

	TSubclassOf<class UUserWidget>uiGameShopBPClass;
	UUserWidget* uiGameShopWidget;
};
