// Fill out your copyright notice in the Description page of Project Settings.


#include "../mouseController.h"
#include "Components/Button.h"
#include "../dirtyWarGameModeBase.h"
#include "dwNodeNameWidget.h"


FReply UdwNodeNameWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseMove(InGeometry, InMouseEvent);

    AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
    if (dwBottomLeftBorder)
    {
        if (dwBottomLeftBorder->IsHovered())
        {
            PlayerController->overHUD = true;
        }
    }

    return Reply;
}

void UdwNodeNameWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);

    AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
    PlayerController->overHUD = false;
}


void UdwNodeNameWidget::NativeConstruct()
{

    Super::NativeConstruct();

    dwSpeedUpTime->OnClicked.AddUniqueDynamic(this, &UdwNodeNameWidget::ondwSpeedUpTimeClicked);
    dwSlowDownTime->OnClicked.AddUniqueDynamic(this, &UdwNodeNameWidget::ondwSlowDownTimeClicked);

    dwSpeedUpTime->OnHovered.AddUniqueDynamic(this, &UdwNodeNameWidget::setControllerStill);
    dwSlowDownTime->OnHovered.AddUniqueDynamic(this, &UdwNodeNameWidget::setControllerStill);
    dwSpeedUpTime->OnUnhovered.AddUniqueDynamic(this, &UdwNodeNameWidget::freeController);
    dwSlowDownTime->OnUnhovered.AddUniqueDynamic(this, &UdwNodeNameWidget::freeController);

    dwTopLeftGovnBtn->OnClicked.AddUniqueDynamic(this, &UdwNodeNameWidget::openGovnHUDTab);
    dwTopLeftMnufBtn->OnClicked.AddUniqueDynamic(this, &UdwNodeNameWidget::openWeaponsHUDTab);
    dwTopleftRecruitBtn->OnClicked.AddUniqueDynamic(this, &UdwNodeNameWidget::openUnitsHUDTab);
    

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

void UdwNodeNameWidget::openGovnHUDTab()
{

    AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
    if (GovnInfoHUD == nullptr) {
        this->openClearAllTopTabs(PlayerController);
        GovnInfoHUD = CreateWidget<UdwGovnInfoHUD>(PlayerController, PlayerController->GovnInfoHUDClass);
        if (GovnInfoHUD) {
            GovnInfoHUD->AddToPlayerScreen();
        }
    }
    else if(GovnInfoHUD != nullptr) {
        GovnInfoHUD->RemoveFromParent();
        GovnInfoHUD = nullptr;
    }
    
}

void UdwNodeNameWidget::openWeaponsHUDTab()
{

    AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
    if (WpnsInfoHUD == nullptr) {
        this->openClearAllTopTabs(PlayerController);
        WpnsInfoHUD = CreateWidget<UdwWpnsMnuHUD>(PlayerController, PlayerController->WpnsInfoHUDClass);
        if (WpnsInfoHUD) {
            WpnsInfoHUD->AddToPlayerScreen();
        }
    }
    else if (WpnsInfoHUD != nullptr) {
        WpnsInfoHUD->RemoveFromParent();
        WpnsInfoHUD = nullptr;
    }
}

void UdwNodeNameWidget::openUnitsHUDTab()
{

    AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
    if (RecruitUnitHUD == nullptr) {
        this->openClearAllTopTabs(PlayerController);
        RecruitUnitHUD = CreateWidget<UdwRecruitUnitsHUD>(PlayerController, PlayerController->RecruitUnitHUDClass);
        if (RecruitUnitHUD) {
            RecruitUnitHUD->AddToPlayerScreen();
        }
    }
    else if (RecruitUnitHUD != nullptr) {
        RecruitUnitHUD->RemoveFromParent();
        RecruitUnitHUD = nullptr;
    }

}

void UdwNodeNameWidget::openClearAllTopTabs(AmouseController* PlayerController)
{
    if (WpnsInfoHUD != nullptr) {
        WpnsInfoHUD->RemoveFromParent();
        WpnsInfoHUD = nullptr;
    }
    if (GovnInfoHUD != nullptr) {
        GovnInfoHUD->RemoveFromParent();
        GovnInfoHUD = nullptr;
    }
    if (RecruitUnitHUD != nullptr) {
        RecruitUnitHUD->RemoveFromParent();
        RecruitUnitHUD = nullptr;
    }
  
}


