// Fill out your copyright notice in the Description page of Project Settings.

#include "Slate/SlateBrushAsset.h"
#include "SlateOptMacros.h"
#include "Engine/Texture2D.h"
#include "Rendering/DrawElements.h"
#include "dwNodeClickedPieChart.h"


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

    

    return FReply::Handled();
}

void UdwNodeClickedPieChart::NativeOnMouseLeave(const FPointerEvent& MouseEvent)
{
    if (HoveredSegmentIndex != INDEX_NONE)
    {
        Segments[HoveredSegmentIndex].CurrentScaleFactor = 1.0f;
        HoveredSegmentIndex = INDEX_NONE;

        Invalidate(EInvalidateWidget::LayoutAndVolatility);
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
