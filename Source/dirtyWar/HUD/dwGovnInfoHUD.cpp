// Fill out your copyright notice in the Description page of Project Settings.


#include "dwGovnInfoHUD.h"
#include <dirtyWar/mouseController.h>

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
