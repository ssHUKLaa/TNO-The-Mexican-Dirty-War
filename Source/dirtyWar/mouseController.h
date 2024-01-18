// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "mousePawn.h"
#include "mouseController.generated.h"


/**
 * 
 */
UCLASS()
class DIRTYWAR_API AmouseController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AmouseController();
	void PossessPawn(AmousePawn* PawnToPossess);
	
	

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void Zoom(float Value);


private:
	AmousePawn* ControlledPawn;



	void Tick(float DeltaTime) override;

	// Functions to handle input
	
};
