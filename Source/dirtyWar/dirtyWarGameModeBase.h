// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "dwNode.h"
#include "Engine/DataTable.h"
#include "dirtyWarGameModeBase.generated.h"



/**
 * 
 */
UCLASS()
class DIRTYWAR_API AdirtyWarGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AdirtyWarGameModeBase();

	virtual void BeginPlay() override;
	virtual void SpawnNodes(UDataTable*);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, AdwNode*> IDNodeMap;
	TArray<AdwNode*> DWNodes;
	
	
};
