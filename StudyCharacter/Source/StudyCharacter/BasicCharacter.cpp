// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"
#include "Containers/Array.h"
#include "MyTestWeapon.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isDuringAttack = false;
	ComboAttackNum = 0;
	myHealth = 0.f;
	myMaxHealth = 100.0f;
}

//***************Weapon****************

USkeletalMeshComponent* ABasicCharacter::GetSpecificPawnMesh() const
{
	return GetMesh();
}

FName ABasicCharacter::GetWeaponAttachPoint() const
{
	return WeaponAttachPoint;
}

void ABasicCharacter::EquipWeapon(AMyTestWeapon* Weapon)
{
	if (Weapon)
	{
		SetCurrentWeapon(Weapon, CurrentWeapon);
	}
}

void ABasicCharacter::AddWeapon(AMyTestWeapon* Weapon)
{
	if (Weapon)
	{
		Inventory.AddUnique(Weapon);
	}
}

void ABasicCharacter::SetCurrentWeapon(AMyTestWeapon* NewWeapon, AMyTestWeapon* LastWeapon)
{
	AMyTestWeapon* LocalLastWeapon = NULL;
	if (LastWeapon != NULL) 
	{
		LocalLastWeapon = LastWeapon;
	}

	if (NewWeapon)
	{
		NewWeapon->SetOwningPawn(this);
		NewWeapon->OnEquip(LastWeapon);
	}
}

void ABasicCharacter::SpawndefaultInventory()
{
	int32 NumWeaponClasses = DefaultInventoryClasses.Num();
	
	if (DefaultInventoryClasses[0])
	{
		FActorSpawnParameters SpawnInfo;
		UWorld* WRLD = GetWorld();
		AMyTestWeapon* NewWeapon = WRLD->SpawnActor<AMyTestWeapon>(DefaultInventoryClasses[0], SpawnInfo);
		AddWeapon(NewWeapon);
	}
	
	if (Inventory.Num() > 0)
	{
		EquipWeapon(Inventory[0]);
	}
}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	AnimArr.Emplace(Attack_Melee_Anim01);
	AnimArr.Emplace(Attack_Melee_Anim02);
	AnimArr.Emplace(Attack_Melee_Anim03);
}

//************************************

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

void ABasicCharacter::Attack_Anim(UAnimMontage* AnimMontage)
{
	PlayAnimMontage(AnimMontage, 1.0f);
	isDuringAttack = true;
}

void ABasicCharacter::Attack_Melee()
{
	Attack_Anim(AnimArr[ComboAttackNum++]);
	if (ComboAttackNum > 2) {
		ComboAttackNum = 0;
	}
	
	FTimerHandle TH_Attack_End;
	GetWorldTimerManager().SetTimer(TH_Attack_End, this,
		&ABasicCharacter::Attack_Melee_End, 1.7f, false);
}

void ABasicCharacter::Attack_Melee_End()
{
	isDuringAttack = false;
}

void ABasicCharacter::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{

}

float ABasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float myGetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (myHealth <= 0)
	{
		this->Destroy();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP is : %f"), myHealth));
		myHealth -= myGetDamage;
	}
	PlayAnimMontage(BeHit_AnimMontage, 1.0f);

	return 0.0f;
}
