// Fill out your copyright notice in the Description page of Project Settings.


#include "mouseController.h"
#include "mousePawn.h"
#include "dirtyWarGameModeBase.h"
#include <PaperSpriteComponent.h>
#include "reticleActor.h"


AmouseController::AmouseController()
{
    bShowMouseCursor = true;
	
}

void AmouseController::PossessPawn(AmousePawn* PawnToPossess)
{
    if (PawnToPossess)
    {
        Possess(PawnToPossess);
    }
}

void AmouseController::BeginPlay()
{
    Super::BeginPlay();

    AdirtyWarGameModeBase* YourGameMode = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());

    if (YourGameMode)
    {
        // Get the default pawn class for this player controller from the custom game mode
        UClass* DefaultPawnClass = YourGameMode->GetDefaultPawnClassForController(this);

        if (DefaultPawnClass)
        {
            // Spawn the default pawn
            AmousePawn* DefaultPawn = Cast<AmousePawn>(GetWorld()->GetFirstPlayerController()->GetPawn());

            if (DefaultPawn)
            {
                // Possess the default pawn
                Possess(DefaultPawn);
                UE_LOG(LogTemp, Warning, TEXT("Pawn possessed by controller"));

                // Now, this player controller is in control of the default pawn
            }
        }
    }

    ControlledPawn = Cast<AmousePawn>(GetPawn());
}
void AmousePawn::PossessedBy(AController* NewController)
{
    UE_LOG(LogTemp, Warning, TEXT("Pawn possessed by controller"));
}
void AmouseController::SetupInputComponent()
{

    Super::SetupInputComponent();
    InputComponent->BindAxis("Zoom", this, &AmouseController::Zoom);
    InputComponent->BindAction("Click", IE_Pressed, this, &AmouseController::HandleClick);
}
void AmouseController::HandleClick()
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECC_Visibility, false, HitResult);


    AdwNode* ClickedNode = Cast<AdwNode>(HitResult.GetActor());
    if (ClickedNode)
    {
        selectedNode = ClickedNode;
        NodeClicked(ClickedNode);

        FVector loc = ClickedNode->GetActorLocation();
        loc.Z += 1.f;


        //reticle anim
        if (!newReticle)
        {
            newReticle = GetWorld()->SpawnActor<AreticleActor>(AreticleActor::StaticClass(), loc, FRotator(0.0f, 0.0f, -90.f));
            newReticle->SetActorScale3D(FVector(100.f, 100.f, 100.f));
        }
        else
        {
            newReticle->SetActorLocation(loc);
        }
        newReticle->SetActorScale3D(FVector(100.f, 100.f, 100.f));
        newReticle->StartScaleAnimation();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("fail"));
    }
}


void AmouseController::NodeClicked(AdwNode* NodeID)
{
    UE_LOG(LogTemp, Warning, TEXT("Clicked on Node with Name: %s"), *NodeID->NODE_NAME);
}
void AmouseController::Zoom(float Value)
{
    if (ControlledPawn)
    {
        // Pass input to the pawn for handling zoom
        ControlledPawn->Zoom(Value);
    }
}


void AmouseController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Edge scrolling logic
    FVector2D MousePosition;
    GetMousePosition(MousePosition.X, MousePosition.Y);

    FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
    const float EdgeMargin = 200.0f;

    FVector2D ScrollDirection = FVector2D::ZeroVector;

    if (MousePosition.X < EdgeMargin)
    {
        ScrollDirection.X = -1.0f; // Scroll left
    }
    else if (MousePosition.X > ViewportSize.X - EdgeMargin)
    {
        ScrollDirection.X = 1.0f; // Scroll right
    }

    if (MousePosition.Y < EdgeMargin)
    {
        ScrollDirection.Y = -1.0f; // Scroll up
    }
    else if (MousePosition.Y > ViewportSize.Y - EdgeMargin)
    {
        ScrollDirection.Y = 1.0f; // Scroll down
    }
    if (ControlledPawn)
    {
        ControlledPawn->AdjustPawnMovement(ScrollDirection);
    }
}


