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
	FName MyCharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
	float myHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
	float myMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float myHPnum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString myHPbarText;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString myCharacterNameText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString myCharacterLevelText;

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

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, class AController* Killer, class AActor* DamageCauser);

	void DeathAnimationEnd();

	class UWidgetComponent* Widget_Component;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack_Anim(UAnimMontage* AnimMontage);
	void Attack_Melee();
	void Attack_Melee_End();

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* AttackCombo_AnimMt;

	UAnimMontage* Melee_Anim_Idle;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* BeHit_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
	UAnimMontage* Death_AnimMontage;

	bool isDuringAttack;

	int ComboAttackNum;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	//HP관련
	float get_Health() const;
	float get_maxHealth() const;
	void set_health(float const new_health);
};
