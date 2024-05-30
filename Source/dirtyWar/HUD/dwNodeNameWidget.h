// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/TextBlock.h>
#include <map>
#include "Components/Border.h"
#include <Components/Button.h>
#include <Components/Image.h>
#include "Slate/SlateBrushAsset.h"
#include "dwGovnInfoHUD.h"
#include "Styling/SlateBrush.h"
#include "dwWpnsMnuHUD.h"
#include "dwRecruitUnitsHUD.h"
#include "dwNodeNameWidget.generated.h"





/**
 * 
 */
UCLASS()
class DIRTYWAR_API UdwNodeNameWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	std::map<int, FString> monthMap = {
	{1, "January"}, {2, "February"}, {3, "March"}, {4, "April"},
	{5, "May"}, {6, "June"}, {7, "July"}, {8, "August"},
	{9, "September"}, {10, "October"}, {11, "November"}, {12, "December"}
	};
public:
	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void toggleBottomLeftBorderState();
	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void SetTextInWidget(const int& year, const int& month, const int& day, const int& hour);

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void setControllerStill();

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void freeController();

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void getNewDate();
	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void ondwSlowDownTimeClicked();
	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void ondwSpeedUpTimeClicked();

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void openGovnHUDTab();

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void openWeaponsHUDTab();

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void openUnitsHUDTab();

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void openClearAllTopTabs(AmouseController* PlayerController);

	UPROPERTY()
	UdwGovnInfoHUD* GovnInfoHUD;

	UPROPERTY()
	UdwWpnsMnuHUD* WpnsInfoHUD;

	UPROPERTY()
	UdwRecruitUnitsHUD* RecruitUnitHUD;


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* dwTopLeftHeader;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwDateTime;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* dwSpeedUpTime;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* dwSlowDownTime;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* dwBtmLftBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UBorder* dwBottomLeftBorder;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* slideOut;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* dwTopLeftGovnBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* dwTopLeftMnufBtn;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* dwTopleftRecruitBtn;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	bool bottomleftGUIState = false;

	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void NativeOnMouseLeave(const FPointerEvent& InMouseEvent);

	virtual void NativeConstruct() override;
	
protected:
	
	
};
