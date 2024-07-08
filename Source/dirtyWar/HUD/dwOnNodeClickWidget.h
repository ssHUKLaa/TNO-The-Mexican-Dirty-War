// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Components/TextBlock.h>
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include "Components/Border.h"
#include "dwNodeNameWidget.h"
#include "Components/Scrollbox.h"
#include <Components/ProgressBar.h>
#include "dwOnNodeClickWidget.generated.h"


/**
 * 
 */
UCLASS()
class DIRTYWAR_API UdwOnNodeClickWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void slideOutAnim();

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void SetNodeText(FString name);

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void SetNodeUnits(TArray<URegimentType*> nodeUnits, AmouseController* ctrl);

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void SetNodeIntelProg(int32 intel);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwNodeText;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* NodeClickedBorder;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* dwNodeExitButton;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* SlideIN; 

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* dwNodeUnitList;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* dwNodeIntelProgbar;


};
