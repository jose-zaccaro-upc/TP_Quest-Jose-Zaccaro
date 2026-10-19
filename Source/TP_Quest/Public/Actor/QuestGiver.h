// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Public/Interface/InteractableInterface.h"
#include "QuestGiver.generated.h"

class UPDA_QuestDefinition;
class USceneComponent;
class USkeletalMeshComponent;

UCLASS()
class TP_QUEST_API AQuestGiver : public AActor, public IInteractableInterface
{
	GENERATED_BODY()

public:
	AQuestGiver();
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(AActor* Interactor) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	TObjectPtr<const UPDA_QuestDefinition> QuestToGive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FName TargetID;
};
