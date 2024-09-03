// Fill out your copyright notice in the Description page of Project Settings.


#include "dwNodeBattleUnitEntryHUD.h"

void UdwNodeBattleUnitEntryHUD::setupUnitsAndOrganization(int32 units,int32 org)
{
	dwBattleUnitNum->SetText(FText::FromString(FString::FromInt(units) + " Units"));
	dwBattleUnitOrg->SetText(FText::FromString(FString::FromInt(org) + "% Organized"));
}
void UdwNodeBattleUnitEntryHUD::setupUnitName(FString Name)
{
	dwBattleUnitName->SetText(FText::FromString(Name));
}