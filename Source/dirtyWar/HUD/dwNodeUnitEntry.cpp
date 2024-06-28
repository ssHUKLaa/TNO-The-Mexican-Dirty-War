// Fill out your copyright notice in the Description page of Project Settings.


#include "dwNodeUnitEntry.h"

void UdwNodeUnitEntry::setUnitNameText(FString nameText,FString unitType, int32 regSize, int32 orgPerc)
{
	dwUnitEntryNameText->SetText(FText::FromString(nameText));
	dwUnitTypeName->SetText(FText::FromString(unitType));
	int32 nowAvail = round((orgPerc / 100) * regSize);
	FString temp = FString::FromInt(nowAvail) + "/" + FString::FromInt(regSize);
	dwUnitEntryRegimentText->SetText(FText::FromString(temp));
}
