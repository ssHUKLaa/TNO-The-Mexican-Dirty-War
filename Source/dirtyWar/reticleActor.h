// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include <PaperSpriteComponent.h>
#include "GameFramework/Actor.h"
#include <Components/TimelineComponent.h>
#include "reticleActor.generated.h"


UCLASS()
class DIRTYWAR_API AreticleActor : public AActor
{
	GENERATED_BODY()

private:
	FTimeline ScaleTimeline;
	float InitialScaleValue;
	float TargetScaleValue;
	
public:	
	// Sets default values for this actor's properties
	AreticleActor();
	void StartScaleAnimation();
	void ScaleDown();
	void oscScale();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paper2D", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* SpriteComponent;
	float natVariance;

	UPROPERTY(EditAnywhere, Category = "Animation")
	UCurveFloat* ScaleCurve;
	FTimerHandle ScaleTimerHandle;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
