#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"
#include "Food.h"


// Sets default values
ASnakeBase::ASnakeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 10.f;
	LastMoveDirection = EMovementDirection::DOWN;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(5);
	
}

void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i)
	{
		
		FVector NewLocation(SnakeElements.Num() * ElementSize, 0, 55);
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NewSnakeElem->SnakeOwner = this;
		NewSnakeElem->SetActorHiddenInGame(true);
		int32 ElementIndex = SnakeElements.Add(NewSnakeElem);

		if (ElementIndex == 0) 
		{
			NewSnakeElem->SetFirstElementType();
			
		}
		
	}	
}

void ASnakeBase::Stop(float *Speed)
{
	(*Speed) = 0;
}


void ASnakeBase::Move()
{
	FVector MovementVector(FVector::ZeroVector);
	MovementSpeed = ElementSize ;


	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:

		MovementVector.X += MovementSpeed;
		break;
		
	case EMovementDirection::DOWN:

		MovementVector.X -= MovementSpeed;
		break;

	case EMovementDirection::LEFT:

		MovementVector.Y += MovementSpeed;
		break;

	case EMovementDirection::RIGHT:

		MovementVector.Y -= MovementSpeed;
		break;
	}

	//AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleColission();

	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];
		SnakeElements[0]->SetActorHiddenInGame(false);
		SnakeElements[i]->SetActorHiddenInGame(false);
		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleColission();
}




void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		IInteractable* InteraclableInterface = Cast<IInteractable>(Other);
		if (InteraclableInterface)
		{
			InteraclableInterface->Interact(this, bIsFirst);
		}

	}

	

}
