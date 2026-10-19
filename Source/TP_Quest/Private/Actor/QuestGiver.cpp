

#include "Public/Actor/QuestGiver.h"

#include "Public/Component/QuestComponent.h"
#include "Public/Data_Asset/PDA_QuestDefinition.h"
#include "Public/Game_State/QuestGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
AQuestGiver::AQuestGiver()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
}

void AQuestGiver::BeginPlay()
{
	Super::BeginPlay();
	
}

void AQuestGiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuestGiver::Interact_Implementation(AActor* Interactor)
{
	if (!Interactor)
	{
		return;
	}

	if (QuestToGive)
	{
		if (UQuestComponent* QuestComp = Interactor->FindComponentByClass<UQuestComponent>())
		{
			QuestComp->AddQuest(QuestToGive);
		}
	}

	if (!TargetID.IsNone())
	{
		if (AQuestGameState* GS = Cast<AQuestGameState>(UGameplayStatics::GetGameState(this)))
		{
			GS->ReportGameplayObjective(EQuestObjectiveType::Interact, TargetID, 1);
		}
	}
}