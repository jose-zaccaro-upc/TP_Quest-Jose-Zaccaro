// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "QuestGameModeBase.generated.h"

/**
 * Dedicated GameMode for the C++ Quest demonstration level (L_Quests_CPP).
 * Configures AQuestGameState and AQuestCharacter as default classes.
 */
UCLASS()
class TP_QUEST_API AQuestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AQuestGameModeBase();
};
