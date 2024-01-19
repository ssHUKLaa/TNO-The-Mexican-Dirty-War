// Copyright Epic Games, Inc. All Rights Reserved.


#include "dirtyWarGameModeBase.h"
#include "mouseController.h"
#include "nodeStruct.h"
#include "dwNodeConnection.h"



AdirtyWarGameModeBase::AdirtyWarGameModeBase()
{
	PlayerControllerClass = AmouseController::StaticClass();
	DefaultPawnClass = AmousePawn::StaticClass();
}

void AdirtyWarGameModeBase::BeginPlay()
{
	Super::BeginPlay();

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
void AdirtyWarGameModeBase::SpawnNodes(UDataTable* nodeTable)
{
	if (!nodeTable) return;
	else {
		TArray<FnodeStruct*> Rows;
		nodeTable->GetAllRows<FnodeStruct>(TEXT(""), Rows);
		float posx = -28770.0f;
		float posy = -18140.0f;
		float scale = 9.8f;

		for (FnodeStruct* Row : Rows) {
			
			
			AdwNode* NewNode = GetWorld()->SpawnActor<AdwNode>(AdwNode::StaticClass(), FVector(posx+((Row->POS_X)*10),posy+((Row->POS_Y)*10), 50), FRotator(0.0f, 0.0f, -90.f));

			NewNode->NODE_ID = Row->ID;
			NewNode->NODE_TYPE = Row->NODE_TYPE;
			NewNode->NODE_CONNECTIONS = Row->NODE_CONNECTIONS;
			NewNode->setFlipBook();

			IDNodeMap.Add(NewNode->NODE_ID, NewNode);
			DWNodes.Add(NewNode);
		}

        UMaterialInterface* ConnectionMaterial;
        ConnectionMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/nodeImages/connections/bar_frame_Mat.bar_frame_Mat"));
        TArray<AdwNode*> finishedNodes;
        UStaticMesh* DefaultPlaneMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Plane.Plane"));

        if (!DefaultPlaneMesh) {
            UE_LOG(LogTemp, Error, TEXT("Failed to load default plane mesh"));
        }

        UStaticMeshComponent* ConnectionMeshComponent = NewObject<UStaticMeshComponent>(GetTransientPackage(), UStaticMeshComponent::StaticClass());
        ConnectionMeshComponent->RegisterComponent();

        for (AdwNode* node : DWNodes) {
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
                            ConnectionMesh->SetStaticMesh(DefaultPlaneMesh);
                            ConnectionMesh->SetMaterial(0, ConnectionMaterial);
                            ConnectionMesh->SetWorldScale3D(FVector(Distance, 1.0f, 1.0f));

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

	}
}

