// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <Components/Button.h>
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

	void getNewDate();

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwDateTime;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* dwSpeedUpTime;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* dwSlowDownTime;

	virtual void NativeConstruct() override;
protected:

	
};
