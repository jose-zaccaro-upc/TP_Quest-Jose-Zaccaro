// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "QuestEnemy.generated.h"

UCLASS()
class TP_QUEST_API AQuestEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AQuestEnemy();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, 
								 AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FName TargetID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Health = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stats")
	bool bIsDead = false;

	virtual void Die();
};
