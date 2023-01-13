// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattleProject.h"
#include "Blueprint/UserWidget.h"
#include "ABCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENABATTLEPROJECT_API UABCharacterWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void BindCharaterStat(class UABCharacterStatComponent* NewCharacterStat);

protected:
	virtual void NativeConstruct() override;
	void UpdateHPWidget();

private:
	TWeakObjectPtr<class UABCharacterStatComponent> CurrentCharacterStat;

	UPROPERTY()
	class UProgressBar* HPProgressBar;
	
};
