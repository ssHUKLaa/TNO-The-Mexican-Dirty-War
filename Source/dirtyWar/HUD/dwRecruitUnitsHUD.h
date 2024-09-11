// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include "dwRecruitUnitsHUD.generated.h"

/**
 * 
 */
UCLASS()
class DIRTYWAR_API UdwRecruitUnitsHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* slideIn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* dwGovnExitBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwRecruitInfText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwRecruitMotText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwRecruitSupText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwRecruitFigText;

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void closeHUD();

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void setEquipmentNumbers();
	
};
