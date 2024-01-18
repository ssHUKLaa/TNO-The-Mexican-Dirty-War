// Copyright Epic Games, Inc. All Rights Reserved.


#include "dirtyWarGameModeBase.h"
#include "mouseController.h"
#include "nodeStruct.h"



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

		for (AdwNode* node : DWNodes) {
			for (int32 connid : node->NODE_CONNECTIONS) {
				AdwNode* connedNode = *IDNodeMap.Find(connid);
				if (!finishedNodes.Contains(connedNode)){
					/*
					float Distance = FVector::Distance(node->GetActorLocation(), connedNode->GetActorLocation());

					UStaticMeshComponent* ConnectionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConnectionMesh"));

					ConnectionMesh->SetStaticMesh(ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Plane.Plane")).Object);
					ConnectionMesh->SetMaterial(0, ConnectionMaterial);

					FVector MidPoint = 0.5f * (node->GetActorLocation() + connedNode->GetActorLocation());
					FRotator Rotation = FRotationMatrix::MakeFromX(node->GetActorLocation() - connedNode->GetActorLocation()).Rotator();

					FTransform Transform = FTransform(Rotation, MidPoint, FVector(Distance, 1.0f, 1.0f));
					ConnectionMesh->SetWorldTransform(Transform);
					ConnectionMesh->RegisterComponent();
					*/
					
				}
				finishedNodes.Add(node);
			}
		}

	}
}
