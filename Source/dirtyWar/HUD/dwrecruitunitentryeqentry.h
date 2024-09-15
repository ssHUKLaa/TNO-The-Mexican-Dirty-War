// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "dwrecruitunitentryeqentry.generated.h"

/**
 * 
 */
UCLASS()
class DIRTYWAR_API Udwrecruitunitentryeqentry : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwEqName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* dwEqIcon;
};
