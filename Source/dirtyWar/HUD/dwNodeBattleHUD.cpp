// Fill out your copyright notice in the Description page of Project Settings.


#include "dwNodeBattleHUD.h"

void UdwNodeBattleHUD::NativeConstruct()
{
    Super::NativeConstruct();
    nodeBattleClose->OnClicked.AddUniqueDynamic(this, &UdwNodeBattleHUD::closeWidget);

}
void UdwNodeBattleHUD::closeWidget()
{
    this->RemoveFromParent();
}