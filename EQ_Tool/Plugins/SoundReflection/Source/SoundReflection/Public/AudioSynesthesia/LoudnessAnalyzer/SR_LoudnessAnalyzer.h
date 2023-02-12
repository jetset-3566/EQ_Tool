// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoudnessNRT.h"
#include "AudioSynesthesia/SR_AudioAnalyzerBase.h"
#include "SR_LoudnessAnalyzer.generated.h"


/**
 * Class for analyze and output loudness of sounds
 */
UCLASS()
class SOUNDREFLECTION_API ASR_LoudnessAnalyzer : public ASR_AudioAnalyzerBase
{
	GENERATED_BODY()
public:
	virtual void BindSoundComponent() override;
	virtual void AudioPlaybackUpdate(const USoundWave* PlayingSoundWave, const float PlaybackPercent) override;

	//Recipients who listener analyzer sound and react. Dont forget recipient must have interface SR_IReceivingAudio
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AudioAnalizer")
	TArray<TObjectPtr<AActor>> Recipients;
	//Sound source with result data of loudness. 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AudioAnalizer")
	TObjectPtr<ULoudnessNRT> LoudnessResult = nullptr;
};
