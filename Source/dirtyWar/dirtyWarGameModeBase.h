// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "dwNode.h"
#include "HUD/dwNodeNameWidget.h"
#include "HUD/dwNodeBattleHUD.h"
#include "Engine/DataTable.h"
#include "dwNodeConnection.h"
#include "dirtyWarGameModeBase.generated.h"




USTRUCT(BlueprintType)
struct FGameDate
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 year;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 month;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 hour;

	FGameDate() : year(0), month(0), day(0), hour(0) {}

	FGameDate(int32 InYear, int32 InMonth, int32 InDay, int32 InHour)
		: year(InYear), month(InMonth), day(InDay), hour(InHour)
	{
	}
};

/**
 *
 */
USTRUCT(BlueprintType)
struct FNodeDistancePair
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AdwNode* Node;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameDate Distance;

	FNodeDistancePair()
		: Node(nullptr), Distance(FGameDate())
	{
	}

	FNodeDistancePair(AdwNode* InNode, FGameDate InDistance)
		: Node(InNode), Distance(InDistance)
	{
	}
};

USTRUCT(BlueprintType)
struct FRegimentMovementData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	URegimentType* RegimentType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	TArray<FNodeDistancePair> NodeDistances;

	// Default constructor
	FRegimentMovementData()
	{
		RegimentType = nullptr;
	}

	// Constructor with parameters
	FRegimentMovementData(URegimentType* InRegimentType, const TArray<FNodeDistancePair>& InNodeDistances)
		: RegimentType(InRegimentType)
		, NodeDistances(InNodeDistances)
	{
	}
};

USTRUCT(BlueprintType)
struct FnodeInBattleValues
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameDate timeTillNextPhase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 phase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 sideOneWinning;

	FnodeInBattleValues()
		: timeTillNextPhase(0, 0, 0, 0), phase(0), sideOneWinning(0)
	{
	}

	FnodeInBattleValues(FGameDate timeTillNextPhase, int32 phase, int32 sideOneWinning)
		: timeTillNextPhase(timeTillNextPhase)
		, phase(phase)
		, sideOneWinning(sideOneWinning)
	{
	}
};


UCLASS()
class DIRTYWAR_API AdirtyWarGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	FTimerHandle GAME_TIMETIMER;
	int DaysPassed = 0;



public:

	AdirtyWarGameModeBase();

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	FSlateBrush setBrushesFromLoad(UTexture2D* helper);

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	float calcUnitDmg(URegimentType* unit);

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	float GetDistanceBetweenNodes(AdwNode* Node1, AdwNode* Node2);

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	FGameDate convertDistToGameTime(float dist);

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	TArray<FNodeDistancePair> utilAStarSearch(AdwNode* Start, AdwNode* End);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSlateBrush> ButtonBrushes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString,FSlateBrush> factionBrushes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSlateBrush> frameBrushes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSlateBrush> unitBrushes;

	bool GAME_UNPAUSED = false;
	int GAME_SPEED = 5;	
	
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void SpawnNodes(UDataTable* nodeTable);
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	bool ShouldHappen(int percentage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, AdwNode*> IDNodeMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AdwNode*> DWNodes;
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	float calculateGameSpeedConversion();
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void ModifyTime(int modif, UdwNodeNameWidget* PlayerHUD);
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void HandleSpaceBar(UdwNodeNameWidget* PlayerHUD);
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void GameSpeedTimerManager(UdwNodeNameWidget* PlayerHUD);
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void IterGameTime(UdwNodeNameWidget* PlayerHUD);
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	URequiredEquipments* setUpRequiredEquipments(UEquipmentType* thingy, int32 amountt);

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameDate currentDate = { 1965,1,1,0 };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GAME_startYear = 1965;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GAME_endYear = 1975;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<AdwNode*, FnodeInBattleValues> GAME_nodesInBattle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString,UFactionType*> GAME_allFactions = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UUnitType*> GAME_allUnitTypes = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UEquipmentType*> GAME_allEquipmentTypes = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<UEquipmentType*, int32> GAME_currentEquipment = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRegimentMovementData> GAME_movingUnits = {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GAME_BASEINTELDECAY = 2.f;

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void GAME_ONHOURLY();
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void GAME_ONDAILY();
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void GAME_ONWEEKLY();
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void GAME_ONMONTHLY();
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void GAME_ONYEARLY();

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void GenerateIntel();
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void decrementFGameDate(FGameDate& date, const FGameDate& amount);
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void moveUnits();

	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void createUnitPath(AdwNode* ClickedNode, AmouseController* control);
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void startNodeBattles();
	UFUNCTION(BlueprintCallable, Category = "My Functions")
	void cleanUpUnitRefs(URegimentType* unit);



};

