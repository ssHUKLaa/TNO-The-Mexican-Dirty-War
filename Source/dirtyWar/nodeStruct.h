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
