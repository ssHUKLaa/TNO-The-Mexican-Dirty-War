// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
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
	void setUnitNameText(FString nameText, FString unitType);


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwUnitEntryNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwUnitTypeName;




	
};
