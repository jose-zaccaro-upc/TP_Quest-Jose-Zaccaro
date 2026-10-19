// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_QuestCharacter.h"
#include "QuestCharacter.generated.h"

class UQuestComponent;
class UInputAction;
class UUserWidget;

/**
 * Character variant with integrated Quest Component and interaction trace support.
 */
UCLASS()
class TP_QUEST_API AQuestCharacter : public ATP_QuestCharacter
{
	GENERATED_BODY()

public:
	AQuestCharacter();

	/** Returns the QuestComponent subobject */
	UFUNCTION(BlueprintPure, Category = "Quest")
	UQuestComponent* GetQuestComponent() const { return QuestComponent; }

	/** Performs a line trace by Visibility channel to detect and interact with IInteractableInterface actors */
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	virtual void PerformInteractionTrace();

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Player HUD Widget class to automatically spawn on BeginPlay */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	/** Quest management component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UQuestComponent> QuestComponent;

	/** Input Action for Interaction (defaults to IA_Interact if available) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;

	/** Maximum distance for interaction trace (center of screen deprojected with default 2500 units) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float InteractionDistance = 2500.0f;

	/** Whether to draw debug line trace in the viewport */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bDrawDebugTrace = true;

	/** Duration (in seconds) the debug line remains visible */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float DebugTraceDuration = 2.5f;
};
