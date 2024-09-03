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
#include "HUD/dwGovnInfoHUD.h"
#include "nodeStruct.h"
#include "dwNodeConnection.h"
#include "dirtyWarGameModeBase.h"
#include "HUD/dwBattleFactionEntry.h"
#include "HUD/dwNodeBattleUnitEntryHUD.h"
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

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdwNodeBattleHUD> NodeBattleHUDClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdwBattleFactionEntry> NodeBattleHUDFactionClass;

	UPROPERTY()
	class UdwOnNodeClickWidget* NodeClickedHUD;
	bool overHUD = false;

	UPROPERTY()
	class UdwNodeBattleHUD* NodeBattleHUDSelected;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdwGovnInfoHUD> GovnInfoHUDClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdwRecruitUnitsHUD> RecruitUnitHUDClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdwNodeUnitEntry> UnitEntryHUDClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UdwNodeBattleUnitEntryHUD> BattleUnitEntryHUDClass;

	UPROPERTY(EditAnywhere)
	TMap<URegimentType*,AdwNode*> player_AllUnits;

	UPROPERTY(EditAnywhere)
	TArray<AdwNode*> connectionsMovingUnit;

	void handleConnectionReUp();

	UPROPERTY()
	UdwGovnInfoHUD* GovnInfoHUD;
	
	void NodeClicked(AdwNode* NodeID);

	class UdwNodeBattleHUD* startNodeBattleHUD(AdwNode* node);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	void BindSpaceBarAction();

	void HandleRightClick();

	

	void HandleClick();

	TArray<FNodeDistancePair> utilAStarSearch(AdwNode* start, AdwNode* end, AdirtyWarGameModeBase* YourGameMode);

	FGameDate convertDistToGameTime(float dist);

	

	

	float GetDistanceBetweenNodes(AdwNode* Node1, AdwNode* Node2);
	void Zoom(float Value);

	

private:
	AmousePawn* ControlledPawn;
	void Tick(float DeltaTime) override;
	AreticleActor* newReticle;
	
	
	
	
	
};
