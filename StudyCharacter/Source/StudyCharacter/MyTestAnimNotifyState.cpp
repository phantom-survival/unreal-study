// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestAnimNotifyState.h"
#include "Engine.h"
#include "BasicCharacter.h"

void UMyTestAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, __FUNCTION__);
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		ABasicCharacter* Player = Cast<ABasicCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->isDuringAttack = true;
		}
	}
}

void UMyTestAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, __FUNCTION__);
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		ABasicCharacter* Player = Cast<ABasicCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->Attack_Melee_End();
			Player->isDuringAttack = false;
		}
	}
}
