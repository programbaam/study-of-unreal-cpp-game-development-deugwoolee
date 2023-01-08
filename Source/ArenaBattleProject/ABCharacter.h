// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattleProject.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "ABCharacter.generated.h"

UCLASS()
class ARENABATTLEPROJECT_API AABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	UCameraComponent* Camera;

	/** MappingContext */
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputMappingContext* DefaultMappingContext;
	
private:
	void UpDown(const FInputActionValue& Value);
	void LeftRight(const FInputActionValue& Value);
	
};
