// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConstantQNRT.h"
#include "AudioSynesthesia/SR_AudioAnalyzerBase.h"
#include "SR_SpectraAnalyzer.generated.h"

USTRUCT(BlueprintType)
struct FSpectraRecipients
{
	GENERATED_BODY()

	//Recipients who listener analyzer sound and react. Dont forget recipient must have interface SR_IReceivingAudio
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AudioAnalizer")
	TObjectPtr<AActor> Recipient;
	/* 
	 * -1 the recipient will receive the entire spectrum as an array by SpectraUpdated() from SR_IReceivingAudio interface.
	 * any 0 - (NumBands - 1). recipient get only this channel of spectra
	 * NumBands - it variable of SpectraResult setting. Total number of resulting constant Q bands
	 */ 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, AdvancedDisplay, Category="AudioAnalizer")
	int32 IndexChannelSpectra = -1;
};

/**
 * Class for analyze and output spectra of sounds
 */
UCLASS()
class SOUNDREFLECTION_API ASR_SpectraAnalyzer : public ASR_AudioAnalyzerBase
{
	GENERATED_BODY()

public:
	virtual void BindSoundComponent() override;
	virtual void AudioPlaybackUpdate(const USoundWave* PlayingSoundWave, const float PlaybackPercent) override;
	
	
	//Recipients who listener analyzer sound and react. Dont forget recipient must have interface EQ_IReceivingAudio
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AudioAnalizer")
	TArray<FSpectraRecipients> Recipients;
	//Sound source with result data of loudness. 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AudioAnalizer")
	TObjectPtr<UConstantQNRT> SpectraResult = nullptr;
};
