// Fill out your copyright notice in the Description page of Project Settings.
#include "dwNodeClickedPieChart.h"
#include "Slate/SlateBrushAsset.h"
#include "SlateOptMacros.h"
#include "Engine/Texture2D.h"
#include "Rendering/DrawElements.h"
#include <Blueprint/WidgetLayoutLibrary.h>



int32 UdwNodeClickedPieChart::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
    Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);

    const FVector2D Pos = AllottedGeometry.GetAbsolutePosition();
    const FVector2D Size = AllottedGeometry.GetAbsoluteSize();
    const FVector2D Center = Pos + 0.5 * Size;
    const float Radius = FMath::Min(Size.X, Size.Y) * 0.5f;

    float TotalPercentage = 0.0f;
    for (const FPieChartSegment& Value : Segments)
    {
        TotalPercentage += Value.Percentage;
    }

    if (TotalPercentage <= 0.0f || TotalPercentage > 100.0f)
    {
        return LayerId;
    }

    float StartAngle = 0.0f;

    for (int32 Index = 0; Index < Segments.Num(); ++Index)
    {
        float EndAngle = StartAngle + (Segments[Index].Percentage / 100.0f) * 360.0f;
        FLinearColor Color = Segments[Index].Color;

        TArray<FSlateVertex> Vertices;
        TArray<SlateIndex> Indices;

        const int32 NumSegments = segmentSmoothness;
        const float AngleStep = (EndAngle - StartAngle) / NumSegments;

        Vertices.Add(FSlateVertex::Make<ESlateVertexRounding::Disabled>(FVector2f(Center), FVector2f::ZeroVector, FVector2f::ZeroVector, FColor(Color.ToFColor(true))));

        for (int32 SegmentIndex = 0; SegmentIndex <= NumSegments; ++SegmentIndex)
        {
            float Angle = FMath::DegreesToRadians(StartAngle + SegmentIndex * AngleStep);
            FVector2D VertexPos = Center + Segments[Index].CurrentScaleFactor * Radius * FVector2D(FMath::Cos(Angle), FMath::Sin(Angle));
            Vertices.Add(FSlateVertex::Make<ESlateVertexRounding::Disabled>(FVector2f(VertexPos), FVector2f::ZeroVector, FVector2f::ZeroVector, FColor(Color.ToFColor(true))));
        }

        for (int32 SegmentIndex = 0; SegmentIndex < NumSegments; ++SegmentIndex)
        {
            Indices.Add(0);
            Indices.Add(SegmentIndex + 1);
            Indices.Add(SegmentIndex + 2);
        }

        FSlateResourceHandle Handle;
        FSlateDrawElement::MakeCustomVerts(
            OutDrawElements,
            LayerId,
            Handle,
            Vertices,
            Indices,
            nullptr,
            0,
            0
        );

        StartAngle = EndAngle;
    }

    return LayerId + 1;
}

FReply UdwNodeClickedPieChart::NativeOnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
    Super::NativeOnMouseMove(MyGeometry, MouseEvent);
    const FVector2D MousePosition = MouseEvent.GetScreenSpacePosition();
    const int32 SegmentIndex = GetSegmentIndexAtPosition(MousePosition, MyGeometry);

    if (SegmentIndex != HoveredSegmentIndex)
    {
        if (HoveredSegmentIndex != INDEX_NONE)
        {
            Segments[HoveredSegmentIndex].CurrentScaleFactor = 1.0f;
        }

        if (SegmentIndex != INDEX_NONE)
        {
            Segments[SegmentIndex].CurrentScaleFactor = changeableScaleFactor;
        }

        HoveredSegmentIndex = SegmentIndex;
        

        Invalidate(EInvalidateWidget::LayoutAndVolatility);
    }
    
    UpdateTooltip(MousePosition, MyGeometry);

    return FReply::Handled();
}

void UdwNodeClickedPieChart::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
    if (HoveredSegmentIndex != INDEX_NONE)
    {
        Segments[HoveredSegmentIndex].CurrentScaleFactor = 1.0f;
        HoveredSegmentIndex = INDEX_NONE;

        Invalidate(EInvalidateWidget::LayoutAndVolatility);

        if (TooltipWidgetInstance)
        {
            TooltipWidgetInstance->RemoveFromParent();
            TooltipWidgetInstance = nullptr;
        }
    }

    Super::NativeOnMouseLeave(MouseEvent);
}

int32 UdwNodeClickedPieChart::GetSegmentIndexAtPosition(const FVector2D& Position, const FGeometry& MyGeometry) const
{
    const FVector2D Center = MyGeometry.GetAbsolutePosition() + 0.5 * MyGeometry.GetAbsoluteSize();
    const FVector2D LocalPosition = Position - Center;
    const float Radius = FMath::Min(MyGeometry.GetAbsoluteSize().X, MyGeometry.GetAbsoluteSize().Y) * 0.5f;

    if (LocalPosition.SizeSquared() > Radius * Radius)
    {
        return INDEX_NONE;
    }

    const float Angle = FMath::Atan2(LocalPosition.Y, LocalPosition.X) * 180.0f / PI;
    const float AdjustedAngle = (Angle < 0.0f) ? (Angle + 360.0f) : Angle;

    float StartAngle = 0.0f;

    for (int32 Index = 0; Index < Segments.Num(); ++Index)
    {
        float EndAngle = StartAngle + (Segments[Index].Percentage / 100.0f) * 360.0f;
        if (AdjustedAngle >= StartAngle && AdjustedAngle < EndAngle)
        {
            return Index;
        }
        StartAngle = EndAngle;
    }

    return INDEX_NONE;
}

void UdwNodeClickedPieChart::UpdateTooltip(const FVector2D MousePosition, const FGeometry& MyGeometry)
{
    if (HoveredSegmentIndex != INDEX_NONE)
    {
        if (!TooltipWidgetInstance && TooltipWidgetClass)
        {
            TooltipWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), TooltipWidgetClass);
        }

        if (TooltipWidgetInstance)
        {
            TooltipWidgetInstance->AddToViewport();

            // Set the text or other data in the tooltip widget
            /*
            UTextBlock* TextBlock = Cast<UTextBlock>(TooltipWidgetInstance->GetWidgetFromName(TEXT("TooltipText")));
            if (TextBlock)
            {
                TextBlock->SetText(FText::Format(NSLOCTEXT("PieChart", "SegmentTooltip", "Segment: {0}\nPercentage: {1}%"),
                    Segments[HoveredSegmentIndex].SegmentName,
                    FText::AsNumber(Segments[HoveredSegmentIndex].Percentage)));
            }
            */
            // Set the position of the tooltip widget
            
            UE_LOG(LogTemp, Log, TEXT("Mouse Position: X=%f, Y=%f"), MousePosition.X, MousePosition.Y);
            FVector2D Center = FVector2D(
                MyGeometry.GetAbsolutePosition().X + 0.5f * MyGeometry.GetAbsoluteSize().X,
                MyGeometry.GetAbsolutePosition().Y - 0.5f * MyGeometry.GetAbsoluteSize().Y
            );
            // Set the position of the tooltip widget
            TooltipWidgetInstance->SetPositionInViewport(MousePosition);
        }
    }
    else
    {
        if (TooltipWidgetInstance)
        {
            TooltipWidgetInstance->RemoveFromParent();
            TooltipWidgetInstance = nullptr;
        }
    }
}
