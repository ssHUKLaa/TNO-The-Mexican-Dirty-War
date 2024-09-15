// Fill out your copyright notice in the Description page of Project Settings.


#include "dwRecruitUnitsHUD.h"
#include <dirtyWar/mouseController.h>
#include "dwUnitRecruitEntry.h"
#include "../nodeStruct.h"
#include "../mouseController.h"
#include <dirtyWar/dirtyWarGameModeBase.h>

void UdwRecruitUnitsHUD::NativeConstruct()
{
    Super::NativeConstruct();

    dwGovnExitBtn->OnClicked.AddUniqueDynamic(this, &UdwRecruitUnitsHUD::closeHUD);

    if (slideIn)
    {
        PlayAnimationForward(slideIn);

    }
    setEquipmentNumbers();
    setRecruitableUnits();
}

void UdwRecruitUnitsHUD::closeHUD()
{
    AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
    this->RemoveFromParent();
    PlayerController->GovnInfoHUD = nullptr;
}

void UdwRecruitUnitsHUD::setEquipmentNumbers()
{
    AdirtyWarGameModeBase* gm = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());
    int32 infnum = *gm->GAME_currentEquipment.Find(gm->GAME_allEquipmentTypes[0]);
    int32 supnum = *gm->GAME_currentEquipment.Find(gm->GAME_allEquipmentTypes[1]);
    int32 motnum = *gm->GAME_currentEquipment.Find(gm->GAME_allEquipmentTypes[2]);

    dwRecruitInfText->SetText(FText::FromString("Infantry Equipment: " + FString::FromInt(infnum)));
    dwRecruitSupText->SetText(FText::FromString("Support Equipment: " + FString::FromInt(supnum)));
    dwRecruitMotText->SetText(FText::FromString("Motorized Equipment: " + FString::FromInt(motnum)));
}
void UdwRecruitUnitsHUD::setRecruitableUnits()
{
    AdirtyWarGameModeBase* gm = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());
    AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
    for (UUnitType* unit : gm->GAME_recruitableUnitTypes)
    {
        UdwUnitRecruitEntry* newUnitEntry = CreateWidget<UdwUnitRecruitEntry>(this, PlayerController->unitRecruitEntryHUDClass);
        newUnitEntry->dwRecruitUnitName->SetText(FText::FromString(*gm->GAME_longUnitNames.Find(unit->Name)));
        for (URequiredEquipments* reqEq : unit->requiredEquipment)
        {

        }
        dwUnitRecruitScrBox->AddChild(newUnitEntry);

    }
}