// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioSynesthesia/LoudnessAnalyzer/SR_LoudnessAnalyzer.h"
#include "AudioSynesthesia/SR_IReceivingAudio.h"

void ASR_LoudnessAnalyzer::BindSoundComponent()
{
	Super::BindSoundComponent();
	
	if (!LoudnessResult)
	{
		UE_LOG(LogAudioAnalyzer, Error,
			   TEXT("AEQ_LoudnessAnalyzer::AudioPlaybackUpdate - Check LoudnessResult is not must be null"));
		return;
	}
	if (!LoudnessResult->Sound)
	{
		UE_LOG(LogAudioAnalyzer, Error,
			   TEXT("AEQ_AudioAnalyzerBase::BindSoundComponent - Check LoudnessResult_SoundSource is not must be null"
			   ));
		return;
	}

	AudioComponent->SetSound(LoudnessResult->Sound);
	DurationSoundSource = LoudnessResult->Sound->Duration;
	AudioComponent->OnAudioPlaybackPercent.AddUniqueDynamic(this, &ASR_LoudnessAnalyzer::AudioPlaybackUpdate);
	AudioComponent->Play();
}

void ASR_LoudnessAnalyzer::AudioPlaybackUpdate(const USoundWave* PlayingSoundWave, const float PlaybackPercent)
{
	Super::AudioPlaybackUpdate(PlayingSoundWave, PlaybackPercent);

	if (LoudnessResult)
	{
		float loudness = 0.0f;
		LoudnessResult->GetNormalizedLoudnessAtTime(PlaybackPercent * DurationSoundSource, loudness);
		for (auto recipient : Recipients)
		{
			if (!recipient)
			{
				UE_LOG(LogAudioAnalyzer, Warning, TEXT("AEQ_LoudnessAnalyzer::AudioPlaybackUpdate - recipient - actor of array null "));
				break;
			}
			
			if (recipient->Implements<USR_IReceivingAudio>())
				ISR_IReceivingAudio::Execute_LoudnessUpdated(recipient, loudness);
			else
				UE_LOG(LogAudioAnalyzer, Warning, TEXT("AEQ_LoudnessAnalyzer::AudioPlaybackUpdate - actor - %s - not have interface IReceivingAudio"), *GetDebugName(recipient));
		}
	}
}