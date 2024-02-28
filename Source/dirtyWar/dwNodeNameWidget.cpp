// Fill out your copyright notice in the Description page of Project Settings.


#include "dwNodeNameWidget.h"

void UdwNodeNameWidget::SetTextInWidget(const FText& NewText)
{
    if (dwDateTime)
    {
        dwDateTime->SetText(NewText);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("dwNodeName is null in UdwNodeNameWidget::SetTextInWidget"));
    }
}
