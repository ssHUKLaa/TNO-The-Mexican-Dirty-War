// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <Components/Button.h>
#include <Components/ScrollBox.h>
#include <Components/ProgressBar.h>
#include "dwNodeBattleHUD.generated.h"

/**
 * 
 */
UCLASS()
class DIRTYWAR_API UdwNodeBattleHUD : public UUserWidget
{
	GENERATED_BODY()
	

public:


	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* nodeBattleClose;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* dwFactionEntryScroll;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* dwNodeBattleWinningProg;


	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void NativeConstruct();
	UFUNCTION(BlueprintCallable, Category = "My Widget Functions")
	void closeWidget();

	

};
