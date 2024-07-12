// Fill out your copyright notice in the Description page of Project Settings.


#include "dwNodeConnection.h"

void AdwNodeConnection::setAnimSwitchParam(bool which)
{
	int32 shouldSineGlowInt = which ? 1 : 0;
	DynamicMaterialInstance->SetScalarParameterValue(FName("shouldSineGlow"), shouldSineGlowInt);
}
