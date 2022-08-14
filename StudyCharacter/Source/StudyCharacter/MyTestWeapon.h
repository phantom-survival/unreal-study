// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasicCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "MyTestWeapon.generated.h"

UCLASS()
class STUDYCHARACTER_API AMyTestWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTestWeapon(const class FObjectInitializer& ObjectInitializer);

	void SetOwningPawn(ABasicCharacter* NewOwner);
	void AttachMeshToPawn();
	void OnEquip(const AMyTestWeapon* LastWeapon);

private:
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
	class UBoxComponent* WeaponCollision;

protected:
	class ABasicCharacter* MyPawn;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
