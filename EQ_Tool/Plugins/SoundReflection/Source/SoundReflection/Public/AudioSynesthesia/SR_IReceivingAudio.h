// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SR_IReceivingAudio.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, BlueprintType)
class USR_IReceivingAudio : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SOUNDREFLECTION_API ISR_IReceivingAudio
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	void LoudnessUpdated (float inValue);

	UFUNCTION(BlueprintNativeEvent)
	void SpectraUpdated (const TArray<float> &inValue);
	UFUNCTION(BlueprintNativeEvent)
	void SpectraRecipientUpdated (const float inValue);

	//Only for Spectra analyzer //maybe separate interface with one parent?
	UFUNCTION(BlueprintNativeEvent)
	void UpdateColumnSpectra(int32 inColumn);
};
