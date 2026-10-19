#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Public/Struct/QuestObjective.h"
#include "PDA_QuestDefinition.generated.h"

UCLASS()
class TP_QUEST_API UPDA_QuestDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FName QuestID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FText QuestName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	TArray<FQuestObjective> Objectives;
};
