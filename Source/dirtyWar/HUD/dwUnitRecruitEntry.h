// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/ScrollBox.h>
#include <Components/TextBlock.h>
#include "dwUnitRecruitEntry.generated.h"

/**
 * 
 */
UCLASS()
class DIRTYWAR_API UdwUnitRecruitEntry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwRecruitUnitName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* dwRecruitUnitEqScBox;

};
