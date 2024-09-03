// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include <Components/Button.h>
#include "dwNodeBattleUnitEntryHUD.generated.h"

/**
 * 
 */
UCLASS()
class DIRTYWAR_API UdwNodeBattleUnitEntryHUD : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void setupUnitsAndOrganization(int32 units, int32 org);

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void setupUnitName(FString Name);
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwBattleUnitName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwBattleUnitNum;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwBattleUnitOrg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* dwBattleUnitImg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* dwBattleUnitRegInfo;

};
