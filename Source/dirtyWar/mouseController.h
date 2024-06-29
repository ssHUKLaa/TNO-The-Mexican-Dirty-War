// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "mousePawn.h"
#include "reticleActor.h"
#include "dwNode.h"
#include "HUD/dwNodeNameWidget.h"
#include "HUD/dwOnNodeClickWidget.h"
#include "HUD/dwNodeUnitEntry.h"
#include "nodeStruct.h"
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
	AdwNode* selectedNode;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdwNodeNameWidget> playerHUDClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdwWpnsMnuHUD> WpnsInfoHUDClass;

	UPROPERTY()
	class UdwNodeNameWidget* PlayerHUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdwOnNodeClickWidget> NodeClickedHUDClass;

	UPROPERTY()
	class UdwOnNodeClickWidget* NodeClickedHUD;
	bool overHUD = false;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdwGovnInfoHUD> GovnInfoHUDClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdwRecruitUnitsHUD> RecruitUnitHUDClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdwNodeUnitEntry> UnitEntryHUDClass;

	UPROPERTY(EditAnywhere)
	TMap<URegimentType*,AdwNode*> player_AllUnits;
	

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void BindSpaceBarAction();

	

	void HandleClick();

	

	void NodeClicked(AdwNode* NodeID);


	void Zoom(float Value);

	

private:
	AmousePawn* ControlledPawn;
	void Tick(float DeltaTime) override;
	AreticleActor* newReticle;
	
	
	
	
	
};
