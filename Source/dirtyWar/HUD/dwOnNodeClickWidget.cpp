// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/WidgetAnimation.h" 
#include "dwOnNodeClickWidget.h"



void UdwOnNodeClickWidget::NativeConstruct()
{
    Super::NativeConstruct();

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



void UdwOnNodeClickWidget::SetNodeText(FString name)
{
	dwNodeText->SetText(FText::FromString(name));
}
