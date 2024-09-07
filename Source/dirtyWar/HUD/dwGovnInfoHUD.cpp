// Fill out your copyright notice in the Description page of Project Settings.


#include "dwGovnInfoHUD.h"
#include <dirtyWar/mouseController.h>
#include "TimerManager.h"

void UdwGovnInfoHUD::NativeConstruct()
{
    Super::NativeConstruct();

    dwGovnExitBtn->OnClicked.AddUniqueDynamic(this, &UdwGovnInfoHUD::closeHUD);

    if (slideIn)
    {
        PlayAnimationForward(slideIn);

    }
}

void UdwGovnInfoHUD::closeHUD()
{
    AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
    this->RemoveFromParent();
    PlayerController->GovnInfoHUD = nullptr;
}

void UdwGovnInfoHUD::updateAllSupportInfo(int32 mil,int32 intel, int32 med, int32 gov)
{
    dwUSAmilSuppProg->SetPercent(static_cast<float>(mil) / 100);
    dwUSAintSuppProg->SetPercent(static_cast<float>(intel) / 100);
    dwUSAmedSuppProg->SetPercent(static_cast<float>(med) / 100);
    dwUSAgovSuppProg->SetPercent(static_cast<float>(gov) / 100);

    int32 ovrall = (mil + intel + med + gov) / 4;
    dwUSAOvrSuppProg->SetPercent(static_cast<float>(ovrall) / 100);
    
    if (ovrall <= 25)
    {
        dwTextToFlash = dwASNoText;
        dwASSdotFlashing = dwASSdot4;
        Color1 = FSlateColor(FLinearColor(0.1, 0.022759, 0.023175, 0.25));
        Color2 = FSlateColor(FLinearColor(0.1, 0.022759, 0.023175, 1.0));
    }
    else if (ovrall > 25 && ovrall <= 40)
    {
        dwTextToFlash = dwASWeakText;
        dwASSdotFlashing = dwASSdot3;
        Color1 = FSlateColor(FLinearColor(0.64448, 0.181164, 0.184475, 0.25));
        Color2 = FSlateColor(FLinearColor(0.64448, 0.181164, 0.184475, 1.0));
    }
    else if (ovrall>40 && ovrall<=75)
    {
        dwTextToFlash = dwASSlightText;
        dwASSdotFlashing = dwASSdot2;
        Color1 = FSlateColor(FLinearColor(0.234551, 0.822786, 0.270498, 0.25));
        Color2 = FSlateColor(FLinearColor(0.234551, 0.822786, 0.270498, 1.0));
    }
    else
    {
        dwTextToFlash = dwASStrongText;
        dwASSdotFlashing = dwASSdot1;
        Color2 = FSlateColor(FLinearColor(0.0, 0.533333, 0.032597, 1.0));
    }
    GetWorld()->GetTimerManager().SetTimer(FlashTimerHandle, this, &UdwGovnInfoHUD::ToggleTextColor, 1.0f, true);

    FString supportValue = "";
    FSlateColor colourValue;
    
    detSupportLevel(mil,supportValue,colourValue);

    dwUSAmilSuppText->SetText(FText::FromString(supportValue + " SUPPORT"));

    dwUSAmilSuppText->SetColorAndOpacity(colourValue);
    detSupportLevel(intel, supportValue, colourValue);
    dwUSAintSuppText->SetText(FText::FromString(supportValue + " SUPPORT"));
    dwUSAintSuppText->SetColorAndOpacity(colourValue);
    detSupportLevel(med, supportValue, colourValue);
    dwUSAmedSuppText->SetText(FText::FromString(supportValue + " SUPPORT"));
    dwUSAmedSuppText->SetColorAndOpacity(colourValue);
    detSupportLevel(gov, supportValue, colourValue);
    dwUSAgovSuppText->SetText(FText::FromString(supportValue + " SUPPORT"));
    dwUSAgovSuppText->SetColorAndOpacity(colourValue);
}   

void UdwGovnInfoHUD::detSupportLevel(int32 value, FString& supVal, FSlateColor& colVal)
{
    if (value <= 25)
    {
        supVal = "NO";
        FLinearColor LinearColor(0.1, 0.022759, 0.023175, 1.0);
        colVal = FSlateColor(LinearColor);
    }
    else if (value > 25 && value <= 40)
    {
        supVal = "WEAK";
        FLinearColor LinearColor(0.64448, 0.181164, 0.184475, 1.0);
        colVal = FSlateColor(LinearColor);
    }
    else if (value > 40 && value <= 75)
    {
        supVal = "SLIGHT";
        FLinearColor LinearColor(0.234551, 0.822786, 0.270498, 1.0);
        colVal = FSlateColor(LinearColor);
    }
    else
    {
        supVal = "STRONG";
        FLinearColor LinearColor(0.0, 0.533333, 0.032597, 1.0);
        colVal = FSlateColor(LinearColor);
    }
}

void UdwGovnInfoHUD::ToggleTextColor()
{
    if (dwTextToFlash)
    {
        if (bUseColor1)
        {
            dwTextToFlash->SetColorAndOpacity(Color1);
            dwASSdotFlashing->SetColorAndOpacity(Color1.GetSpecifiedColor());
        }
        else
        {
            dwTextToFlash->SetColorAndOpacity(Color2);
            dwASSdotFlashing->SetColorAndOpacity(Color2.GetSpecifiedColor());
        }
        bUseColor1 = !bUseColor1;
    }
}
