#include "Public/Component/QuestComponent.h"

#include "Public/Game_State/QuestGameState.h"
#include "Public/Data_Asset/PDA_QuestDefinition.h"
#include "Public/Struct/QuestObjective.h"
#include "Public/Struct/QuestRuntime.h"
#include "Kismet/GameplayStatics.h"

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AQuestGameState* QuestGS = Cast<AQuestGameState>(UGameplayStatics::GetGameState(this)))
	{
		QuestGS->OnGameplayObjectiveEvent.AddDynamic(this, &UQuestComponent::HandleGameplayObjective);
	}
}

bool UQuestComponent::FindQuestByID(FName QuestID, FQuestRuntime& OutQuestData, int32& OutIndex) const
{
	for (int32 i = 0; i < ActiveQuests.Num(); ++i)
	{
		if (ActiveQuests[i].QuestID == QuestID)
		{
			OutQuestData = ActiveQuests[i];
			OutIndex = i;
			return true;
		}
	}

	OutIndex = INDEX_NONE;
	return false;
}

bool UQuestComponent::AddQuest(const UPDA_QuestDefinition* QuestDefinition)
{
	if (!QuestDefinition)
	{
		return false;
	}

	FQuestRuntime ExistingQuest;
	int32 ExistingIndex = INDEX_NONE;
	if (FindQuestByID(QuestDefinition->QuestID, ExistingQuest, ExistingIndex))
	{
		return false; // Prevenir duplicados
	}

	FQuestRuntime NewQuest;
	NewQuest.QuestID = QuestDefinition->QuestID;
	NewQuest.QuestDefinition = QuestDefinition;
	NewQuest.Objectives = QuestDefinition->Objectives;
	NewQuest.bIsActive = true;
	NewQuest.bIsCompleted = false;

	ActiveQuests.Add(NewQuest);

	OnQuestStarted.Broadcast(NewQuest);
	return true;
}

bool UQuestComponent::UpdateObjectiveProgress(int32 QuestIndex, int32 ObjectiveIndex, int32 Amount)
{
	if (!ActiveQuests.IsValidIndex(QuestIndex))
	{
		return false;
	}

	FQuestRuntime& Quest = ActiveQuests[QuestIndex];
	if (!Quest.bIsActive || Quest.bIsCompleted || !Quest.Objectives.IsValidIndex(ObjectiveIndex))
	{
		return false;
	}

	FQuestObjective& Objective = Quest.Objectives[ObjectiveIndex];
	Objective.CurrentAmount = FMath::Clamp(Objective.CurrentAmount + Amount, 0, Objective.RequiredAmount);

	OnQuestProgressChanged.Broadcast(Quest);

	CheckQuestCompleted(QuestIndex);
	return true;
}

bool UQuestComponent::CheckQuestCompleted(int32 QuestIndex)
{
	if (!ActiveQuests.IsValidIndex(QuestIndex))
	{
		return false;
	}

	FQuestRuntime& Quest = ActiveQuests[QuestIndex];
	if (Quest.bIsCompleted)
	{
		return true;
	}

	bool bAllCompleted = true;
	for (const FQuestObjective& Obj : Quest.Objectives)
	{
		if (Obj.CurrentAmount < Obj.RequiredAmount)
		{
			bAllCompleted = false;
			break;
		}
	}

	if (bAllCompleted)
	{
		Quest.bIsCompleted = true;
		Quest.bIsActive = false;
		OnQuestCompleted.Broadcast(Quest);
		return true;
	}

	return false;
}

void UQuestComponent::HandleGameplayObjective(EQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount)
{
	for (int32 q = 0; q < ActiveQuests.Num(); ++q)
	{
		FQuestRuntime& Quest = ActiveQuests[q];
		if (!Quest.bIsActive || Quest.bIsCompleted)
		{
			continue;
		}

		for (int32 o = 0; o < Quest.Objectives.Num(); ++o)
		{
			const FQuestObjective& Obj = Quest.Objectives[o];
			if (Obj.ObjectiveType == ObjectiveType && Obj.TargetID == TargetID)
			{
				UpdateObjectiveProgress(q, o, Amount);
			}
		}
	}
}