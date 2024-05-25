// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/TextBlock.h>
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "dwOnNodeClickWidget.generated.h"


/**
 * 
 */
UCLASS()
class DIRTYWAR_API UdwOnNodeClickWidget : public UUserWidget
{
	GENERATED_BODY()
	


public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void slideOutAnim();

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void SetNodeText(FString name);
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwNodeText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* NodeClickedBorder;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* SlideIN; 
};
