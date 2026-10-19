// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Character/QuestCharacter.h"

#include "Public/Component/QuestComponent.h"
#include "Public/Interface/InteractableInterface.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

AQuestCharacter::AQuestCharacter()
{
	// Instantiate the QuestComponent
	QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("QuestComponent"));

	// Attempt to locate and assign the default IA_Interact input action
	static ConstructorHelpers::FObjectFinder<UInputAction> InteractActionFinder(TEXT("/Game/Input/Actions/IA_Interact.IA_Interact"));
	if (InteractActionFinder.Succeeded())
	{
		InteractAction = InteractActionFinder.Object;
	}

	// Attempt to assign WBP_PlayerHUD_CPP as default HUD widget
	static ConstructorHelpers::FClassFinder<UUserWidget> HUDFinder(TEXT("/Game/QuestsGame/CPP/UI/WBP_PlayerHUD_CPP"));
	if (HUDFinder.Succeeded())
	{
		PlayerHUDWidgetClass = HUDFinder.Class;
	}
}

void AQuestCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Automatically create and add HUD to viewport for local player
	if (IsLocallyControlled() && PlayerHUDWidgetClass)
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			if (UUserWidget* HUDWidget = CreateWidget<UUserWidget>(PC, PlayerHUDWidgetClass))
			{
				HUDWidget->AddToViewport();
			}
		}
	}
}

void AQuestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (InteractAction)
		{
			EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AQuestCharacter::PerformInteractionTrace);
		}
	}
}

void AQuestCharacter::PerformInteractionTrace()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	FVector TraceStart = FVector::ZeroVector;
	FVector WorldDirection = FVector::ForwardVector;

	APlayerController* PC = Cast<APlayerController>(GetController());
	bool bDeprojected = false;

	if (PC)
	{
		int32 ViewportSizeX = 0;
		int32 ViewportSizeY = 0;
		PC->GetViewportSize(ViewportSizeX, ViewportSizeY);

		if (ViewportSizeX > 0 && ViewportSizeY > 0)
		{
			// Center of screen
			const float ScreenCenterX = ViewportSizeX * 0.5f;
			const float ScreenCenterY = ViewportSizeY * 0.5f;

			bDeprojected = PC->DeprojectScreenPositionToWorld(
				ScreenCenterX,
				ScreenCenterY,
				TraceStart,
				WorldDirection
			);
		}

		if (!bDeprojected)
		{
			FRotator ViewRot;
			PC->GetPlayerViewPoint(TraceStart, ViewRot);
			WorldDirection = ViewRot.Vector();
		}
	}


	const FVector TraceEnd = TraceStart + (WorldDirection * InteractionDistance);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	const bool bHit = World->LineTraceSingleByChannel(
		HitResult,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		QueryParams
	);

	// Draw debug visual trace if enabled
	if (bDrawDebugTrace)
	{
		const FVector DebugLineEnd = bHit ? HitResult.ImpactPoint : TraceEnd;
		const FColor TraceColor = bHit ? FColor::Green : FColor::Red;
		DrawDebugLine(World, TraceStart, DebugLineEnd, TraceColor, false, DebugTraceDuration, 0, 2.0f);

		if (bHit)
		{
			// Dim line continuing after impact and yellow dot on impact
			DrawDebugLine(World, HitResult.ImpactPoint, TraceEnd, FColor(100, 0, 0), false, DebugTraceDuration, 0, 1.0f);
			DrawDebugPoint(World, HitResult.ImpactPoint, 14.0f, FColor::Yellow, false, DebugTraceDuration);
		}
	}

	AActor* TargetActor = nullptr;

	if (bHit && HitResult.GetActor() && HitResult.GetActor()->Implements<UInteractableInterface>())
	{
		TargetActor = HitResult.GetActor();
	}
	else
	{
		// Fallback: Check in front of the character in case the camera angle was slightly misaligned
		const FVector CharStart = GetActorLocation() + FVector(0.f, 0.f, 40.f);
		const FVector CharEnd = CharStart + (GetActorForwardVector() * 350.0f);

		FHitResult CharHit;
		if (World->LineTraceSingleByChannel(CharHit, CharStart, CharEnd, ECC_Visibility, QueryParams))
		{
			if (bDrawDebugTrace)
			{
				DrawDebugLine(World, CharStart, CharHit.bBlockingHit ? CharHit.ImpactPoint : CharEnd, FColor::Cyan, false, DebugTraceDuration, 0, 1.5f);
			}

			if (CharHit.GetActor() && CharHit.GetActor()->Implements<UInteractableInterface>())
			{
				TargetActor = CharHit.GetActor();
			}
		}
	}

	if (TargetActor)
	{
		IInteractableInterface::Execute_Interact(TargetActor, this);
	}
}
