// Copyright Epic Games, Inc. All Rights Reserved.


#include "SnakeGameGameModeBase.h"
#include "Food.h"

void ASnakeGameGameModeBase::BeginPlay()
{
	FTimerHandle FoodTimer;

	GetWorld()->GetTimerManager().SetTimer(FoodTimer, this, &ASnakeGameGameModeBase::SpawnSomething, 5.0f, true);
}

void ASnakeGameGameModeBase::Tick(float DeltaTime)

{
	Super::Tick(DeltaTime);
}

void ASnakeGameGameModeBase::SpawnSomething()
{
	int32 RandomIndex = FMath::RandRange(0, SpawnActorArray.Num() - 1);
	auto ClassForSpawn = SpawnActorArray[RandomIndex];

	int RandomX = FMath::RandRange(-437, 437);
	int RandomY = FMath::RandRange(-437, 437);

	if (ClassForSpawn)
	{
		GetWorld()->SpawnActor<AActor>(ClassForSpawn, FTransform(FVector(RandomX, RandomY, 0)));
	}

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Spawn something"));
}
