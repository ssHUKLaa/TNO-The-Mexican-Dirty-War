// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include "dwNodeNameWidget.generated.h"


/**
 * 
 */
UCLASS()
class DIRTYWAR_API UdwNodeNameWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:


	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void SetTextInWidget(const FText& NewText);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwDateTime;

};
