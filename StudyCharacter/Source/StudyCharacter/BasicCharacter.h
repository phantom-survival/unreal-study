// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicCharacter.generated.h"

UCLASS()
class STUDYCHARACTER_API ABasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABasicCharacter();

	USkeletalMeshComponent* GetSpecificPawnMesh() const;

	FName GetWeaponAttachPoint() const;

	void EquipWeapon(class AMyTestWeapon* Weapon);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
	float myHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
	float myMaxHealth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	FName WeaponAttachPoint;

	TArray<class AMyTestWeapon*> Inventory;

	class AMyTestWeapon* CurrentWeapon;

	void AddWeapon(class AMyTestWeapon* Weapon);

	void SetCurrentWeapon(class AMyTestWeapon* NewWeapon, class AMyTestWeapon* LastWeapon);

	void SpawndefaultInventory();

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TArray<TSubclassOf<class AMyTestWeapon>>DefaultInventoryClasses;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack_Anim(UAnimMontage* AnimMontage);
	void Attack_Melee();
	void Attack_Melee_End();

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* Attack_Melee_Anim01;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* Attack_Melee_Anim02;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* Attack_Melee_Anim03;

	TArray<UAnimMontage*> AnimArr;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* Melee_Anim_Idle;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* BeHit_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* Death_AnimMontage;

	bool isDuringAttack;

	int ComboAttackNum;

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
