// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Actor/QuestItemCollect.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Public/Game_State/QuestGameState.h"


AQuestItemCollect::AQuestItemCollect()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	RootComponent = SphereCollision;
	SphereCollision->SetCollisionProfileName(TEXT("Trigger"));
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AQuestItemCollect::OnOverlapBegin);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AQuestItemCollect::BeginPlay()
{
	Super::BeginPlay();
	
}

void AQuestItemCollect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AQuestItemCollect::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
									  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
									  bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACharacter>(OtherActor))
	{
		if (AQuestGameState* GS = Cast<AQuestGameState>(UGameplayStatics::GetGameState(this)))
		{
			GS->ReportGameplayObjective(EQuestObjectiveType::Collect, TargetID, Amount);
			Destroy();
		}
	}
}