// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPCbot.h"
#include "Controller_StartMenu.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine.h"
#include "MyTestCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyNPCbot::AMyNPCbot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GateCollisionSphere"));
	CollisionSphere->SetupAttachment(this->GetCapsuleComponent());
	CollisionSphere->InitSphereRadius(250.f);

	isTalk = false;
}

void AMyNPCbot::FaceRotation(FRotator NewRotation, float DeltaTime)
{
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), NewRotation, DeltaTime, 8.f);
	Super::FaceRotation(CurrentRotation, DeltaTime);
}

// Called when the game starts or when spawned
void AMyNPCbot::BeginPlay()
{
	Super::BeginPlay();
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMyNPCbot::OnOverlapBegin);
}

// Called every frame
void AMyNPCbot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector PlayerPos = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
	FVector myLoc = GetActorLocation();
	
	FVector Forward = (PlayerPos - myLoc);
	
	FRotator PlayerRot = FRotationMatrix::MakeFromX(Forward).Rotator();
	
	if (isTalk)
	{
		FaceRotation(PlayerRot, 0.01f);
	}
}

// Called to bind functionality to input
void AMyNPCbot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyNPCbot::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && !isTalk)
	{
		UGameplayStatics::PlaySound2D(this, InteractSound);
		isTalk = true;

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("Touch!!"));
	}
}

void AMyNPCbot::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && isTalk)
	{
		isTalk = false;
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("Out!"));
	}
}
