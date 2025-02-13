// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ABCharacterSetting.generated.h"

/**
 * 
 */
UCLASS(Config=ArenaBattleProject)
class ARENABATTLESETTING_API UABCharacterSetting : public UObject
{
	GENERATED_BODY()

public:
	UABCharacterSetting();

	UPROPERTY(Config)
	TArray<FSoftObjectPath> CharacterAssets;
};
