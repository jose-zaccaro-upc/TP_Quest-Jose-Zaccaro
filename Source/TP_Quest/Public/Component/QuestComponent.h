// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Public/Enum/QuestTypes.h"
#include "Public/Struct/QuestRuntime.h"
#include "QuestComponent.generated.h"

class UPDA_QuestDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestRuntimeEventSignature, const FQuestRuntime&, QuestData);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TP_QUEST_API UQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UQuestComponent();

	UPROPERTY(BlueprintAssignable, Category = "Quest")
	FOnQuestRuntimeEventSignature OnQuestStarted;

	UPROPERTY(BlueprintAssignable, Category = "Quest")
	FOnQuestRuntimeEventSignature OnQuestProgressChanged;

	UPROPERTY(BlueprintAssignable, Category = "Quest")
	FOnQuestRuntimeEventSignature OnQuestCompleted;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool AddQuest(const UPDA_QuestDefinition* QuestDefinition);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool FindQuestByID(FName QuestID, FQuestRuntime& OutQuestData, int32& OutIndex) const;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool UpdateObjectiveProgress(int32 QuestIndex, int32 ObjectiveIndex, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool CheckQuestCompleted(int32 QuestIndex);

	UFUNCTION(BlueprintCallable, Category = "Quest")
	const TArray<FQuestRuntime>& GetActiveQuests() const { return ActiveQuests; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TArray<FQuestRuntime> ActiveQuests;

	UFUNCTION()
	void HandleGameplayObjective(EQuestObjectiveType ObjectiveType, FName TargetID, int32 Amount);
};
