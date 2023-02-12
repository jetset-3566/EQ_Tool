// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioSynesthesia/SR_AudioAnalyzerBase.h"

DEFINE_LOG_CATEGORY(LogAudioAnalyzer);
// Sets default values
ASR_AudioAnalyzerBase::ASR_AudioAnalyzerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(FName("AudioComponent"));
	SetRootComponent(AudioComponent);
}

// Called when the game starts or when spawned
void ASR_AudioAnalyzerBase::BeginPlay()
{
	Super::BeginPlay();

	
	
}

// Called every frame
void ASR_AudioAnalyzerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASR_AudioAnalyzerBase::BindSoundComponent()
{
	if (!AudioComponent && AudioComponent->IsPlaying())
		return;
}

void ASR_AudioAnalyzerBase::StartPlaySound(float inDelay)
{
	if (FMath::IsNearlyZero(inDelay))
		BindSoundComponent();
	else
		GetWorldTimerManager().SetTimer(m_StartDelay,this, &ASR_AudioAnalyzerBase::BindSoundComponent,inDelay,false);
}

void ASR_AudioAnalyzerBase::AudioPlaybackUpdate(const USoundWave* PlayingSoundWave,const float Percent)
{
	if (!PlayingSoundWave)
		return;
}
