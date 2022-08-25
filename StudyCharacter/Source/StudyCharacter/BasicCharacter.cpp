// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"
#include "Containers/Array.h"
#include "GameFramework/Pawn.h"
#include "MyTestWeapon.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "HPBar.h"
#include "Engine.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
	:myHealth(myMaxHealth)
	,Widget_Component(CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue")))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isDuringAttack = false;
	ComboAttackNum = 1;

	//위젯 컴포넌트 위치세팅
	if (Widget_Component)
	{
		Widget_Component->SetupAttachment(RootComponent);
		Widget_Component->SetWidgetSpace(EWidgetSpace::Screen);
		Widget_Component->SetRelativeLocation(FVector(0.0f, 0.0f, 80.0f));
		static ConstructorHelpers::FClassFinder<UUserWidget> widget_class(TEXT("/Game/_My/UI/HPbar_BP"));

		if (widget_class.Succeeded())
		{
			Widget_Component->SetWidgetClass(widget_class.Class);
		}
	}
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

	myHealth = myMaxHealth;
}

//************************************

// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//HPbar update
	auto const uw = Cast<UHPbar>(Widget_Component->GetUserWidgetObject());
	if (uw)
	{
		uw->set_bar_value_percent((myHealth / myMaxHealth) * 100 * 0.01f);
	}
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
	if (ComboAttackNum <= 3)
	{
		FString PlaySection = "Light0" + FString::FromInt(ComboAttackNum);

		PlayAnimMontage(AttackCombo_AnimMt, 1.f, FName(*PlaySection));

		ComboAttackNum++;

		isDuringAttack = true;

	}
	else
	{
		PlayAnimMontage(AttackCombo_AnimMt, 1.f);
		ComboAttackNum = 1;
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
	PlayAnimMontage(BeHit_AnimMontage);
	if (DamageTaken > 0.f)
	{
		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}
}

void ABasicCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	myHealth = FMath::Min(0.f, myHealth);

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) 
		: GetDefault<UDamageType>();

	Killer = GetDamageInstigator(Killer, *DamageType);

	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();

	}

	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetSimulatePhysics(true);
	
	if (Controller != NULL)
	{
		Controller->UnPossess();
	}

	float DeathAnimDuration = PlayAnimMontage(Death_AnimMontage);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABasicCharacter::DeathAnimationEnd, DeathAnimDuration, false);
}

void ABasicCharacter::DeathAnimationEnd()
{
	this->SetActorHiddenInGame(true);
	SetLifeSpan(0.1f);
}

float ABasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float myGetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (myHealth <= 0.f)
	{
		return 0.0f;
	}

	if (myGetDamage > 0.f)
	{
		myHealth -= myGetDamage;
	}

	if (myHealth <= 0.0f)
	{
		PlayAnimMontage(Death_AnimMontage, 1.0f);
		Die(myGetDamage, DamageEvent, EventInstigator, DamageCauser);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP is : %f"), myHealth));
		OnHit(myGetDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
	}

	return myGetDamage;
}

float ABasicCharacter::get_Health() const
{
	return myHealth;
}

float ABasicCharacter::get_maxHealth() const
{
	return myMaxHealth;
}

void ABasicCharacter::set_health(float const new_health)
{
	myHealth = new_health;
}
