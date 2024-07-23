// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include "Components/Scrollbox.h"
#include "dwBattleFactionEntry.generated.h"

/**
 * 
 */
UCLASS()
class DIRTYWAR_API UdwBattleFactionEntry : public UUserWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwBattleFactionText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwNodeBattleFacReg;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwNodeBattleFacUnits;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwNodeBattleFacControl;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* dwNodeBattleFactionImg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* dwNodeBattleFacUnitScroll;

};
