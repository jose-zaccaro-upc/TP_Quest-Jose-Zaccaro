// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Actor/QuestLocation.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Public/Game_State/QuestGameState.h"


AQuestLocation::AQuestLocation()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	RootComponent = BoxCollision;
	BoxCollision->SetCollisionProfileName(TEXT("Trigger"));
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AQuestLocation::OnOverlapBegin);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AQuestLocation::BeginPlay()
{
	Super::BeginPlay();
	
}

void AQuestLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AQuestLocation::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
								   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
								   bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bAlreadyReached && Cast<ACharacter>(OtherActor))
	{
		if (AQuestGameState* GS = Cast<AQuestGameState>(UGameplayStatics::GetGameState(this)))
		{
			bAlreadyReached = true;
			GS->ReportGameplayObjective(EQuestObjectiveType::ReachLocation, TargetID, 1);
		}
	}
}

