// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Actor/QuestEnemy.h"

#include "Kismet/GameplayStatics.h"
#include "Public/Game_State/QuestGameState.h"


// Sets default values
AQuestEnemy::AQuestEnemy()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AQuestEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQuestEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AQuestEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AQuestEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, 
							  AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (bIsDead)
	{
		return 0.0f;
	}

	Health -= ActualDamage;

	if (Health <= 0.0f)
	{
		Die();
	}

	return ActualDamage;
}

void AQuestEnemy::Die()
{
	bIsDead = true;

	if (AQuestGameState* GS = Cast<AQuestGameState>(UGameplayStatics::GetGameState(this)))
	{
		GS->ReportGameplayObjective(EQuestObjectiveType::Kill, TargetID, 1);
	}

	SetActorEnableCollision(false);
	Destroy();
}