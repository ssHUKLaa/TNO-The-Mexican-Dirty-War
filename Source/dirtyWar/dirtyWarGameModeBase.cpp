// Copyright Epic Games, Inc. All Rights Reserved.


#include "dirtyWarGameModeBase.h"
#include "mouseController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "HUD/dwNodeNameWidget.h"
#include "HUD/dwNodeUnitEntry.h"
#include "nodeStruct.h"
#include "util/PriorityQueue.cpp"



int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
AdirtyWarGameModeBase::AdirtyWarGameModeBase()
{
    PlayerControllerClass = AmouseController::StaticClass();
    DefaultPawnClass = AmousePawn::StaticClass();
    //PrimaryActorTick.bCanEverTick = true;
    //PrimaryActorTick.bStartWithTickEnabled = true;

    GAME_TIMETIMER.Invalidate();

    ButtonBrushes.Add(setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/close0.close0")).Object));
    ButtonBrushes.Add(setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/close1.close1")).Object));

    frameBrushes.Add(setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/unitentrything.unitentrything")).Object));
    frameBrushes.Add(setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/unitframesel.unitframesel")).Object));
    
    unitBrushes.Add(setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/UnitIcons/mex_dw_soldat_1.mex_dw_soldat_1")).Object));
    unitBrushes.Add(setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/UnitIcons/mex_dw_police_1.mex_dw_police_1")).Object));
    unitBrushes.Add(setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/UnitIcons/mex_dw_dfs_1.mex_dw_dfs_1")).Object));
    unitBrushes.Add(setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/UnitIcons/mex_dw_jet_1.mex_dw_jet_1")).Object));

    factionBrushes.Add("Government", setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/factionIcons/governmentbig.governmentbig")).Object));
    factionBrushes.Add("GPG", setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/factionIcons/gpgbig.gpgbig")).Object));
    factionBrushes.Add("FLN", setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/factionIcons/flnbig.flnbig")).Object));
    factionBrushes.Add("Los Tecos", setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/factionIcons/los_tecosbig.los_tecosbig")).Object));
    factionBrushes.Add("PDLP", setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/factionIcons/pdlpbig.pdlpbig")).Object));
    factionBrushes.Add("TBD", setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/factionIcons/tbdbig.tbdbig")).Object));
    factionBrushes.Add("TBDSYN_2", setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/factionIcons/tbdsyn2big.tbdsyn2big")).Object));
    factionBrushes.Add("TBDSYN", setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/factionIcons/tbdsynbig.tbdsynbig")).Object));
    factionBrushes.Add("UNS", setBrushesFromLoad(ConstructorHelpers::FObjectFinder<UTexture2D>(TEXT("/Game/dwHUD/factionIcons/unsbig.unsbig")).Object));

}
FSlateBrush AdirtyWarGameModeBase::setBrushesFromLoad(UTexture2D* texture)
{
    if (texture)
    {
        FSlateBrush Brush1;
        Brush1.SetResourceObject(texture);
        Brush1.ImageSize = FVector2D(texture->GetSizeX(), texture->GetSizeY());
        return Brush1;
    }
    return FSlateBrush();
}
void AdirtyWarGameModeBase::BeginPlay()
{
	Super::BeginPlay();
    //SETUP FACTIONS
    // Create Government faction

    UFactionType* None = NewObject<UFactionType>();
    None->Name = "None";
    None->Description = "WIP";
    None->Association = 3;
    None->totalUnits = 0;
    None->nodeImage = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/nodeImages/marker_green/marker_green_flipbook.marker_green_flipbook")); //redundant
    None->factionColour = FVector4d(0.698, 0.788, 0.76, 0.5);


    UFactionType* Govn = NewObject<UFactionType>();
    Govn->Name = "Government";
    Govn->Description = "WIP";
    Govn->Association = 0;
    Govn->totalUnits = 0;
    Govn->nodeImage = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/nodeImages/marker_green/marker_green_flipbook.marker_green_flipbook"));
    Govn->factionColour = FVector4d(0.099899, 0.571125, 0.53948, 0.5);


    // Create GPG faction
    UFactionType* GPG = NewObject<UFactionType>();
    GPG->Name = "GPG";
    GPG->Description = "WIP";
    GPG->Association = 1;
    GPG->totalUnits = 0;
    GPG->nodeImage = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/nodeImages/marker_red/marker_red_Flipbook.marker_red_Flipbook"));
    GPG->factionColour = FVector4d(0.82353, 0.2863, 0.2863, 0.5);

    GAME_allFactions.Add("Govn",Govn);
    GAME_allFactions.Add("GPG",GPG);
    GAME_allFactions.Add("None",None);


    //SETUP EQUIPMENT
    UEquipmentType* infantry_eq_1 = NewObject<UEquipmentType>();
    infantry_eq_1->Name = "Infantry Equipment";
    infantry_eq_1->Description = "WIP";
    infantry_eq_1->powerMult = 1;

    UEquipmentType* support_eq = NewObject<UEquipmentType>();
    support_eq->Name = "Support Equipment";
    support_eq->Description = "WIP";
    support_eq->powerMult = 1.15;

    UEquipmentType* motorized_eq_1 = NewObject<UEquipmentType>();
    motorized_eq_1->Name = "motorized_1";
    motorized_eq_1->Description = "WIP";
    motorized_eq_1->powerMult = 1.2;

    GAME_allEquipmentTypes.Add(infantry_eq_1);
    GAME_allEquipmentTypes.Add(support_eq);
    GAME_allEquipmentTypes.Add(motorized_eq_1);

    GAME_currentEquipment.Add(infantry_eq_1,100);
    GAME_currentEquipment.Add(support_eq, 100);
    GAME_currentEquipment.Add(motorized_eq_1, 100);
    
    //SETUP UNITS
    UUnitType* soldier_unit = NewObject<UUnitType>();
    soldier_unit->Name = "Soldier";
    soldier_unit->Description = "WIP";
    soldier_unit->techLevel = 1;
    soldier_unit->healthPoints = 100;
    soldier_unit->baseTravelableDistance = 10;
    soldier_unit->baseTacticsLevel = 1;
    soldier_unit->baseIntelGeneration = 0.2;
    soldier_unit->basePower = 1;
    soldier_unit->requiredEquipment = { 
        setUpRequiredEquipments(infantry_eq_1,1), 
        setUpRequiredEquipments(support_eq,1)};
    soldier_unit->unitEntryIcon = unitBrushes[0];

    UUnitType* police_unit = NewObject<UUnitType>();
    police_unit->Name = "Police";
    police_unit->Description = "WIP";
    police_unit->techLevel = 1;
    police_unit->healthPoints = 50;
    police_unit->baseTravelableDistance = 4;
    police_unit->baseTacticsLevel = 0.8;
    police_unit->baseIntelGeneration = 1;
    police_unit->basePower = 0.7;
    police_unit->requiredEquipment = { setUpRequiredEquipments(infantry_eq_1,1), setUpRequiredEquipments(support_eq,1) };
    police_unit->unitEntryIcon = unitBrushes[1];

    UUnitType* dfs_unit = NewObject<UUnitType>();
    dfs_unit->Name = "DFS";
    dfs_unit->Description = "WIP";
    dfs_unit->techLevel = 1;
    dfs_unit->healthPoints = 50;
    dfs_unit->baseTravelableDistance = 4;
    dfs_unit->baseTacticsLevel = 0.8;
    dfs_unit->baseIntelGeneration = 1;
    dfs_unit->basePower = 0.7;
    dfs_unit->requiredEquipment = { setUpRequiredEquipments(infantry_eq_1,1), setUpRequiredEquipments(support_eq,1) };
    dfs_unit->unitEntryIcon = unitBrushes[2];

    UUnitType* jet_unit = NewObject<UUnitType>();
    jet_unit->Name = "Jet";
    jet_unit->Description = "WIP";
    jet_unit->techLevel = 1;
    jet_unit->healthPoints = 5;
    jet_unit->baseTravelableDistance = 20;
    jet_unit->baseTacticsLevel = 1.5;
    jet_unit->baseIntelGeneration = 2;
    jet_unit->basePower = 5;
    jet_unit->requiredEquipment = { setUpRequiredEquipments(infantry_eq_1,1), setUpRequiredEquipments(support_eq,1) };
    jet_unit->unitEntryIcon = unitBrushes[3];

    GAME_allUnitTypes.Add(soldier_unit);
    GAME_allUnitTypes.Add(police_unit);
    GAME_allUnitTypes.Add(dfs_unit);
    GAME_allUnitTypes.Add(jet_unit);




	UDataTable* MyDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/mappedNode.mappedNode"));
	SpawnNodes(MyDataTable);
    
}
float CalculateConnectionYaw(const FVector& StartLocation, const FVector& EndLocation)
{
    FVector Direction = EndLocation - StartLocation;
    Direction.Normalize();

    float YawRotation = FMath::Atan2(Direction.Y, Direction.X) * (180.0f / PI);

    return YawRotation;
}
float AdirtyWarGameModeBase::calculateGameSpeedConversion() {
    switch (GAME_SPEED)
    {
    case 1:
        return 2.0f;
        break;
    case 2:
        return 0.5f;
        break;
    case 3:
        return 0.2f;
        break;
    case 4:
        return 0.1f;
        break;
    case 5:
        return FApp::GetDeltaTime();
        break;
    default:
        return 0.f;
        break;
    }
}
void AdirtyWarGameModeBase::ModifyTime(int modif, UdwNodeNameWidget* PlayerHUD) {

    if (((GAME_SPEED != 5) && (modif > 0)) || ((GAME_SPEED != 1) && (modif < 0))) {
        GAME_SPEED += modif;
        UE_LOG(LogTemp, Error, TEXT("%i"), GAME_SPEED);
        this->GameSpeedTimerManager(PlayerHUD);
    }
}
void AdirtyWarGameModeBase::HandleSpaceBar(UdwNodeNameWidget* PlayerHUD) {
     
    GAME_UNPAUSED = !GAME_UNPAUSED;
    this->GameSpeedTimerManager(PlayerHUD);
}
void AdirtyWarGameModeBase::GameSpeedTimerManager(UdwNodeNameWidget* PlayerHUD) {
    if (GAME_UNPAUSED == true) {
        float timerTime = AdirtyWarGameModeBase::calculateGameSpeedConversion();

        GetWorldTimerManager().ClearTimer(GAME_TIMETIMER);
        UE_LOG(LogTemp, Warning, TEXT("Float value: %f"), timerTime);

        GetWorldTimerManager().SetTimer(GAME_TIMETIMER, FTimerDelegate::CreateUObject(this, &AdirtyWarGameModeBase::IterGameTime, PlayerHUD), timerTime, true);

    }
    else {
        GetWorldTimerManager().ClearTimer(GAME_TIMETIMER);
    }
}
void AdirtyWarGameModeBase::IterGameTime(UdwNodeNameWidget* PlayerHUD) {

    // Adjust February days for leap years
    if ((currentDate.year % 4 == 0 && currentDate.year % 100 != 0) || (currentDate.year % 400 == 0)) {
        daysInMonth[1] = 29; // Leap year
    }
    else {
        daysInMonth[1] = 28; // Not a leap year
    }

    if (currentDate.hour == 23) {
        currentDate.hour = 0;

        if (currentDate.day == daysInMonth[currentDate.month] && currentDate.month == 11) { // December 31st
            currentDate.year++;
            GAME_ONYEARLY();
            currentDate.month = 0; // January
            currentDate.day = 1;
        }
        else if (currentDate.day == daysInMonth[currentDate.month]) { // Last day of the month
            currentDate.month++;
            GAME_ONMONTHLY();
            currentDate.day = 1;
        }
        else {
            currentDate.day++;
            GAME_ONDAILY();

            DaysPassed++;
            if (DaysPassed == 7) {
                GAME_ONWEEKLY();
                DaysPassed = 0;
            }
        }
    }
    else {
        // Just advance the hour
        currentDate.hour++;
        GAME_ONHOURLY();
    }

    PlayerHUD->SetTextInWidget(currentDate.year, currentDate.month, currentDate.day, currentDate.hour);
}


URequiredEquipments* AdirtyWarGameModeBase::setUpRequiredEquipments(UEquipmentType* thingy, int32 amountt)
{
    URequiredEquipments* req_eqs = NewObject<URequiredEquipments>();
    req_eqs->equipment = thingy;
    req_eqs->amount = amountt;
        
    return req_eqs;
}

void AdirtyWarGameModeBase::SpawnNodes(UDataTable* nodeTable)
{
	if (!nodeTable) return;
	else {
		TArray<FnodeStruct*> Rows;
		nodeTable->GetAllRows<FnodeStruct>(TEXT(""), Rows);
		float posx = -28770.0f;
		float posy = -18140.0f;
		float scale = 9.8f;
        UMaterialInterface* ConnectionMaterial;
        ConnectionMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/nodeImages/connections/bar_frame_Mat.bar_frame_Mat"));
        UStaticMesh* DefaultPlaneMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Plane.Plane"));
        UFactionType** nonethindy = GAME_allFactions.Find("None");
        //INITIAL NODE SETUP
		for (FnodeStruct* Row : Rows) {
			AdwNode* NewNode = GetWorld()->SpawnActor<AdwNode>(AdwNode::StaticClass(), FVector(posx+((Row->POS_X)*10),posy+((Row->POS_Y)*10), 50), FRotator(0.0f, 0.0f, -90.f));

			NewNode->NODE_ID = Row->ID;
			NewNode->NODE_TYPE = Row->NODE_TYPE;
            
			NewNode->NODE_CONNECTIONS = Row->NODE_CONNECTIONS;
            NewNode->NODE_NAME = Row->LOCATION_NAME;
            NewNode->NODE_INTEL = FMath::RoundToInt(FMath::FRand()*100);
            NewNode->NODE_FACTION = *nonethindy; //all initially none
            if (NewNode->NODE_TYPE == 1)
            {
                UFactionType* ref = *GAME_allFactions.Find("Govn");
                NewNode->NODE_FACTION_CONTROL.Add(ref, 100);
            }
            else {
                UFactionType* ref = *GAME_allFactions.Find("None");
                NewNode->NODE_FACTION_CONTROL.Add(ref, 100);
            }
			NewNode->setFlipBook();

			IDNodeMap.Add(NewNode->NODE_ID, NewNode);
			DWNodes.Add(NewNode);
		}

        
        TArray<AdwNode*> finishedNodes;
        

        if (!DefaultPlaneMesh) {
            UE_LOG(LogTemp, Error, TEXT("Failed to load default plane mesh"));
        }

        UStaticMeshComponent* ConnectionMeshComponent = NewObject<UStaticMeshComponent>(GetTransientPackage(), UStaticMeshComponent::StaticClass());
        ConnectionMeshComponent->RegisterComponent();

        //NODE CONNECTIONS
        UFactionType** govnthingy = GAME_allFactions.Find("Govn");
        
        for (AdwNode* node : DWNodes) {
            
            if (node->NODE_TYPE == 1) {
                
                node->NODE_FACTION = *govnthingy;
                for (int32 connid : node->NODE_CONNECTIONS) {
                    AdwNode* connedNode;
                    AdwNode** ConnedNodePtr = IDNodeMap.Find(connid);
                    if (ConnedNodePtr) {
                        connedNode = *ConnedNodePtr;
                    }
                    else {
                        UE_LOG(LogTemp, Error, TEXT("Failed to find connected node with ID %d"), connid);
                        continue;
                    }

                    if (connedNode->NODE_TYPE == 0) {
                        int32 RandomIndex = FMath::RandRange(0, 1);
                        if (ShouldHappen(70)) {
                            connedNode->NODE_FACTION = *govnthingy;
                            UFactionType* ref = *GAME_allFactions.Find("Govn");
                            connedNode->NODE_FACTION_CONTROL.Empty();
                            connedNode->NODE_FACTION_CONTROL.Add(ref, 100);
                            connedNode->SetNewFlipbookImage();

                            URegimentType* newReg = NewObject<URegimentType>();
                            newReg->Name = "test";
                            newReg->associatedUnit = GAME_allUnitTypes[1];
                            newReg->unitAmount = FMath::RandRange(1,50);
                            newReg->associatedFaction = *govnthingy;
                            newReg->PercentOrganized = 100;
                            newReg->nodesMovable = GAME_allUnitTypes[1]->baseTravelableDistance;
                            newReg->regimentLevel = 1;
                            connedNode->addNewUnit(newReg);
                        }
                    }
                }
            }
            for (int32 connid : node->NODE_CONNECTIONS) {
                AdwNode* connedNode;
                AdwNode** ConnedNodePtr = IDNodeMap.Find(connid);
                if (ConnedNodePtr) {
                    connedNode = *ConnedNodePtr;
                }
                else {
                    UE_LOG(LogTemp, Error, TEXT("Failed to find connected node with ID %d"), connid);
                    continue;
                }

                if (!finishedNodes.Contains(connedNode)) {
                    FVector MidPoint = (node->GetActorLocation() + connedNode->GetActorLocation()) / 2;
                    MidPoint.Z = 2.f;

                    float Distance = FVector::Distance(node->GetActorLocation(), connedNode->GetActorLocation())/100;

                    AdwNodeConnection* ConnectionActor = GetWorld()->SpawnActor<AdwNodeConnection>(AdwNodeConnection::StaticClass(), MidPoint, FRotator(0.f, CalculateConnectionYaw(node->GetActorLocation(), connedNode->GetActorLocation()), 0.f));

                    if (ConnectionActor) {
                        UStaticMeshComponent* ConnectionMesh = ConnectionActor->GetStaticMeshComponent();
                        if (ConnectionMesh) {
                            node->NODE_CONNECTIONACTORS.Add(connedNode, ConnectionActor);
                            connedNode->NODE_CONNECTIONACTORS.Add(node, ConnectionActor);

                            ConnectionMesh->SetStaticMesh(DefaultPlaneMesh);
                            UMaterialInstanceDynamic* DynamicMaterialInstance = UMaterialInstanceDynamic::Create(ConnectionMaterial, ConnectionActor);
                            ConnectionActor->DynamicMaterialInstance = DynamicMaterialInstance;
                            
                            ConnectionMesh->SetMaterial(0, DynamicMaterialInstance);
                            ConnectionMesh->SetWorldScale3D(FVector(Distance, 0.3f, 1.0f));
                        }
                        else {
                            UE_LOG(LogTemp, Error, TEXT("Failed to get static mesh component for connection actor"));
                        }
                    }
                    else {
                        UE_LOG(LogTemp, Error, TEXT("Failed to spawn connection actor"));
                    }
                }
            }
            finishedNodes.Add(node);
        }

        for (AdwNode* node : DWNodes)
        {
            if (node->NODE_REGIMENTS.Num() == 0 && node->NODE_TYPE!=1 && ShouldHappen(70))
            {
                URegimentType* newReg = NewObject<URegimentType>();
                newReg->Name = "test";
                newReg->associatedUnit = GAME_allUnitTypes[0];
                newReg->unitAmount = FMath::RandRange(1, 50);
                newReg->associatedFaction = *GAME_allFactions.Find("GPG");
                newReg->PercentOrganized = 100;
                newReg->nodesMovable = GAME_allUnitTypes[0]->baseTravelableDistance;
                newReg->regimentLevel = 1;
                node->addNewUnit(newReg);
            }
            for (int32 connid : node->NODE_CONNECTIONS)
            {
                AdwNode* connedNode;
                AdwNode** ConnedNodePtr = IDNodeMap.Find(connid);
                if (ConnedNodePtr) {
                    connedNode = *ConnedNodePtr;

                    AdwNodeConnection** connactorptr = node->NODE_CONNECTIONACTORS.Find(connedNode);
                    if (connactorptr)
                    {
                        AdwNodeConnection* connactor = *connactorptr;

                        if (connedNode->NODE_FACTION == node->NODE_FACTION)
                        {
                            connactor->DynamicMaterialInstance->SetVectorParameterValue(FName("tileColour"), node->NODE_FACTION->factionColour);
                        }
                    }
                }
            }
        }
	}
}

void AdirtyWarGameModeBase::GenerateIntel()
{
    AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
    UE_LOG(LogTemp, Error, TEXT("init GenerateIntel, sel intel: %d"), PlayerController->selectedNode->NODE_INTEL);

    for (AdwNode* node : DWNodes)
    {
        float intelmult = 1.f;
        if (node->NODE_FACTION == *GAME_allFactions.Find("None")) { //not govn
            intelmult = 1.f;
        }
        else if (node->NODE_FACTION != *GAME_allFactions.Find("Govn"))
        {
            intelmult = 2.f;
        }
        else
        {
            intelmult = 0.f;
        }
        node->NODE_INTEL -= GAME_BASEINTELDECAY * intelmult;
        for (URegimentType* unit : node->NODE_REGIMENTS)
        {
            if (unit->associatedFaction == *GAME_allFactions.Find("Govn")) //is govn
            {
                node->NODE_INTEL += (unit->associatedUnit->baseIntelGeneration * unit->unitAmount);

                if (unit->associatedUnit->Name == "DFS")
                {
                    for (int32 connectionnodeid : node->NODE_CONNECTIONS)
                    {
                        AdwNode** connodeptr = IDNodeMap.Find(connectionnodeid);
                        AdwNode* connnode = *connodeptr;
                        connnode->NODE_INTEL += ((unit->associatedUnit->baseIntelGeneration * unit->unitAmount) / 4.f);

                    }
                }
            }

        }

        //set node images
        if ((node->NODE_FACTION == *GAME_allFactions.Find("Govn")) && (node->NODE_INTEL < 25)) {
            node->NODE_FACTION = *GAME_allFactions.Find("None");
            node->SetNewFlipbookImage();
        }
        else if ((node->NODE_FACTION == *GAME_allFactions.Find("None")) && (node->NODE_INTEL >= 50))
        {
            node->NODE_FACTION = *GAME_allFactions.Find("Govn");
            node->SetNewFlipbookImage();
        }
    }

    //refresh UI

    if (PlayerController->selectedNode)
    {
        if (PlayerController->NodeClickedHUD)
        {
            PlayerController->NodeClickedHUD->SetNodeIntelProg(PlayerController->selectedNode->NODE_INTEL);
        }
    }

    UE_LOG(LogTemp, Error, TEXT("finish GenerateIntel, sel intel: %d"), PlayerController->selectedNode->NODE_INTEL);
}
void AdirtyWarGameModeBase::decrementFGameDate(FGameDate& date, const FGameDate& amount)
{
    // Decrement hours
    if (date.hour >= amount.hour)
    {
        date.hour -= amount.hour;
    }
    else
    {
        // Borrow a day if hour goes below 0
        if (date.day > 0)
        {
            date.day--;
            date.hour = (date.hour + 24) - amount.hour; // Handle hour underflow
        }
        else if (date.month > 0)
        {
            date.month--;
            date.day = 29; // Assume 30 days in the previous month for simplicity
            date.hour = (date.hour + 24) - amount.hour;
        }
        else if (date.year > 0)
        {
            date.year--;
            date.month = 11; // Assume December (previous month)
            date.day = 29;   // Assume 30 days in the previous month
            date.hour = (date.hour + 24) - amount.hour;
        }
        else
        {
            date.hour = 0; // Clamp to 0 if no more days left to borrow from
        }
    }

    // Decrement days
    if (date.day >= amount.day)
    {
        date.day -= amount.day;
    }
    else
    {
        // Borrow a month if day goes below 0
        if (date.month > 0)
        {
            date.month--;
            date.day = (date.day + 30) - amount.day; // Assume 30 days in the previous month
        }
        else if (date.year > 0)
        {
            date.year--;
            date.month = 11; // Assume December
            date.day = (date.day + 30) - amount.day;
        }
        else
        {
            date.day = 0; // Clamp to 0 if no more months left to borrow from
        }
    }

    // Decrement months
    if (date.month >= amount.month)
    {
        date.month -= amount.month;
    }
    else
    {
        // Borrow a year if month goes below 0
        if (date.year > 0)
        {
            date.year--;
            date.month = (date.month + 12) - amount.month; // Handle month underflow
        }
        else
        {
            date.month = 0; // Clamp to 0 if no more years left to borrow from
        }
    }

    // Decrement years
    if (date.year >= amount.year)
    {
        date.year -= amount.year;
    }
    else
    {
        date.year = 0; // Clamp to 0, as year cannot be negative
    }

    // Log the updated date
    UE_LOG(LogTemp, Log, TEXT("Updated Date: Year=%d, Month=%d, Day=%d, Hour=%d"), date.year, date.month, date.day, date.hour);

}
void AdirtyWarGameModeBase::moveUnits()
{
    for (auto It = GAME_movingUnits.CreateIterator(); It; ++It)
    {
        FRegimentMovementData& unitline = *It;

        FNodeDistancePair& nextOne = unitline.NodeDistances[0];

        if (nextOne.Distance.hour == 0 && nextOne.Distance.day == 0 && nextOne.Distance.month == 0 && nextOne.Distance.year == 0)
        {
            
            AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
            if (unitline.NodeDistances.Num() > 1 && unitline.RegimentType->nodesMovable>0) {
                UE_LOG(LogTemp, Warning, TEXT("unit moving now from %s"), *nextOne.Node->NODE_NAME);
                nextOne.Node->NODE_REGIMENTS.Remove(unitline.RegimentType);
                unitline.NodeDistances.RemoveAt(0);
                nextOne.Node->NODE_REGIMENTS.Add(unitline.RegimentType);

                UE_LOG(LogTemp, Warning, TEXT("to %s"), *nextOne.Node->NODE_NAME);
                unitline.RegimentType->nodesMovable -= 1;
                UE_LOG(LogTemp, Warning, TEXT("nodesmovable: %d"), unitline.RegimentType->nodesMovable);
                TArray<UFactionType*> facs;

                for (URegimentType* reg : nextOne.Node->NODE_REGIMENTS)
                {
                    if (!facs.Contains(reg->associatedFaction))
                    {
                        facs.Add(reg->associatedFaction);
                    }
                }
                if (facs.Num() > 1)
                {
                    //2 factions in node, start battle
                    GAME_nodesInBattle.Add(nextOne.Node, FnodeInBattleValues(FGameDate(0,0,4,0),0,50));
                    PlayerController->NodeClicked(nextOne.Node);
                    


                }

                if (PlayerController->NodeClickedHUD)
                {
                    TArray<UWidget*> widgetentryChildren = PlayerController->NodeClickedHUD->dwNodeUnitList->GetAllChildren();

                    for (UWidget* Child : widgetentryChildren)
                    {
                        UdwNodeUnitEntry* Entry = Cast<UdwNodeUnitEntry>(Child);
                        if (Entry)
                        {
                            Entry->UpdateUnitEntryText();
                        }
                    }
                }
            }
            else if (unitline.NodeDistances.Num() == 1)
            {
                unitline.NodeDistances.RemoveAt(0);
                It.RemoveCurrent();

                UE_LOG(LogTemp, Warning, TEXT("unit done moving"));
            }
            PlayerController->NodeClickedHUD->SetNodeUnits(PlayerController->selectedNode->NODE_REGIMENTS, PlayerController);
        }
        else if (!GAME_nodesInBattle.Contains(nextOne.Node)){ // if not in battle, start decrementing down when move
            decrementFGameDate(nextOne.Distance,FGameDate(0,0,0,1));
        }
    }

}
FGameDate AdirtyWarGameModeBase::convertDistToGameTime(float dist)
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
TArray<FNodeDistancePair> AdirtyWarGameModeBase::utilAStarSearch(AdwNode* Start, AdwNode* End)
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
            AdwNode* Neighbor = IDNodeMap.Contains(ConnectionID) ? IDNodeMap[ConnectionID] : nullptr;
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
float AdirtyWarGameModeBase::GetDistanceBetweenNodes(AdwNode* Node1, AdwNode* Node2)
{
    if (Node1 && Node2)
    {
        return FVector::Dist(Node1->GetActorLocation(), Node2->GetActorLocation());
    }
    return TNumericLimits<float>::Max();
}
void AdirtyWarGameModeBase::createUnitPath(AdwNode* ClickedNode,AmouseController* control)
{

    for (TPair<URegimentType*, AdwNode*> Pair : control->player_AllUnits)
    {
        TArray<FNodeDistancePair> listOfNodes = utilAStarSearch(Pair.Value, ClickedNode);

        //if unit is moving somewhere else, get rid of its current path and replace it with a new one
        for (auto It = GAME_movingUnits.CreateIterator(); It; ++It)
        {
            FRegimentMovementData& UnitDistInst = *It;
            if (UnitDistInst.RegimentType == Pair.Key)
            {
                It.RemoveCurrent();
                break;
            }
        }

        //turn conn green
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
                control->connectionsMovingUnit.Add(node);
            }
        }
        FRegimentMovementData unitDistList = { Pair.Key,listOfNodes };
        GAME_movingUnits.Add(unitDistList);
    }
    //deselect all units
    control->player_AllUnits.Empty();
    control->NodeClickedHUD->SetNodeUnits(control->selectedNode->NODE_REGIMENTS, control);
}
void AdirtyWarGameModeBase::startNodeBattles()
{
    for (TPair<AdwNode*, FnodeInBattleValues>& pair : GAME_nodesInBattle)
    {
        UE_LOG(LogTemp, Warning, TEXT("time %d %d"), pair.Value.timeTillNextPhase.day, pair.Value.timeTillNextPhase.hour);
        if (pair.Value.timeTillNextPhase.hour == 0 && pair.Value.timeTillNextPhase.day == 0 && pair.Value.timeTillNextPhase.month == 0 && pair.Value.timeTillNextPhase.year == 0)
        {
            TArray<URegimentType*> firstGroup{};
            TArray<URegimentType*> secondGroup{};

            TArray<URegimentType*> govnunit{};
            TArray<URegimentType*> redunit{};
            TArray<URegimentType*> brownunit{};

            for (URegimentType* unit : pair.Key->NODE_REGIMENTS)
            {
                if (unit->associatedFaction->Association == 0)
                {
                    govnunit.Add(unit);
                }
                else if (unit->associatedFaction->Association == 1)
                {
                    redunit.Add(unit);
                }
                else if (unit->associatedFaction->Association == 2)
                {
                    brownunit.Add(unit);
                }
            }
            if (govnunit.Num() > 0)
            {
                for (URegimentType* unit : govnunit)
                {
                    firstGroup.Add(unit);
                }
                for (URegimentType* unit : redunit)
                {
                    secondGroup.Add(unit);
                }
                for (URegimentType* unit : brownunit)
                {
                    secondGroup.Add(unit);
                }
            }
            else if (redunit.Num()>0 && brownunit.Num()>0)
            {
                
                for (URegimentType* unit : redunit)
                {
                    firstGroup.Add(unit);
                }
                for (URegimentType* unit : brownunit)
                {
                    secondGroup.Add(unit);
                }
            }
            else if (redunit.Num() > 0) //TODO
            {
                
            }
            else if (brownunit.Num() > 0) //TODO
            {

            }

            //Actual Damage calc
            float firstGroupDmg = 0;
            float secondGroupDmg = 0;
            
            for (URegimentType* unit : firstGroup)
            {
                firstGroupDmg += calcUnitDmg(unit);
            }
            for (URegimentType* unit : secondGroup)
            {
                secondGroupDmg += calcUnitDmg(unit);
            }


            //calc dmg for each group            
            float accdmg = firstGroupDmg / secondGroup.Num();
            for (URegimentType* unit : secondGroup)
            {
                float thisdmg = accdmg;
                while (thisdmg > 0 && unit->unitAmount > 0)
                {
                    thisdmg -= unit->associatedUnit->healthPoints;
                    unit->unitAmount -= 1;

                    if (unit->unitAmount <= 0)
                    {
                        unit->unitAmount = 0;
                        pair.Key->NODE_REGIMENTS.Remove(unit);
                        cleanUpUnitRefs(unit);


                        break;
                    }
                }
            }
            
            float accdmg2 = secondGroupDmg / firstGroup.Num();
            for (URegimentType* unit : firstGroup)
            {
                float thisdmg = accdmg2;
                while (thisdmg > 0 && unit->unitAmount > 0)
                {
                    thisdmg -= unit->associatedUnit->healthPoints;
                    unit->unitAmount -= 1;

                    if (unit->unitAmount <= 0)
                    {
                        unit->unitAmount = 0;
                        pair.Key->NODE_REGIMENTS.Remove(unit);
                        cleanUpUnitRefs(unit);

                        break;
                    }
                }
            }

            AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
            if (PlayerController->selectedNode == pair.Key && PlayerController->NodeClickedHUD)
            {
                if (PlayerController->NodeBattleHUDSelected)
                {
                    PlayerController->NodeBattleHUDSelected->RemoveFromParent();
                    PlayerController->NodeBattleHUDSelected = nullptr;
                }
                PlayerController->NodeBattleHUDSelected = PlayerController->startNodeBattleHUD(pair.Key);
                PlayerController->NodeClickedHUD->SetNodeUnits(pair.Key->NODE_REGIMENTS, PlayerController);
            }

            pair.Value.timeTillNextPhase = FGameDate(0, 0, 4, 0);
            pair.Value.phase += 1;
            pair.Value.sideOneWinning = 50; //TODO

            if (pair.Value.phase >= 3 || (PlayerController->NodeBattleHUDSelected->dwFactionEntryScroll->GetChildrenCount() < 2))
            {  
                if (pair.Value.phase >= 3)
                {
                    TArray<URegimentType*> unitsToMove = firstGroup;
                    if (pair.Value.sideOneWinning >= 50)
                    {
                        unitsToMove = secondGroup;

                    }
                    for (URegimentType* unitvalue : unitsToMove)
                    {
                        int32 RandomIndex = FMath::RandRange(0, pair.Key->NODE_CONNECTIONS.Num() - 1);
                        int32 connint = pair.Key->NODE_CONNECTIONS[RandomIndex];
                        AdwNode* connNode = *IDNodeMap.Find(connint);
                        PlayerController->player_AllUnits.Add(unitvalue, pair.Key);
                        createUnitPath(connNode, PlayerController);

                    }
                }
                AdwNode* tempValue = pair.Key;
                GAME_nodesInBattle.Remove(pair.Key);
                if (PlayerController->NodeBattleHUDSelected)
                {

                    PlayerController->NodeBattleHUDSelected->RemoveFromParent();
                    PlayerController->NodeBattleHUDSelected = nullptr;
                    
                }
                if (PlayerController->selectedNode == tempValue)
                {
                    PlayerController->NodeClickedHUD->RemoveFromParent();
                    PlayerController->NodeClickedHUD = nullptr;
                    PlayerController->NodeClicked(tempValue);
                }
                
            }
            
        }
        else
        {
            decrementFGameDate(pair.Value.timeTillNextPhase,FGameDate(0,0,1,0));
        }
    }
}
void AdirtyWarGameModeBase::cleanUpUnitRefs(URegimentType* unit)
{
    AmouseController* PlayerController = Cast<AmouseController>(GetWorld()->GetFirstPlayerController());
    for (int32 i = GAME_movingUnits.Num() - 1; i >= 0; i--)
    {
        if (GAME_movingUnits[i].RegimentType == unit)
        {
            GAME_movingUnits.RemoveAt(i);
            break;
        }
    }
    if (PlayerController->player_AllUnits.Contains(unit))
    {
        PlayerController->player_AllUnits.Remove(unit);
    }

    unit->ConditionalBeginDestroy();
    
}
float AdirtyWarGameModeBase::calcUnitDmg(URegimentType* unit)
{
    float basepower = unit->associatedUnit->basePower * unit->unitAmount;
    basepower *= unit->associatedUnit->techLevel;
    basepower *= unit->associatedUnit->baseTacticsLevel;
    basepower *= FMath::Exp(unit->associatedUnit->techLevel);
    float diceRoll = FMath::Sqrt(FMath::RandRange(1, 6));

    basepower *= diceRoll;
    return basepower;
}
bool AdirtyWarGameModeBase::ShouldHappen(int percentage)
{
    return (FMath::RandRange(1, 100 / percentage) == 1 ? true : false);
}
// always call functions, dont put much of anything here so we know the line of continual operations
void AdirtyWarGameModeBase::GAME_ONHOURLY()
{
    moveUnits();
    
}
void AdirtyWarGameModeBase::GAME_ONDAILY()
{
    startNodeBattles();
}
void AdirtyWarGameModeBase::GAME_ONWEEKLY()
{
    GenerateIntel();
}
void AdirtyWarGameModeBase::GAME_ONMONTHLY()
{
}
void AdirtyWarGameModeBase::GAME_ONYEARLY()
{
}

