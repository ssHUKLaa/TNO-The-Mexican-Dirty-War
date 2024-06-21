// Fill out your copyright notice in the Description page of Project Settings.


#include "dwNodeUnitEntry.h"

void UdwNodeUnitEntry::setUnitNameText(FString nameText,FString unitType)
{
	dwUnitEntryNameText->SetText(FText::FromString(nameText));
	dwUnitTypeName->SetText(FText::FromString(unitType));
}
