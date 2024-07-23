// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>

#include "dwGovnInfoHUD.generated.h"

/**
 * 
 */
UCLASS()
class DIRTYWAR_API UdwGovnInfoHUD : public UUserWidget
{
	GENERATED_BODY()
	

public:

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* slideIn;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* dwGovnExitBtn;

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void closeHUD();
};
