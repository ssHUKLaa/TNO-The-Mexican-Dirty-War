// Fill out your copyright notice in the Description page of Project Settings.


#include "../mouseController.h"
#include "Components/Button.h"
#include "../dirtyWarGameModeBase.h"
#include "dwNodeNameWidget.h"



void UdwNodeNameWidget::NativeConstruct()
{

    Super::NativeConstruct();

    dwSpeedUpTime->OnClicked.AddUniqueDynamic(this, &UdwNodeNameWidget::ondwSpeedUpTimeClicked);
    dwSlowDownTime->OnClicked.AddUniqueDynamic(this, &UdwNodeNameWidget::ondwSlowDownTimeClicked);

    dwSpeedUpTime->OnHovered.AddUniqueDynamic(this, &UdwNodeNameWidget::setControllerStill);
    dwSlowDownTime->OnHovered.AddUniqueDynamic(this, &UdwNodeNameWidget::setControllerStill);
    dwSpeedUpTime->OnUnhovered.AddUniqueDynamic(this, &UdwNodeNameWidget::freeController);
    dwSlowDownTime->OnUnhovered.AddUniqueDynamic(this, &UdwNodeNameWidget::freeController);

    

    if (dwBtmLftBtn)
    {
        dwBtmLftBtn->OnClicked.AddUniqueDynamic(this, &UdwNodeNameWidget::toggleBottomLeftBorderState);
        UE_LOG(LogTemp, Log, TEXT("dwBtmLftBtn is properly bound"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("dwBtmLftBtn is null"));
    }

    this->toggleBottomLeftBorderState();

}

void UdwNodeNameWidget::toggleBottomLeftBorderState()
{
    UE_LOG(LogTemp, Warning, TEXT("toggleBottomLeftBorderState clicked"));
    if (bottomleftGUIState) {
        if (slideOut)
        {
            UE_LOG(LogTemp, Warning, TEXT("tes"));
            PlayAnimationForward(slideOut);
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("no slideout"));
        }
    }
    else {
        if (slideOut)
        {
            PlayAnimationReverse(slideOut);
            
        }
    }
    bottomleftGUIState = !bottomleftGUIState;
    FButtonStyle ButtonStyle = dwBtmLftBtn->WidgetStyle;
    int intbool = bottomleftGUIState ? 1 : 0;

    AdirtyWarGameModeBase* YourGameMode = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());
    TArray<FSlateBrush> btnBrush = YourGameMode->ButtonBrushes;
    ButtonStyle.SetNormal(btnBrush[intbool]);
    ButtonStyle.SetHovered(btnBrush[intbool]);
    ButtonStyle.SetPressed(btnBrush[intbool]);

    dwBtmLftBtn->SetStyle(ButtonStyle);
}

void UdwNodeNameWidget::SetTextInWidget(const int& year, const int& month, const int& day, const int& hour)
{
    if (dwDateTime)
    {
        FString monthStr = monthMap[month];
        FString dayStr = FString::FromInt(day);
        FString yearStr = FString::FromInt(year);
        FString hourStr = FString::FromInt(hour);
        FText dateText = FText::FromString(hourStr+":00, "+dayStr + " " + monthStr + ", " + yearStr);
        dwDateTime->SetText(dateText);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("dwNodeName is null in UdwNodeNameWidget::SetTextInWidget"));
    }
}
void UdwNodeNameWidget::setControllerStill() {
    AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
    PlayerController->overHUD = true;
}
void UdwNodeNameWidget::freeController() {
    AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
    PlayerController->overHUD = false;
}
void UdwNodeNameWidget::getNewDate() {

}
void UdwNodeNameWidget::ondwSlowDownTimeClicked()
{
    AdirtyWarGameModeBase* YourGameMode = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());
    YourGameMode->ModifyTime(-1,this);
}

void UdwNodeNameWidget::ondwSpeedUpTimeClicked()
{
    AdirtyWarGameModeBase* YourGameMode = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());
    YourGameMode->ModifyTime(1,this);
}


