// Fill out your copyright notice in the Description page of Project Settings.


#include "mousePawn.h"

// Sets default values
AmousePawn::AmousePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 500.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	// Set the initial rotation of the spring arm or camera to point down
	SpringArmComponent->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
	// Alternatively, if you want to set the camera's rotation
	// CameraComponent->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));

	SetActorLocation(FVector(100, 100, 1000));


}

// Called when the game starts or when spawned
void AmousePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AmousePawn::AdjustPawnMovement(const FVector2D& ScrollDirection)
{

	float CurrentArmLength = SpringArmComponent->TargetArmLength;

	float ScrollSpeed = (CurrentArmLength > 0) ? 60.0f * FMath::Loge(1.0f + CurrentArmLength / 100.0f) : 60.0f;
    // Adjust pawn movement based on edge scrolling
    FVector AdjustedMovement = FVector(ScrollDirection.X, ScrollDirection.Y, 0.0f) * ScrollSpeed;
    AddActorWorldOffset(AdjustedMovement, true);
}

void AmousePawn::Zoom(float ZoomAmount)
{
	float ZoomSpeed = 100.0f;
	// Adjust the spring arm length based on the zoom input
	SpringArmComponent->TargetArmLength += ZoomAmount * ZoomSpeed;

	// Ensure the spring arm length stays within a specified range if needed
	float MinZoom = 0.f;
	float MaxZoom = 1000000.f;
	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength, MinZoom, MaxZoom);
}
