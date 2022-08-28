// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Inventory_Widget.h"
#include "Controller_StartMenu.h"

void UUI_Inventory_Widget::NativeConstruct()
{
	if (Btn_Inventory_Close)
	{
		Btn_Inventory_Close->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Inventory_CloseWindow);
	}
}

void UUI_Inventory_Widget::Btn_Inventory_CloseWindow()
{
	AController_StartMenu* ctr = Cast<AController_StartMenu>(GetOwningPlayer());
	ctr->CloseInventory();
}

void UUI_Inventory_Widget::SpawnSlots()
{
	AController_StartMenu* ctr = Cast<AController_StartMenu>(GetOwningPlayer());

	UUserWidget* slotWidget = ctr->uiItemSlotWidget;

	for (int i = 0; i < 8; i++)
	{
		slotWidget = CreateWidget<UUserWidget>(GetWorld());
		GridPanel_ItemSlots->AddChildToGrid(slotWidget);
		MyItemSlot->AddToViewport();
	}
}
