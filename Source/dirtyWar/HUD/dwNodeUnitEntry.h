// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Image.h>
#include "../nodeStruct.h"
#include <Components/Button.h>
#include <Components/ProgressBar.h>
#include "dwNodeUnitEntry.generated.h"


/**
 * 
 */
UCLASS()
class DIRTYWAR_API UdwNodeUnitEntry : public UUserWidget
{
	GENERATED_BODY()

	

public:

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void setUnitNameText(FString nameText, FString unitType, int32 regSize, int32 orgPerc);

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void setTravelableProgBar();

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void onUnitEntrySelected();

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void onUnitEntryHovered();

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void onUnitEntryUnHovered();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwUnitEntryNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwUnitTypeName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwUnitEntryRegimentText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* dwUnitSelOutline;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* dwUnitEntryBtnSel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool entrySelected = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	URegimentType* associatedRegiment;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* TravelableNodeDistBar;

	virtual void NativeConstruct() override;
	
};
