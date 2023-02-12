// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioSynesthesia/SpectraAnalyzer/SR_SpectraAnalyzer.h"
#include "AudioSynesthesia/SR_IReceivingAudio.h"

void ASR_SpectraAnalyzer::BindSoundComponent()
{
	Super::BindSoundComponent();

	if (!SpectraResult)
	{
		UE_LOG(LogAudioAnalyzer, Error,
		       TEXT("AEQ_SpectraAnalyzer::AudioPlaybackUpdate - Check LoudnessResult is not must be null"));
		return;
	}
	if (!SpectraResult->Sound)
	{
		UE_LOG(LogAudioAnalyzer, Error,
		       TEXT("AEQ_SpectraAnalyzer::BindSoundComponent - Check LoudnessResult_SoundSource is not must be null"
		       ));
		return;
	}

	AudioComponent->SetSound(SpectraResult->Sound);
	DurationSoundSource = SpectraResult->Sound->Duration;
	AudioComponent->OnAudioPlaybackPercent.AddUniqueDynamic(this, &ASR_AudioAnalyzerBase::AudioPlaybackUpdate);
	AudioComponent->Play();

	for (auto spectraRecipient : Recipients)
	{
		if (spectraRecipient.Recipient)
		{
			if (spectraRecipient.Recipient->Implements<USR_IReceivingAudio>())
				ISR_IReceivingAudio::Execute_UpdateColumnSpectra(spectraRecipient.Recipient, SpectraResult->Settings->NumBands);
		}
	}
}

void ASR_SpectraAnalyzer::AudioPlaybackUpdate(const USoundWave* PlayingSoundWave, const float PlaybackPercent)
{
	Super::AudioPlaybackUpdate(PlayingSoundWave, PlaybackPercent);

	if (SpectraResult)
	{
		TArray<float> spectra;
		SpectraResult->GetNormalizedChannelConstantQAtTime(PlaybackPercent * DurationSoundSource, 0, spectra);
		for (auto spectraRecipient : Recipients)
		{
			if (!spectraRecipient.Recipient)
			{
				UE_LOG(LogAudioAnalyzer, Warning, TEXT("AEQ_SpectraAnalyzer::AudioPlaybackUpdate - recipient - actor of array null "));
				break;
			}

			if (!spectraRecipient.Recipient->Implements<USR_IReceivingAudio>())
			{
				UE_LOG(LogAudioAnalyzer, Warning, TEXT("AEQ_SpectraAnalyzer::AudioPlaybackUpdate - actor - %s - not have interface IReceivingAudio"),
				       *GetDebugName(spectraRecipient.Recipient));
				break;
			}

			if (spectraRecipient.IndexChannelSpectra == -1)
				ISR_IReceivingAudio::Execute_SpectraUpdated(spectraRecipient.Recipient, spectra);
			else
			{
				if (spectra.IsValidIndex(spectraRecipient.IndexChannelSpectra))
				{
					ISR_IReceivingAudio::Execute_SpectraRecipientUpdated(spectraRecipient.Recipient, spectra[spectraRecipient.IndexChannelSpectra]);
				}
				else
					UE_LOG(LogAudioAnalyzer, Warning,
				       TEXT("AEQ_SpectraAnalyzer::AudioPlaybackUpdate - IndexChannelSpectra not valid to spectra check index or setting of SpectraResult"));
			}
		}
	}
}
