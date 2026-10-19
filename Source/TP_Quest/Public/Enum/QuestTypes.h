// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestTypes.generated.h"

UENUM(BlueprintType)
enum class EQuestObjectiveType : uint8
{
	Kill,
	Collect,
	Interact,
	ReachLocation
};