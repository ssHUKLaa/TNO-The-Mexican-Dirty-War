// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include <Components/CapsuleComponent.h>
#include "dwNode.generated.h"


UCLASS()
class DIRTYWAR_API AdwNode : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paper2D", meta = (AllowPrivateAccess = "true"))
	class UPaperFlipbookComponent* FlipbookComponent;
	UPaperFlipbook* SelectRandomOption(TArray<UPaperFlipbook*> flips);

public:	
	// Sets default values for this actor's properties
	AdwNode();

	void setFlipBook();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NODE_TYPE;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	UPaperFlipbook* YourLoadedFlipbook;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 NODE_ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> NODE_CONNECTIONS;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NODE_NAME;
	void SetRootComponent(USceneComponent* NewRootComponent);

};
