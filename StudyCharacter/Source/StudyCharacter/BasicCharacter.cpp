// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasicCharacter::Attack_Melee()
{
	switch (ComboAttackNum)
	{
	case 0:
		PlayAnimMontage(Attack_Melee_Anim01, 1.0f);
		isDuringAttack = true;
		ComboAttackNum++;
		break;
	case 1:
		PlayAnimMontage(Attack_Melee_Anim02, 1.0f);
		isDuringAttack = true;
		ComboAttackNum++;
		break;
	case 2:
		PlayAnimMontage(Attack_Melee_Anim03, 1.0f);
		isDuringAttack = true;
		ComboAttackNum++;
		break;
	default:
		ComboAttackNum = 0;
		break;
	}
	
	FTimerHandle TH_Attack_End;
	GetWorldTimerManager().SetTimer(TH_Attack_End, this,
		&ABasicCharacter::Attack_Melee_End, 1.7f, false);
}

void ABasicCharacter::Attack_Melee_End()
{
	isDuringAttack = false;
	//공격 후 공격 준비자세
	//PlayAnimMontage(Melee_Anim_Idle, 1.0f);
	ComboAttackNum = 0;
}
