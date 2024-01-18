// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "nodeStruct.generated.h"


/**
 * 
 */
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

	FnodeStruct();

};
