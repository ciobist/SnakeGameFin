#include "Food.h"
#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "ctime"
#include "DrawDebugHelpers.h"



AFood::AFood()
{
	Location == FVector(0, 0, 0);
	PrimaryActorTick.bCanEverTick = true;

}


void AFood::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called when the game starts or when spawned

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFood::CoordinatesGeneration(FVector *Locations)
{
	int srand(time(NULL));
	int Xcoordinates = -450 + 100 * (rand() % 9);
	int Ycoordinates = -450 + 100 * (rand() % 9);
	FVector Coordinates(Xcoordinates, Ycoordinates, 55);
	(*Locations) = Coordinates;

}

void AFood::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{

			Snake->AddSnakeElement();

			CoordinatesGeneration(&Location);

			FHitResult Hit;
			FVector Start = Location;
			FVector End = Start + FVector(10, 10, 0);
			FCollisionQueryParams TraceParams;
			GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ECC_WorldStatic, TraceParams);
			//DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 2.0f);

			while (Hit.bBlockingHit)
			{
				CoordinatesGeneration(&Location);
				Start = Location;
				End = Start + FVector(10, 10, 0);
				GetWorld()->LineTraceSingleByObjectType(Hit, Start, End, ECC_WorldStatic, TraceParams);
				//DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 2.0f);
				GEngine->AddOnScreenDebugMessage(-1, 25.0f, FColor::Red, TEXT("Changed"));
			}
			if (!Hit.bBlockingHit)
			{
				SetActorLocation(Location);
				//GEngine->AddOnScreenDebugMessage(-1, 25.0f, FColor::Green, TEXT("Nice"));
				
			}
			

		}


	}
	
}



