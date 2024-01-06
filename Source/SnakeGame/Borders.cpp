
#include "Borders.h"
#include "SnakeBase.h"
#include "SnakeElementBase.h"

// Sets default values
ABorders::ABorders()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABorders::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABorders::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABorders::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			Snake->Stop(&(Snake->MovementSpeed));
			Snake->Destroy();

		}


	}

}

