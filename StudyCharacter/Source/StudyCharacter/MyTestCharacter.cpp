// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyTestCharacter::AMyTestCharacter() {

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AMyTestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//컴포넌트가 있는지 체크
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyTestCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyTestCharacter::MoveRight);

	PlayerInputComponent->BindAction("Attack", IE_Released, this, &AMyTestCharacter::Attack_Melee);
}

void AMyTestCharacter::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f) && isDuringAttack == false) {
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AMyTestCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f) && isDuringAttack == false) {
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}
