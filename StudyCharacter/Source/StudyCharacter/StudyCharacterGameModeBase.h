// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StudyCharacterGameModeBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGameState :uint8
{
	GameStart,
	GamePlay,
	GamePause,
	GameOver,
};

UCLASS()
class STUDYCHARACTER_API AStudyCharacterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	//UUserWidget* CurrentWidget;
	//
	////TSubclassOf = 타입제한
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	//TSubclassOf<UUserWidget> HUDWidget;

	UPROPERTY(EditAnywhere, Category = "UMG Game")
	EGameState gameStateEnum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> HUDWidgetclass;

	UUserWidget* CurrentWidget;

public:
	AStudyCharacterGameModeBase();
	void ChangeUI();
};
