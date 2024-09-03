// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include <PaperFlipbook.h>
#include "nodeStruct.generated.h"



/**
 * 
 */



UCLASS(BlueprintType)
class DIRTYWAR_API UFactionType : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Association; // 0 - Government, 1 - Leftist, 2 - Rightist

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 totalUnits;

	UPROPERTY(EditAnywhere)
	FVector4d factionColour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* nodeImage;


	UFactionType() : Name(""), Description(""), Association(-1), totalUnits(0), nodeImage(), factionColour(0,0,0,0){}

	UFactionType(FString curName, FString curDesc, int32 curAssoc, int32 curUnits, UPaperFlipbook* curFlip, FVector4d curColour)
		: Name(curName), Description(curDesc), Association(curAssoc), totalUnits(curUnits), nodeImage(curFlip), factionColour(curColour)
	{
	}
};
UCLASS(BlueprintType)
class DIRTYWAR_API UEquipmentType : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double powerMult;

	UEquipmentType() : Name(""), Description(""), powerMult(0) { }

	UEquipmentType(FString curName, FString curDesc,double curMult)
		: Name(curName), Description(curDesc), powerMult(curMult)
	{
	}

};
UCLASS(BlueprintType)
class DIRTYWAR_API URequiredEquipments : public UObject
{
	GENERATED_BODY()
public:
	UEquipmentType* equipment;
	int32 amount;

	URequiredEquipments() : equipment(), amount(0) { }

	URequiredEquipments(UEquipmentType* curEquipment, int32 curAmount)
		: equipment(curEquipment), amount(curAmount)
	{
	}
};
UCLASS(BlueprintType)
class DIRTYWAR_API UUnitType : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 techLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 healthPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 baseTravelableDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float baseTacticsLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double baseIntelGeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float basePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<URequiredEquipments*> requiredEquipment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FSlateBrush unitEntryIcon;

	UUnitType() : Name(""), Description(""), techLevel(0), healthPoints(0), baseTravelableDistance(0), baseTacticsLevel(0), baseIntelGeneration(0), basePower(0), unitEntryIcon() {}

	UUnitType(FString curName, FString curDesc, int32 curTech, int32 curHealth, int32 curTravel, int32 curTactic, double curIntel, int32 curPower, TArray<URequiredEquipments*> curReq, FSlateBrush unitEntryIcon)
		: Name(curName), Description(curDesc), techLevel(curTech), healthPoints(curHealth), baseTravelableDistance(curTravel), baseTacticsLevel(curTactic), baseIntelGeneration(curIntel), basePower(curPower), requiredEquipment(curReq), unitEntryIcon(unitEntryIcon)
	{
	}
};

UCLASS(BlueprintType)
class DIRTYWAR_API URegimentType : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUnitType* associatedUnit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UFactionType* associatedFaction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 unitAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PercentOrganized;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 nodesMovable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 regimentLevel;

	URegimentType() : Name(""), associatedUnit(nullptr), associatedFaction(nullptr),unitAmount(0)  {}

	URegimentType(FString curName, UUnitType* curUnitAss, int32 curAmount, UFactionType* curFac, int32 curOrg, int32 curnodemov)
		: Name(curName), associatedUnit(curUnitAss), unitAmount(curAmount), associatedFaction(curFac), PercentOrganized(curOrg), nodesMovable(curnodemov)
	{
	}
};

USTRUCT(BlueprintType)
struct DIRTYWAR_API FnodeStruct : public FTableRowBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NODE_TYPE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 POS_X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 POS_Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> NODE_CONNECTIONS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString LOCATION_NAME;

	FnodeStruct();



};
