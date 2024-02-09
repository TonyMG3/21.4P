// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake.h"
#include "SnakeElementBase.h"
#include "Interactable.h"

// Sets default values
ASnake::ASnake()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 10.f;
	LastMoveDirection = EMovomentDirection::DOWN;

}

// Called when the game starts or when spawned
void ASnake::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(4);
	
}

// Called every frame
void ASnake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);

}

void ASnake :: AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i) 
	
	{
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 0);

		if (SnakeElements.Num() > 0)
		{
			NewLocation = SnakeElements[SnakeElements.Num() - 1]->GetActorLocation();
		}
	    FTransform NewTransform(NewLocation);
	    ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NewSnakeElem->SnakeOwner = this;
		
	    int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
		if (ElemIndex == 0)
		{
			NewSnakeElem->SetFirstElementType();
			
		}

	

	}

	
}

void ASnake::Move(float DeltaTime)
{
	FVector MovementVector(FVector::ZeroVector);
	
	switch (LastMoveDirection)
	{
		
	case EMovomentDirection::UP:
		MovementVector.X += ElementSize;
		break;
	case EMovomentDirection::DOWN:
		MovementVector.X -= ElementSize;
		break;
	case EMovomentDirection::LEFT:
		MovementVector.Y += ElementSize;
		break;
	case EMovomentDirection::RIGHT:
		MovementVector.Y -= ElementSize;
		break;
		
	}
	Moving = false;
	SnakeElements[0]->ToggleCollision();

	for (int i = SnakeElements.Num() - 1; i > 0; i--) 
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		FVector PrevLocation = PrevElement -> GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();
	
}

void ASnake::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if(IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this, bIsFirst);
		}
	}
}

