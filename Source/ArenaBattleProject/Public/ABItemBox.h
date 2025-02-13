// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattleProject.h"
#include "GameFramework/Actor.h"
#include "ABItemBox.generated.h"

UCLASS()
class ARENABATTLEPROJECT_API AABItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AABItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:
	UPROPERTY(VisibleAnywhere, Category=Box)
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category=Box)
	UStaticMeshComponent* Box;

	UPROPERTY(VisibleAnywhere, Category=Effect)
	UNiagaraComponent* Effect;

	UPROPERTY(EditInstanceOnly, Category=Box)
	TSubclassOf<class AABWeapon> WeaponItemClass;
	
private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEffectFinished(class UNiagaraComponent* NSystem);
	
};
