// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BasicCharacter.h"
#include "Engine.h"
#include "MyTestCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMyTestActor::AMyTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obj"));
	RootComponent = mStaticMesh;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->InitSphereRadius(100.0f);
	CollisionSphere->SetupAttachment(RootComponent);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMyTestActor::OnOverlapBegin);
	
	static ConstructorHelpers::FObjectFinder<UParticleSystem>ParticleAsset(TEXT("/Game/Particles/P_Explosion.P_Explosion"));
	ParticleFX = ParticleAsset.Object;
}

// Called when the game starts or when spawned
void AMyTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyTestActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(AMyTestCharacter::StaticClass())) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("킷타죠!"));

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleFX, GetActorLocation());
		Destroy(); 
	}
}
