// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/WidgetAnimation.h" 
#include "../mouseController.h"
#include "dwOnNodeClickWidget.h"



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

    dwNodeExitButton->OnClicked.AddUniqueDynamic(this, &UdwOnNodeClickWidget::slideOutAnim);

    if (SlideIN)
    {
        PlayAnimationForward(SlideIN);

    }
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



void UdwOnNodeClickWidget::SetNodeText(FString name, FString control)
{
	dwNodeText->SetText(FText::FromString(name));

    dwNodeControlledText->SetText(FText::FromString(control));
}

void UdwOnNodeClickWidget::SetNodeUnits(TArray<URegimentType*> nodeUntis, AmouseController* ctrl)
{
    
    for (URegimentType* node : nodeUntis) {
        UdwNodeUnitEntry* nodeEntry = CreateWidget<UdwNodeUnitEntry>(ctrl, ctrl->UnitEntryHUDClass);
        nodeEntry->associatedRegiment = node;
        nodeEntry->setUnitNameText(node->Name,node->associatedUnit->Name, node->unitAmount,node->PercentOrganized);
        nodeEntry->setTravelableProgBar();
        dwNodeUnitList->AddChild(nodeEntry);

    }
    UE_LOG(LogTemp, Warning, TEXT("length: %d"), nodeUntis.Num());

}
