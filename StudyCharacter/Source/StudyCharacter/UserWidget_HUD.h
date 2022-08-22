// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserWidget_HUD.generated.h"

/**
 * 
 */
UCLASS()
class STUDYCHARACTER_API UUserWidget_HUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//UUserWidget_HUD();
	//void BeginPlay() override;

private:
	TSubclassOf<class UUserWidget> uiBPClass;
	UUserWidget* uiWidget;
};
