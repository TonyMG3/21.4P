// Fill out your copyright notice in the Description page of Project Settings.


#include "BonusSpeed.h"
#include "Snake.h"

// Sets default values
ABonusSpeed::ABonusSpeed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABonusSpeed::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABonusSpeed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABonusSpeed::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnake>(Interactor);

		if (IsValid(Snake))
		{
			Snake -> MovementSpeed = Snake -> MovementSpeed * 0.50f;
			Snake->SetActorTickInterval(Snake->MovementSpeed);
		
			
			

		}
	}
}
