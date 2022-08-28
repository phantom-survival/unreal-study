// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Components/GridPanel.h"
#include "UI_Inventory_Widget.generated.h"

/**
 * 
 */
UCLASS()
class STUDYCHARACTER_API UUI_Inventory_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UGridPanel* GridPanel_ItemSlots = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MySlot)
	UUserWidget* MyItemSlot;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_Inventory_Close = nullptr;

	UFUNCTION()
	void Btn_Inventory_CloseWindow();

	UFUNCTION()
	void SpawnSlots();
};
