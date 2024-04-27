// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialInterface.h"
#include "dwNodeConnectionMaterial.generated.h"

/**
 * 
 */
UCLASS()
class DIRTYWAR_API UdwNodeConnectionMaterial : public UMaterialInterface
{
	GENERATED_BODY()
	
public:
	UdwNodeConnectionMaterial(const FObjectInitializer& ObjectInitializer);
};
