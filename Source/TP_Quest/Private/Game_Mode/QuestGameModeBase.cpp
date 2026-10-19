// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Game_Mode/QuestGameModeBase.h"

#include "Public/Game_State/QuestGameState.h"
#include "Public/Character/QuestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AQuestGameModeBase::AQuestGameModeBase()
{
	// Set default GameState to C++ AQuestGameState
	GameStateClass = AQuestGameState::StaticClass();

	// Set default Pawn class to AQuestCharacter (or a derived Blueprint if available)
	DefaultPawnClass = AQuestCharacter::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> ThirPersonBPClass(TEXT("/Game/QuestsGame/CPP/Character/BP_ThirPersonCharacter_CPP"));
	if (ThirPersonBPClass.Class != nullptr)
	{
		DefaultPawnClass = ThirPersonBPClass.Class;
	}
	else
	{
		static ConstructorHelpers::FClassFinder<APawn> QuestPawnBPClass(TEXT("/Game/QuestsGame/CPP/Character/BP_QuestCharacter"));
		if (QuestPawnBPClass.Class != nullptr)
		{
			DefaultPawnClass = QuestPawnBPClass.Class;
		}
	}
}
