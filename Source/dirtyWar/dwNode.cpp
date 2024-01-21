// Fill out your copyright notice in the Description page of Project Settings.


#include "dwNode.h"

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
	UE_LOG(LogTemp, Warning, TEXT("NODE_TYPE: %d"), this->NODE_ID);
	if (NODE_TYPE == 1) {
		//taken straight from ue
		YourLoadedFlipbook = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/nodeImages/city/city_flipbook.city_flipbook"));
	}
	else {
		YourLoadedFlipbook = LoadObject<UPaperFlipbook>(nullptr, TEXT("/Game/nodeImages/marker_glitchy_1/marker_glitchy_flipbook.marker_glitchy_flipbook"));
	}

	FlipbookComponent->SetFlipbook(YourLoadedFlipbook);
	float NewScale = 10.f;


	// Set the new scale
	FlipbookComponent->SetRelativeScale3D(FVector(NewScale, NewScale, NewScale));
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

