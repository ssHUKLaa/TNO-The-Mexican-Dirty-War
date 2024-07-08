// Fill out your copyright notice in the Description page of Project Settings.
#include "dwNode.h"
#include "nodeStruct.h"

UPaperFlipbook* AdwNode::SelectRandomOption(TArray<UPaperFlipbook*> flips)
{
	if (flips.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, flips.Num() - 1);

		return flips[RandomIndex];
	}
	return nullptr;
}

// Sets default values
AdwNode::AdwNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("FlipbookComponent"));

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	FlipbookComponent->SetupAttachment(RootComponent);

}
void AdwNode::setFlipBook()
{
	//UE_LOG(LogTemp, Warning, TEXT("NODE_TYPE: %d"), this->NODE_ID);
	
	if (NODE_TYPE == 1) {
		YourLoadedFlipbook = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/nodeImages/city/city_flipbook.city_flipbook"));
		FlipbookComponent->SetFlipbook(YourLoadedFlipbook);
	}
	else {
		TArray<UPaperFlipbook*> flips;
		flips.Add(LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/nodeImages/marker_glitchy_1/marker_glitchy_flipbook.marker_glitchy_flipbook")));
		flips.Add(LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/nodeImages/marker_glitchy_2/marker_glitchy_2_flipbook.marker_glitchy_2_flipbook")));
		flips.Add(LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/nodeImages/marker_glitchy_3/marker_glitchy_3_flipbook.marker_glitchy_3_flipbook")));
		flips.Add(LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/nodeImages/marker_glitchy_4/marker_glitchy_4_flipbook.marker_glitchy_4_flipbook")));
		FlipbookComponent->SetFlipbook(SelectRandomOption(flips));
	}
	float NewScale = 10.f;


	// Set the new scale
	FlipbookComponent->SetRelativeScale3D(FVector(NewScale, NewScale, NewScale));
}
void AdwNode::addNewUnit(URegimentType* regType)
{
	NODE_REGIMENTS.Add(regType);
}
void AdwNode::SetNewFlipbookImage()
{
	if (NODE_FACTION) {
		if (NODE_FACTION->Name == "None") {
			TArray<UPaperFlipbook*> flips;
			flips.Add(LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/nodeImages/marker_glitchy_1/marker_glitchy_flipbook.marker_glitchy_flipbook")));
			flips.Add(LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/nodeImages/marker_glitchy_2/marker_glitchy_2_flipbook.marker_glitchy_2_flipbook")));
			flips.Add(LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/nodeImages/marker_glitchy_3/marker_glitchy_3_flipbook.marker_glitchy_3_flipbook")));
			flips.Add(LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/nodeImages/marker_glitchy_4/marker_glitchy_4_flipbook.marker_glitchy_4_flipbook")));
			FlipbookComponent->SetFlipbook(SelectRandomOption(flips));
		}
		else {
			FlipbookComponent->SetFlipbook(NODE_FACTION->nodeImage);
		}
		
		float NewScale = 10.f;

		FlipbookComponent->SetRelativeScale3D(FVector(NewScale, NewScale, NewScale));
	}
}
// Called when the game starts or when spawned
void AdwNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AdwNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AdwNode::SetRootComponent(USceneComponent* NewRootComponent)
{
}

