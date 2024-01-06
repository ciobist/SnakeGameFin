// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

class ASnakeElementBase;

UENUM()
enum class EMovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class SNAKEGAME_API ASnakeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBase();

	UPROPERTY(BlueprintReadWrite)
	float MovementSpeed;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeElementBase>SnakeElementClass;

	UPROPERTY(EditDefaultsOnly)
	float ElementSize;

	UPROPERTY()
	TArray<ASnakeElementBase*>SnakeElements;

	UPROPERTY()
	FVector SnakeSize;

	UPROPERTY()
	EMovementDirection LastMoveDirection;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddSnakeElement(int ElementsNum = 1);

	void Stop(float *Speed);

	void Move();
	UFUNCTION()
	void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);
};
