// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "GameHUD_UI.generated.h"

/**
 * 
 */
UCLASS()
class STUDYCHARACTER_API UGameHUD_UI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	void set_bar_value_percent(float const value);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* HUD_HP_value = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* HUD_HP_text = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_GameMenu = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn_Attack = nullptr;

private:
	UFUNCTION()
	void Btn_GameMenu_Clicked();

	UFUNCTION()
	void Btn_Attack_Clicked();
};
