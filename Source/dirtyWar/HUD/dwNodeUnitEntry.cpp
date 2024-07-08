// Fill out your copyright notice in the Description page of Project Settings.
#include "dwNodeUnitEntry.h"
#include <dirtyWar/dirtyWarGameModeBase.h>
#include "../mouseController.h"



void UdwNodeUnitEntry::NativeConstruct()
{
	Super::NativeConstruct();
	dwUnitEntryBtnSel->OnHovered.AddUniqueDynamic(this, &UdwNodeUnitEntry::onUnitEntryHovered);
	dwUnitEntryBtnSel->OnUnhovered.AddUniqueDynamic(this, &UdwNodeUnitEntry::onUnitEntryUnHovered);
	dwUnitEntryBtnSel->OnClicked.AddUniqueDynamic(this, &UdwNodeUnitEntry::onUnitEntrySelected);
}

void UdwNodeUnitEntry::setUnitNameText(FString nameText,FString unitType, int32 regSize, int32 orgPerc)
{
	dwUnitEntryNameText->SetText(FText::FromString(nameText));
	dwUnitTypeName->SetText(FText::FromString(unitType));
	int32 nowAvail = round((orgPerc / 100) * regSize);
	FString temp = FString::FromInt(nowAvail) + "/" + FString::FromInt(regSize);
	dwUnitEntryRegimentText->SetText(FText::FromString(temp));
}

void UdwNodeUnitEntry::setTravelableProgBar()
{
	TravelableNodeDistBar->SetPercent((associatedRegiment->nodesMovable) / (associatedRegiment->associatedUnit->baseTravelableDistance));
}

void UdwNodeUnitEntry::onUnitEntrySelected()
{
	
	entrySelected = !entrySelected;
	int intbool = entrySelected ? 1 : 0;

	AdirtyWarGameModeBase* YourGameMode = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());
	TArray<FSlateBrush> imgBrush = YourGameMode->frameBrushes;

	dwUnitSelOutline->SetBrush(imgBrush[intbool]);

	AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
	if (entrySelected) {
		PlayerController->player_AllUnits.Add(associatedRegiment, PlayerController->selectedNode);
	}
	else {
		PlayerController->player_AllUnits.Remove(associatedRegiment);
	}
	UE_LOG(LogTemp, Warning, TEXT("%d units selected"), PlayerController->player_AllUnits.Num());
}
void UdwNodeUnitEntry::onUnitEntryHovered()
{
	AdirtyWarGameModeBase* YourGameMode = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());
	TArray<FSlateBrush> imgBrush = YourGameMode->frameBrushes;

	dwUnitSelOutline->SetBrush(imgBrush[1]);
}
void UdwNodeUnitEntry::onUnitEntryUnHovered()
{
	if (!entrySelected) {
		AdirtyWarGameModeBase* YourGameMode = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());
		TArray<FSlateBrush> imgBrush = YourGameMode->frameBrushes;

		dwUnitSelOutline->SetBrush(imgBrush[0]);
	}	
	
}

//when reclicking on a node, we need to persist each unit entry with its game state.
void UdwNodeUnitEntry::persistsEntryStatus()
{
	AdirtyWarGameModeBase* YourGameMode = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());
	TArray<FSlateBrush> imgBrush = YourGameMode->frameBrushes;

	
	AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
	if (PlayerController->player_AllUnits.Contains(associatedRegiment)) {
		dwUnitSelOutline->SetBrush(imgBrush[1]);
		entrySelected = true;
	}
	else {
		dwUnitSelOutline->SetBrush(imgBrush[0]);
		entrySelected = false;
	}
}
