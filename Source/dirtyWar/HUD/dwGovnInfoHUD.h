// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/TextBlock.h>
#include <Components/ProgressBar.h>
#include <Components/Image.h>
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

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* dwUSAOvrSuppProg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwASStrongText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwASSlightText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwASWeakText;

	

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwASNoText;

	UTextBlock* dwTextToFlash;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwUSAmilSuppText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwUSAintSuppText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwUSAmedSuppText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwUSAgovSuppText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* dwUSAmilSuppProg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* dwUSAintSuppProg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* dwUSAmedSuppProg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* dwUSAgovSuppProg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* dwASSdot1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* dwASSdot2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* dwASSdot3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* dwASSdot4;

	UImage* dwASSdotFlashing;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwDOMSStrongText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwDOMSSlightText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwDOMSWeakText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwDOMSNoText;

	UTextBlock* dwDOMSFlashingText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* dwMEXSdot1;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* dwMEXSdot2;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* dwMEXSdot3;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* dwMEXSdot4;

	UImage* dwMEXSdotFlashing;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* dwMEXOvrSuppProg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* dwDOMintsupProg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* dwDOMintmonProg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* dwDOMindsupProg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* dwDOMindmonProg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* dwDOMworksupProg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwDOMIntSuppText;
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwDOMIndSuppText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* dwDOMworSuppText;

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void closeHUD();
	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void updateAllSupportInfo(int32 mil, int32 intel, int32 med, int32 gov);
	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void updateDomesticSupport(int32 intsup, int32 intmon, int32 indsup, int32 indmon, int32 worksup);
	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void detSupportLevel(int32 value, FString& supVal, FSlateColor& colVal);

	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void ToggleTextColor();

	void ToggleTextColorMEX();

private:
	FTimerHandle FlashTimerHandle;
	FSlateColor Color1;
	FSlateColor Color2;

	FSlateColor MEXColor1;
	FSlateColor MEXColor2;
	bool bUseColor1;
};
