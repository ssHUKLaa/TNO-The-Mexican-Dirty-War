// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Components/CapsuleComponent.h>
#include "mousePawn.generated.h"



UCLASS()
class DIRTYWAR_API AmousePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AmousePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	


public:	
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;


	void AdjustPawnMovement(const FVector2D& ScrollDirection);

	void Zoom(float ZoomAmount);

	
private:
	

	// Variables for movement speed
	UPROPERTY(EditAnywhere)
	float MoveSpeed = 5000.0f;

	FVector CurrentVelocity;
	FVector ForwardMovement;
	FVector RightMovement;

	void PossessedBy(AController* NewController);

};
