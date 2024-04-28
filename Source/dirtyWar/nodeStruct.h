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
USTRUCT(BlueprintType)
struct FFactionType
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperFlipbook* nodeImage;
	FFactionType() : Name(""), Description(""), Association(-1), totalUnits(0), nodeImage() {}

	FFactionType(FString curName, FString curDesc, int32 curAssoc, int32 curUnits, UPaperFlipbook* curFlip)
		: Name(curName), Description(curDesc), Association(curAssoc), totalUnits(curUnits), nodeImage(curFlip)
	{
	}
};
USTRUCT(BlueprintType)
struct FEquipmentType
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double powerMult;

	FEquipmentType() : Name(""), Description(""), powerMult(0) { }

	FEquipmentType(FString curName, FString curDesc,double curMult)
		: Name(curName), Description(curDesc), powerMult(curMult)
	{
	}

};
USTRUCT(BlueprintType)
struct FRequiredEquipments
{
	GENERATED_BODY()
public:
	FEquipmentType equipment;
	int32 amount;

	FRequiredEquipments() : equipment(), amount(0) { }

	FRequiredEquipments(FEquipmentType curEquipment, int32 curAmount)
		: equipment(curEquipment), amount(curAmount)
	{
	}
};
USTRUCT(BlueprintType)
struct FUnitType
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
	int32 baseTacticsLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double baseIntelGeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 basePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRequiredEquipments> requiredEquipment;

	FUnitType() : Name(""), Description(""), techLevel(0), healthPoints(0), baseTravelableDistance(0), baseTacticsLevel(0), baseIntelGeneration(0), basePower(0) {}

	FUnitType(FString curName, FString curDesc, int32 curTech, int32 curHealth, int32 curTravel, int32 curTactic, double curIntel, int32 curPower, TArray<FRequiredEquipments> curReq)
		: Name(curName), Description(curDesc), techLevel(curTech), healthPoints(curHealth), baseTravelableDistance(curTravel), baseTacticsLevel(curTactic), baseIntelGeneration(curIntel), basePower(curPower), requiredEquipment(curReq)
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
