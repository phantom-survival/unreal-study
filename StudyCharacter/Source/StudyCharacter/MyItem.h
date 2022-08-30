// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "MyItem.generated.h"

USTRUCT(BlueprintType)
struct FItemInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemInfo()
	{
		ItemName = FText::FromString("Name");
		ItemLevel = 1;
		ItemGold = 100;
		Description = FText::FromString("This Item is ");
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* ItemThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

};

UCLASS()
class STUDYCHARACTER_API AMyItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
