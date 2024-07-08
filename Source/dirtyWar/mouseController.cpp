// Fill out your copyright notice in the Description page of Project Settings.


#include "mouseController.h"
#include "mousePawn.h"
#include "dirtyWarGameModeBase.h"
#include "HUD/dwNodeNameWidget.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include <PaperSpriteComponent.h>
#include "reticleActor.h"


AmouseController::AmouseController()
{
    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;

    
    // Ensure the mouse controller is valid
    if (this) {
        static ConstructorHelpers::FObjectFinder<UClass> HUDClassFinder(TEXT("/Game/dwHUD/dwHUD.dwHUD_C")); //i have no idea why this works but cool trick to avoid BPs
        static ConstructorHelpers::FObjectFinder<UClass> HUDClassFinder2(TEXT("/Game/dwHUD/dwWhenNodeClickedHUD.dwWhenNodeClickedHUD_C"));

        static ConstructorHelpers::FObjectFinder<UClass> HUDClassFinder3(TEXT("/Game/dwHUD/dwGovnDispHUD.dwGovnDispHUD_C"));
        static ConstructorHelpers::FObjectFinder<UClass> HUDClassFinder4(TEXT("/Game/dwHUD/dwManageWeaponsHUD.dwManageWeaponsHUD_C"));
        static ConstructorHelpers::FObjectFinder<UClass> HUDClassFinder5(TEXT("/Game/dwHUD/dwRecruitUnitHUD.dwRecruitUnitHUD_C"));

        static ConstructorHelpers::FObjectFinder<UClass> HUDClassFinder6(TEXT("/Game/dwHUD/dwNodeUnitEntryHUD.dwNodeUnitEntryHUD_C"));
        if (HUDClassFinder.Succeeded()) {
            playerHUDClass = HUDClassFinder.Object;
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("Failed to find HUD class."));
        }

        if (HUDClassFinder2.Succeeded()) {
            NodeClickedHUDClass = HUDClassFinder2.Object;
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("Failed to find HUD class."));
        }

        if (HUDClassFinder3.Succeeded()) {
            GovnInfoHUDClass = HUDClassFinder3.Object;
        }
        if (HUDClassFinder4.Succeeded()) {
            WpnsInfoHUDClass = HUDClassFinder4.Object;
        }
        if (HUDClassFinder5.Succeeded()) {
            RecruitUnitHUDClass = HUDClassFinder5.Object;
        }
        if (HUDClassFinder6.Succeeded()) {
            UnitEntryHUDClass = HUDClassFinder6.Object;
        }
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("Mouse controller is null."));
    }

    
	
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


                //assign the widget class to the hud
                if (playerHUDClass) {
                    PlayerHUD = CreateWidget<UdwNodeNameWidget>(this, playerHUDClass);
                    if (PlayerHUD) {
                        PlayerHUD->AddToPlayerScreen();

                    }
                    else {
                        UE_LOG(LogTemp, Warning, TEXT("Failed to create PlayerHUD widget."));
                    }
                }
                else {
                    UE_LOG(LogTemp, Warning, TEXT("Failed to load HUD class."));
                }
                
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
    InputComponent->BindAction("SpaceBar", IE_Pressed, this, &AmouseController::BindSpaceBarAction);

    InputComponent->BindAction("Click", IE_Pressed, this, &AmouseController::HandleClick);
    
}
void AmouseController::BindSpaceBarAction() {
    AdirtyWarGameModeBase* YourGameMode = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());
    YourGameMode->HandleSpaceBar(PlayerHUD);
}

void AmouseController::HandleClick()
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECC_Visibility, false, HitResult);


    AdwNode* ClickedNode = Cast<AdwNode>(HitResult.GetActor());
    if (ClickedNode)
    {
        if (selectedNode!= ClickedNode) {
            selectedNode = ClickedNode;
            NodeClicked(selectedNode);
        }
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("fail"));
    }
}


void AmouseController::NodeClicked(AdwNode* NodeID)
{
    FVector loc = NodeID->GetActorLocation();
    FString name = *NodeID->NODE_NAME;
    FString controller;
    if (NodeID->NODE_FACTION != nullptr) {
        controller = NodeID->NODE_FACTION->Name;
    }
    else {
        controller = "Error";
    }

    
    
    UE_LOG(LogTemp, Warning, TEXT("Clicked on Node with Name: %s"), *NodeID->NODE_NAME);
    UE_LOG(LogTemp, Warning, TEXT("Node has %d Regiments"), NodeID->NODE_REGIMENTS.Num());

    loc.Z += 1.f;

    if (NodeClickedHUD){
        
        NodeClickedHUD->slideOutAnim();
        NodeClickedHUD = nullptr;
    }

    if (NodeClickedHUDClass) {
        NodeClickedHUD = CreateWidget<UdwOnNodeClickWidget>(this, NodeClickedHUDClass);
        if (NodeClickedHUD) {
            NodeClickedHUD->AddToPlayerScreen();
            NodeClickedHUD->SetNodeText(name);
            NodeClickedHUD->SetNodeUnits(NodeID->NODE_REGIMENTS, this);
            NodeClickedHUD->SetNodeIntelProg(NodeID->NODE_INTEL);
        }
    }
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

    FVector2D MousePosition;
    GetMousePosition(MousePosition.X, MousePosition.Y);

    FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
    const float EdgeMargin = 200.0f;
    const float MaxScrollSpeed = 1.0f;

    FVector2D ScrollDirection = FVector2D::ZeroVector;
    if (!overHUD) {
        // Calculate normalized distance from edge of the screen
        float NormDistanceFromLeftEdge = FMath::Max(0.0f, 1.0f - (MousePosition.X / EdgeMargin));
        float NormDistanceFromRightEdge = FMath::Max(0.0f, 1.0f - ((ViewportSize.X - MousePosition.X) / EdgeMargin));
        float NormDistanceFromTopEdge = FMath::Max(0.0f, 1.0f - (MousePosition.Y / EdgeMargin));
        float NormDistanceFromBottomEdge = FMath::Max(0.0f, 1.0f - ((ViewportSize.Y - MousePosition.Y) / EdgeMargin));

        // Calculate scroll speed using a power function
        float ScrollSpeedX = MaxScrollSpeed * (NormDistanceFromRightEdge - NormDistanceFromLeftEdge);
        float ScrollSpeedY = MaxScrollSpeed * (NormDistanceFromBottomEdge - NormDistanceFromTopEdge);

        // Apply scroll speed to scrolling direction
        ScrollDirection.X = ScrollSpeedX;
        ScrollDirection.Y = ScrollSpeedY;

        if (ControlledPawn)
        {
            ControlledPawn->AdjustPawnMovement(ScrollDirection);
        }
    }

        
}


