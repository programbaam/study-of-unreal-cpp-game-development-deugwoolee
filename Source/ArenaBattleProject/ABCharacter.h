// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ArenaBattleProject.h"
#include "InputAction.h"
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

	enum class EControlMode
	{
		GTA,
		DIABLO
	};
	
	void SetControlMode(EControlMode NewControlMode);
	EControlMode CurrentControlMode = EControlMode::GTA;
	FVector DirectionToMove=FVector::ZeroVector;

	float ArmLengthTo=0.0f;
	FRotator ArmRotationTo=FRotator::ZeroRotator;
	float ArmLengthSpeed=0.0f;
	float ArmRotationSpeed=0.0f;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool CanSetWeapon();
	void SetWeapon(class AABWeapon* NewWeapon);

	UPROPERTY(VisibleAnywhere, Category=Weapon)
	class AABWeapon* CurrentWeapon;
	
	UPROPERTY(VisibleAnywhere, Category=Weapon)
	USkeletalMeshComponent* Weapon;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* UpDownAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* LeftRightAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* LookUpAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* TurnAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* AttackAction;
	
	//Multiple key Rollover, Chorded action
	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* ViewChangeAction;

	UPROPERTY(VisibleAnywhere, Category = Input)
	UInputAction* KeyboardModifierShiftAction;
	
	/** MappingContext */
	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(VisibleAnywhere, Category = Input)
	class UInputMappingContext* KeboardMappingContext;
	
private:
	void UpDown(const FInputActionValue& Value);
	void LeftRight(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);

	void ViewChange();
	void Attack();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void AttackStartComboState();
	void AttackEndComboState();
	void AttackCheck();
	
private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Attack, Meta=(AllowPrivateAccess=true))
	bool IsAttacking;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Attack, Meta=(AllowPrivateAccess=true))
	bool CanNextCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Attack, Meta=(AllowPrivateAccess=true))
	bool IsComboInputOn;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Attack, Meta=(AllowPrivateAccess=true))
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Attack, Meta=(AllowPrivateAccess=true))
	int32 MaxCombo;
	
	UPROPERTY()
	class UABAnimInstance* ABAnim;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Attack, Meta=(AllowPrivateAccess=true))
	float AttackRange;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category=Attack, Meta=(AllowPrivateAccess=true))
	float AttackRadius;
	
};
