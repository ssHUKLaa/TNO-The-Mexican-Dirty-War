// Fill out your copyright notice in the Description page of Project Settings.
#include "dwOnNodeClickWidget.h"
#include "Animation/WidgetAnimation.h" 
#include "../mouseController.h"




FReply UdwOnNodeClickWidget::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseMove(InGeometry, InMouseEvent);

    AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
    if (NodeClickedBorder)
    {
        if (NodeClickedBorder->IsHovered())
        {
            PlayerController->overHUD = true;
        }
    }

    return Reply;
}

void UdwOnNodeClickWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
    Super::NativeOnMouseLeave(InMouseEvent);

    AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
    PlayerController->overHUD = false;
}

void UdwOnNodeClickWidget::NativeConstruct()
{
    Super::NativeConstruct();
    nodeClickedBattlePanel->SetVisibility(ESlateVisibility::Hidden);
    dwNodeExitButton->OnClicked.AddUniqueDynamic(this, &UdwOnNodeClickWidget::slideOutAnim);
    dwOpenNodeBattleBtn->OnClicked.AddUniqueDynamic(this, &UdwOnNodeClickWidget::openBattleMenu);

    if (SlideIN)
    {
        PlayAnimationForward(SlideIN);

    }
}
void UdwOnNodeClickWidget::openBattleMenu()
{
    Cast<AmouseController>(GetWorld()->GetFirstPlayerController())->startNodeBattleHUD(Cast<AmouseController>(GetWorld()->GetFirstPlayerController())->selectedNode);
}

void UdwOnNodeClickWidget::slideOutAnim()
{
    if (SlideIN)
    {
        const float AnimationDuration = SlideIN->GetEndTime() - SlideIN->GetStartTime();
        UE_LOG(LogTemp, Warning, TEXT("test %d"), SlideIN->GetEndTime() - SlideIN->GetStartTime());

        PlayAnimationReverse(SlideIN);

        FTimerHandle TimerHandle;
        GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]() {
            RemoveFromParent();
            }, AnimationDuration, false);
    }

}

void UdwOnNodeClickWidget::SetBattlePanelVisibility(ESlateVisibility vis)
{
    nodeClickedBattlePanel->SetVisibility(vis);
}

void UdwOnNodeClickWidget::SetNodeText(FString name)
{
	dwNodeText->SetText(FText::FromString(name));

}

void UdwOnNodeClickWidget::SetNodeIntelProg(int32 intel)
{
    dwNodeIntelProgbar->SetPercent(static_cast<float>(intel) / 100.0f);
    UE_LOG(LogTemp, Warning, TEXT("percent %f"), static_cast<float>(intel) / 100.0f);
    setIntelText(intel);
}

void UdwOnNodeClickWidget::SetNodeUnits(TArray<URegimentType*> nodeUntis, AmouseController* ctrl)
{
    dwNodeUnitList->ClearChildren();
    for (URegimentType* node : nodeUntis) {
        UdwNodeUnitEntry* nodeEntry = CreateWidget<UdwNodeUnitEntry>(ctrl, ctrl->UnitEntryHUDClass);
        nodeEntry->associatedRegiment = node;
        nodeEntry->setUnitNameText(node->Name,node->associatedUnit->Name, node->unitAmount,node->PercentOrganized);
        nodeEntry->setTravelableProgBar();
        nodeEntry->persistsEntryStatus();
        nodeEntry->UpdateUnitEntryText();
        nodeEntry->setUnitImage();
        dwNodeUnitList->AddChild(nodeEntry);
        

    }
    UE_LOG(LogTemp, Warning, TEXT("length: %d"), nodeUntis.Num());

}
void UdwOnNodeClickWidget::updateAllUnitOnBattle()
{
    for (UWidget* indiv : dwNodeUnitList->GetAllChildren())
    {
        UdwNodeUnitEntry* nodeEntry = Cast<UdwNodeUnitEntry>(indiv);
        nodeEntry->dwUnitEntryNameText->SetText(FText::FromString("In Battle"));
    }
}
void UdwOnNodeClickWidget::SetFactionControl(TMap<UFactionType*, int32> input)
{
    PieChartHUD->Segments.Empty();
    FString highestControl = "No One";
    int32 controlCheck = 0;
    for (TPair<UFactionType*, int32> facControl : input)
    {
        FPieChartSegment newCont(FVector4dToFLinearColor(facControl.Key->factionColour),facControl.Value,facControl.Key,1.0);
        PieChartHUD->Segments.Add(newCont);
        if (facControl.Value >= controlCheck)
        {
            controlCheck = facControl.Value;
            highestControl = facControl.Key->Name;
        }
    }
    highestControl = (highestControl +" Has Majority Control");
    dwNodeControlText->SetText(FText::FromString(highestControl));
    PieChartHUD->RefreshPieChart();
}
void UdwOnNodeClickWidget::setIntelText(int32 intel)
{
    dwNodeControlIntel->SetText(FText::FromString("We Have " + FString::FromInt(intel) + " Intel"));
}
FLinearColor UdwOnNodeClickWidget::FVector4dToFLinearColor(const FVector4d& Vector)
{
    return FLinearColor(Vector.X, Vector.Y, Vector.Z, Vector.W);
}