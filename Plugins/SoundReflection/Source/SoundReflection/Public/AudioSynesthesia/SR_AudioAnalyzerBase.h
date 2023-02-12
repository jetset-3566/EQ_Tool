// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"
#include "SR_AudioAnalyzerBase.generated.h"


SOUNDREFLECTION_API DECLARE_LOG_CATEGORY_EXTERN(LogAudioAnalyzer, Log, All);
UCLASS(Blueprintable, BlueprintType)
class SOUNDREFLECTION_API ASR_AudioAnalyzerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASR_AudioAnalyzerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BindSoundComponent();
	//Keep inDelay = 0.0 to start play immediately
	UFUNCTION(BlueprintCallable, Category="AudioAnalizer")
	void StartPlaySound(float inDelay = 0.0f);

	
	UPROPERTY(BlueprintReadOnly, Category="AudioAnalizer")
	TObjectPtr<USoundWave> SoundSource;
	UPROPERTY(BlueprintReadOnly, Category="AudioAnalizer")
	float DurationSoundSource = 0.0f;

	UFUNCTION()
	virtual void AudioPlaybackUpdate(const USoundWave* PlayingSoundWave,const float PlaybackPercent);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AudioAnalizer")
	UAudioComponent* AudioComponent = nullptr;

private:
	FTimerHandle m_StartDelay;
};
