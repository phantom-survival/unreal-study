// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestWeapon.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Engine.h"

// Sets default values
AMyTestWeapon::AMyTestWeapon(const class FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
	WeaponMesh->CastShadow = true;
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMesh;

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollision"));
	WeaponCollision->SetBoxExtent(FVector(5.f, 5.f, 5.f));
	WeaponCollision->AttachToComponent(WeaponMesh, FAttachmentTransformRules::KeepRelativeTransform, "DamageSoket");
}

void AMyTestWeapon::SetOwningPawn(ABasicCharacter* NewOwner)
{
	if (MyPawn != NewOwner)
	{
		MyPawn = NewOwner;
	}
}

void AMyTestWeapon::AttachMeshToPawn()
{
	if (MyPawn)
	{
		USkeletalMeshComponent* PawnMesh = MyPawn->GetSpecificPawnMesh();
		FName AttachPoint = MyPawn->GetWeaponAttachPoint();
		WeaponMesh->AttachToComponent(PawnMesh, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
	}
}

void AMyTestWeapon::OnEquip(const AMyTestWeapon* LastWeapon)
{
	AttachMeshToPawn();
}
