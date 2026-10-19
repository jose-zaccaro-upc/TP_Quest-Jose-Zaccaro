// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Game_State/QuestGameState.h"

void AQuestGameState::ReportGameplayObjective(EQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount)
{
	OnGameplayObjectiveEvent.Broadcast(ObjectiveType, TargetID, Amount);
}