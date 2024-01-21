// Fill out your copyright notice in the Description page of Project Settings.

#include "PaperSprite.h"
#include "TimerManager.h"
#include "PaperSpriteComponent.h"
#include "reticleActor.h"

// Sets default values
AreticleActor::AreticleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	
	UPaperSprite* loadedSprite = LoadObject<UPaperSprite>(nullptr, TEXT("/Game/nodeImages/reticle_Sprite.reticle_Sprite"));
	SpriteComponent->SetSprite(loadedSprite);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	SpriteComponent->SetupAttachment(RootComponent);

	ScaleTimerHandle.Invalidate();

	

}
void AreticleActor::StartScaleAnimation()
{

	GetWorldTimerManager().SetTimer(ScaleTimerHandle, this, &AreticleActor::ScaleDown, 0.01f, true, 0.0f);
}
void AreticleActor::ScaleDown()
{
	// Reduce scale gradually over time
	FVector NewScale = GetActorScale3D() * 0.95f; // You can adjust the scaling factor as needed
	SetActorScale3D(NewScale);

	if (NewScale.X < 10.f)
	{
		GetWorldTimerManager().ClearTimer(ScaleTimerHandle);
		GetWorldTimerManager().SetTimer(ScaleTimerHandle, this, &AreticleActor::StartScaleAnimation, 2.0f, false);
	}
}


// Called when the game starts or when spawned
void AreticleActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AreticleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

