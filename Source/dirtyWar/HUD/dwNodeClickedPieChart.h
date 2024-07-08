// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "dwNodeClickedPieChart.generated.h"

USTRUCT(BlueprintType)
struct FPieChartSegment
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PieChart")
    FLinearColor Color;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PieChart")
    float Percentage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PieChart")
    FText SegmentName; 

    UPROPERTY()
    float CurrentScaleFactor;

    
    

    // Constructor
    FPieChartSegment()
        : Percentage(0.0f)
        , CurrentScaleFactor(1.0f)
    {
    }
};
/**
 * 
 */
UCLASS()
class DIRTYWAR_API UdwNodeClickedPieChart : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PieChart")
    TArray<FPieChartSegment> Segments;

    virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PieChart")
    float changeableScaleFactor = 1.1f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PieChart")
    int32 segmentSmoothness = 64;

protected:
    virtual FReply NativeOnMouseMove(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
    virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent) override;

private:
    int32 HoveredSegmentIndex = INDEX_NONE;

    int32 GetSegmentIndexAtPosition(const FVector2D& Position, const FGeometry& MyGeometry) const;

    UPROPERTY(EditAnywhere, Category = "PieChart")
    TSubclassOf<UUserWidget> TooltipWidgetClass;

    UPROPERTY()
    UUserWidget* TooltipWidgetInstance;

    void UpdateTooltip(const FVector2D MousePosition, const FGeometry& MyGeometry);
};
