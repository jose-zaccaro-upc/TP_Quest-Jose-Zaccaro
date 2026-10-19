// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Public/Enum/QuestTypes.h"
#include "QuestGameState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnGameplayObjectiveEventSignature, EQuestObjectiveType, ObjectiveType, FName, TargetID, int32, Amount);

UCLASS()
class TP_QUEST_API AQuestGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Quest Events")
	FOnGameplayObjectiveEventSignature OnGameplayObjectiveEvent;

	UFUNCTION(BlueprintCallable, Category = "Quest Events")
	void ReportGameplayObjective(EQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount = 1);
};
