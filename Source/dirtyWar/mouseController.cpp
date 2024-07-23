// Fill out your copyright notice in the Description page of Project Settings.


#include "mouseController.h"
#include "mousePawn.h"
#include "HUD/dwNodeNameWidget.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include <PaperSpriteComponent.h>
#include "reticleActor.h"
#include "HUD/dwNodeBattleHUD.h"
#include "util/PriorityQueue.cpp"


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
        static ConstructorHelpers::FObjectFinder<UClass> HUDClassFinder7(TEXT("/Game/dwHUD/dwNodeBattle.dwNodeBattle_C"));
        static ConstructorHelpers::FObjectFinder<UClass> HUDClassFinder8(TEXT("/Game/dwHUD/dwNodeBattleFacEntryHUD.dwNodeBattleFacEntryHUD_C"));
        static ConstructorHelpers::FObjectFinder<UClass> HUDClassFinder9(TEXT("/Game/dwHUD/dwBattleFacUnitHUD.dwBattleFacUnitHUD_C"));
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
        if (HUDClassFinder7.Succeeded()) {
            NodeBattleHUDClass = HUDClassFinder7.Object;
        }
        if (HUDClassFinder8.Succeeded()) {
            NodeBattleHUDFactionClass = HUDClassFinder8.Object;
        }
        if (HUDClassFinder9.Succeeded()) {
            BattleUnitEntryHUDClass = HUDClassFinder9.Object;
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
    InputComponent->BindAction("RightClick", IE_Pressed, this, &AmouseController::HandleRightClick);
    
}
void AmouseController::BindSpaceBarAction() {
    AdirtyWarGameModeBase* YourGameMode = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());
    YourGameMode->HandleSpaceBar(PlayerHUD);
}
void AmouseController::HandleRightClick()
{
    //moving units
    if (player_AllUnits.Num()>0){
        FHitResult HitResult;
        GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
        AdwNode* ClickedNode = Cast<AdwNode>(HitResult.GetActor());

        if (ClickedNode)
        {
            if (selectedNode != ClickedNode) {
                AdirtyWarGameModeBase* YourGameMode = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());
                for (TPair<URegimentType*, AdwNode*> Pair : player_AllUnits)
                {
                    TArray<FNodeDistancePair> listOfNodes = utilAStarSearch(Pair.Value, ClickedNode, YourGameMode);
                    
                    //if unit is moving somewhere else, get rid of its current path and replace it with a new one
                    for (auto It = YourGameMode->GAME_movingUnits.CreateIterator(); It; ++It) 
                    {
                        FRegimentMovementData& UnitDistInst = *It;
                        if (UnitDistInst.RegimentType == Pair.Key)
                        {
                            It.RemoveCurrent();
                            break; 
                        }
                    }
                    for (int32 i = 0; i < listOfNodes.Num() - 1; ++i)
                    {
                        FNodeDistancePair& nodepair = listOfNodes[i];
                        AdwNode* node = nodepair.Node;
                        AdwNode* nextNode;

                        FNodeDistancePair& nextNodepair = listOfNodes[i + 1];
                        nextNode = nextNodepair.Node;
                        AdwNodeConnection** connactorptr = node->NODE_CONNECTIONACTORS.Find(nextNode);
                        if (connactorptr)
                        {
                            AdwNodeConnection* connactor = *connactorptr;
                            connactor->DynamicMaterialInstance->SetVectorParameterValue(FName("tileColour"), FVector4d(0.086, 0.729, 0.129, 0.8));
                            connectionsMovingUnit.Add(node);
                        }
                    }
                    FRegimentMovementData unitDistList = { Pair.Key,listOfNodes };
                    YourGameMode->GAME_movingUnits.Add(unitDistList);
                }

                //draw 

                player_AllUnits.Empty();
                NodeClickedHUD->SetNodeUnits(selectedNode->NODE_REGIMENTS, this);
            }
        }
        else {
            UE_LOG(LogTemp, Warning, TEXT("fail"));
        }
    }
}

TArray<FNodeDistancePair> AmouseController::utilAStarSearch(AdwNode* Start, AdwNode* End, AdirtyWarGameModeBase* YourGameMode)
{
    

    TArray<FNodeDistancePair> Path;
    if (!Start || !End)
    {
        UE_LOG(LogTemp, Warning, TEXT("Start or End node is null"));
        return Path;
    }

    TPriorityQueue<AdwNode*> OpenList;
    TMap<AdwNode*, AdwNode*> CameFrom;
    TMap<AdwNode*, float> CostSoFar;

    OpenList.Push(Start, 0);
    CameFrom.Add(Start, nullptr);
    CostSoFar.Add(Start, 0);

    while (!OpenList.IsEmpty())
    {
        AdwNode* Current = OpenList.Pop();

        if (Current == End)
        {
            // Reconstruct path
            AdwNode* Node = Current;
            AdwNode* PreviousNode = nullptr;
            while (Node)
            {
                float DistanceToNextNode = PreviousNode ? GetDistanceBetweenNodes(Node, PreviousNode) : 0.0f;
                Path.Insert(FNodeDistancePair(Node, convertDistToGameTime(DistanceToNextNode)), 0); // Insert at the beginning of the array
                PreviousNode = Node;
                Node = CameFrom.Contains(Node) ? CameFrom[Node] : nullptr;
            }
            return Path;
        }

        for (int32 ConnectionID : Current->NODE_CONNECTIONS)
        {
            AdwNode* Neighbor = YourGameMode->IDNodeMap.Contains(ConnectionID) ? YourGameMode->IDNodeMap[ConnectionID] : nullptr;
            if (!Neighbor)
            {
                continue;
            }

            float NewCost = CostSoFar[Current] + GetDistanceBetweenNodes(Current, Neighbor);

            if (!CostSoFar.Contains(Neighbor) || NewCost < CostSoFar[Neighbor])
            {
                CostSoFar.Add(Neighbor, NewCost);
                float Priority = NewCost + GetDistanceBetweenNodes(Neighbor, End);
                OpenList.Push(Neighbor, Priority);
                CameFrom.Add(Neighbor, Current);
            }
        }
    }

    // No path found
    return Path;
}
FGameDate AmouseController::convertDistToGameTime(float dist)
{
    UE_LOG(LogTemp, Warning, TEXT("dist: %f"), dist);
    int32 totalHours = dist / 9.0f; //arb number - each hour equals 9 units of distance
    int32 years, months, days, remainingHours;

    years = totalHours / (24 * 365);
    int32 remainingHoursAfterYears = totalHours % (24 * 365);
    months = remainingHoursAfterYears / (24 * 30);
    int32 remainingHoursAfterMonths = remainingHoursAfterYears % (24 * 30);

    days = remainingHoursAfterMonths / 24;

    remainingHours = remainingHoursAfterMonths % 24;


    FGameDate GameDate(years, months, days, remainingHours);
    UE_LOG(LogTemp, Warning, TEXT("unit movement Game Time: %d years -%d months-%d days %d hours"), GameDate.year, GameDate.month, GameDate.day, GameDate.hour);
    return GameDate;
}
float AmouseController::GetDistanceBetweenNodes(AdwNode* Node1, AdwNode* Node2)
{
    if (Node1 && Node2)
    {
        return FVector::Dist(Node1->GetActorLocation(), Node2->GetActorLocation());
    }
    return TNumericLimits<float>::Max();
}

void AmouseController::HandleClick()
{
    FHitResult HitResult;
    GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

    
    AdwNode* ClickedNode = Cast<AdwNode>(HitResult.GetActor());
    if (ClickedNode)
    {
        if (selectedNode!= ClickedNode) {
            
            NodeClicked(ClickedNode);
        }
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("fail"));
    }
}
void AmouseController::handleConnectionReUp()
{
    AdirtyWarGameModeBase* YourGameMode = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());
    for (AdwNode* cAc : connectionsMovingUnit)
    {
        for (int32 nodeid : cAc->NODE_CONNECTIONS)
        {
            AdwNode** connNodePtr = YourGameMode->IDNodeMap.Find(nodeid);
            if (connNodePtr)
            {
                AdwNode* connNode = *connNodePtr;
                AdwNodeConnection** connnptr = cAc->NODE_CONNECTIONACTORS.Find(connNode);
                if (connnptr)
                {
                    AdwNodeConnection* connn = *connnptr;
                    if (connNode->NODE_FACTION == cAc->NODE_FACTION)
                    {
                        connn->DynamicMaterialInstance->SetVectorParameterValue(FName("tileColour"), cAc->NODE_FACTION->factionColour);
                    }
                    else
                    {
                        connn->DynamicMaterialInstance->SetVectorParameterValue(FName("tileColour"), FVector4d(0.698, 0.788, 0.76, 0.5));
                    }
                }
            }
        }

    }
    connectionsMovingUnit.Empty();
}

void AmouseController::NodeClicked(AdwNode* NodeID)
{
    AdirtyWarGameModeBase* YourGameMode = Cast<AdirtyWarGameModeBase>(GetWorld()->GetAuthGameMode());
    if (selectedNode)
    {
        for (int32 connid : selectedNode->NODE_CONNECTIONS)
        {
            AdwNode* connedNode;
            AdwNode** ConnedNodePtr = YourGameMode->IDNodeMap.Find(connid);
            if (ConnedNodePtr) {
                connedNode = *ConnedNodePtr;
                AdwNodeConnection** connactorptr = selectedNode->NODE_CONNECTIONACTORS.Find(connedNode);
                if (connactorptr)
                {
                    AdwNodeConnection* connactor = *connactorptr;
                    connactor->setAnimSwitchParam(false);
                }

            }
        }
    }
    selectedNode = NodeID;
    handleConnectionReUp();

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
    if (NodeBattleHUDSelected)
    {
        NodeBattleHUDSelected->RemoveFromParent();
        NodeBattleHUDSelected = nullptr;
    }

    if (NodeClickedHUDClass) {
        NodeClickedHUD = CreateWidget<UdwOnNodeClickWidget>(this, NodeClickedHUDClass);
        if (NodeClickedHUD) {
            NodeClickedHUD->AddToPlayerScreen();
            NodeClickedHUD->SetNodeText(name);
            NodeClickedHUD->SetNodeUnits(NodeID->NODE_REGIMENTS, this);
            NodeClickedHUD->SetNodeIntelProg(NodeID->NODE_INTEL);
            NodeClickedHUD->SetFactionControl(NodeID->NODE_FACTION_CONTROL);
            
            if (YourGameMode->GAME_nodesInBattle.Contains(NodeID))
            {
                NodeClickedHUD->SetBattlePanelVisibility(ESlateVisibility::Visible);
                NodeBattleHUDSelected = startNodeBattleHUD(NodeID);
                NodeClickedHUD->updateAllUnitOnBattle();
                
            }
            
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

    //connection stuff
    
    for (int32 connid : NodeID->NODE_CONNECTIONS)
    {
        AdwNode* connedNode;
        AdwNode** ConnedNodePtr = YourGameMode->IDNodeMap.Find(connid);
        if (ConnedNodePtr) {
            connedNode = *ConnedNodePtr;
            AdwNodeConnection** connactorptr = NodeID->NODE_CONNECTIONACTORS.Find(connedNode);
            if (connactorptr)
            {
                AdwNodeConnection* connactor = *connactorptr;
                connactor->setAnimSwitchParam(true);
            }

        }
        
        
    }
    newReticle->SetActorScale3D(FVector(100.f, 100.f, 100.f));
    newReticle->StartScaleAnimation();

}

class UdwNodeBattleHUD* AmouseController::startNodeBattleHUD(AdwNode* node)
{
    class UdwNodeBattleHUD* NodeBattleHUD = CreateWidget<UdwNodeBattleHUD>(this, NodeBattleHUDClass);

    
    TMap<UFactionType*, class UdwBattleFactionEntry*> entryFactions;
    TMap<UFactionType*, int32> factionRegNumbers;
    TMap<UFactionType*, int32> factionUnitNumbers;
    for (URegimentType* unit : node->NODE_REGIMENTS)
    {
        //if the faction hud type hasnt appeared, create it
        if (!entryFactions.Contains(unit->associatedFaction))
        {

            class UdwBattleFactionEntry* NodeBattleFacHUD = CreateWidget<UdwBattleFactionEntry>(this, NodeBattleHUDFactionClass);
            NodeBattleFacHUD->dwBattleFactionText->SetText(FText::FromString(unit->associatedFaction->Name));
            if (node->NODE_FACTION_CONTROL.Contains(unit->associatedFaction)) {
                NodeBattleFacHUD->dwNodeBattleFacControl->SetText(FText::FromString(FString::FromInt(*node->NODE_FACTION_CONTROL.Find(unit->associatedFaction))));
            }
            else { NodeBattleFacHUD->dwNodeBattleFacControl->SetText(FText::FromString("0")); }
            
            factionRegNumbers.Add(unit->associatedFaction, 1);
            factionUnitNumbers.Add(unit->associatedFaction, unit->unitAmount);

            NodeBattleHUD->dwFactionEntryScroll->AddChild(NodeBattleFacHUD);
            entryFactions.Add(unit->associatedFaction, NodeBattleFacHUD);
        }
        else {
            int32* RegNumberPtr = factionRegNumbers.Find(unit->associatedFaction);
            *RegNumberPtr += 1;
            int32* unitNumberPtr = factionUnitNumbers.Find(unit->associatedFaction);
            *unitNumberPtr += unit->unitAmount;
        }

        class UdwNodeBattleUnitEntryHUD* BattleUnitEntryHUD = CreateWidget<UdwNodeBattleUnitEntryHUD>(this, BattleUnitEntryHUDClass);
        //relevant info
        class UdwBattleFactionEntry* factype = *entryFactions.Find(unit->associatedFaction);
        factype->dwNodeBattleFacUnitScroll->AddChild(BattleUnitEntryHUD);
    }
    for (TPair<UFactionType*, class UdwBattleFactionEntry*> pair : entryFactions)
    {
        class UdwBattleFactionEntry* factype = pair.Value;
        int32 numregss = *factionRegNumbers.Find(pair.Key);
        int32 numunits = *factionUnitNumbers.Find(pair.Key);

        factype->dwNodeBattleFacReg->SetText(FText::FromString(FString::FromInt(numregss)+" Regiments"));
        factype->dwNodeBattleFacUnits->SetText(FText::FromString(FString::FromInt(numunits) + " Units"));
    }


    NodeBattleHUD->AddToPlayerScreen();
    return NodeBattleHUD;

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
    const float EdgeMargin = 50.f;
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


