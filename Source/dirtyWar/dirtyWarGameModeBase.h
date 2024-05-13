// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "dwNode.h"
#include "dwNodeNameWidget.h"
#include "Engine/DataTable.h"
#include "dirtyWarGameModeBase.generated.h"



/**
 * 
 */

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


UCLASS()
class DIRTYWAR_API AdirtyWarGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	FTimerHandle GAME_TIMETIMER;

public:
	AdirtyWarGameModeBase();


	bool GAME_UNPAUSED = false;
	int GAME_SPEED = 5;	
	

	virtual void BeginPlay() override;
	
	virtual void SpawnNodes(UDataTable*);

	bool ShouldHappen(int percentage);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, AdwNode*> IDNodeMap;
	TArray<AdwNode*> DWNodes;

	float calculateGameSpeedConversion();

	void ModifyTime(int modif, UdwNodeNameWidget* PlayerHUD);

	void HandleSpaceBar(UdwNodeNameWidget* PlayerHUD);

	void GameSpeedTimerManager(UdwNodeNameWidget* PlayerHUD);

	void IterGameTime(UdwNodeNameWidget* PlayerHUD);

	URequiredEquipments* setUpRequiredEquipments(UEquipmentType* thingy, int32 amountt);

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameDate currentDate = { 1965,1,1,0 };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GAME_startYear = 1965;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int GAME_endYear = 1975;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UFactionType*> GAME_allFactions = {};
	TArray<UUnitType*> GAME_allUnitTypes = {};
	TArray<UEquipmentType*> GAME_allEquipmentTypes = {};

	TMap<UUnitType*, AdwNode*> GAME_allUnits;

};

