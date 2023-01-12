// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"
#include "ABAnimInstance.h"
#include "DrawDebugHelpers.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
AABCharacter::AABCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRIMGARM"));
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength=400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	//스켈레탈 메시
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if(SK_CARDBOARD.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	//애님인스턴스클래스
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/Book/Animations/WarriorAnimBlueprint.WarriorAnimBlueprint_C"));
	if(WARRIOR_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}

	//입력 액션
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_UPDOWN_AB(TEXT("/Game/Book/Input/Actions/IA_UpDown_AB.IA_UpDown_AB"));
	if(IA_UPDOWN_AB.Succeeded())
	{
		UpDownAction=IA_UPDOWN_AB.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LEFTRIGHT_AB(TEXT("/Game/Book/Input/Actions/IA_LeftRight_AB.IA_LeftRight_AB"));
	if(IA_LEFTRIGHT_AB.Succeeded())
	{
		LeftRightAction=IA_LEFTRIGHT_AB.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_LOOKUP_AB(TEXT("/Game/Book/Input/Actions/IA_LookUp_AB.IA_LookUp_AB"));
	if(IA_LOOKUP_AB.Succeeded())
	{
		LookUpAction=IA_LOOKUP_AB.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_TURN_AB(TEXT("/Game/Book/Input/Actions/IA_Turn_AB.IA_Turn_AB"));
	if(IA_TURN_AB.Succeeded())
	{
		TurnAction=IA_TURN_AB.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_JUMP_AB(TEXT("/Game/Book/Input/Actions/IA_Jump_AB.IA_Jump_AB"));
	if(IA_JUMP_AB.Succeeded())
	{
		JumpAction=IA_JUMP_AB.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> IA_ATTACK_AB(TEXT("/Game/Book/Input/Actions/IA_Attack_AB.IA_Attack_AB"));
	if(IA_ATTACK_AB.Succeeded())
	{
		AttackAction=IA_ATTACK_AB.Object;
	}
	
	//Multiple key Rollover, Chorded action
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_VIEWCHANGE_AB(TEXT("/Game/Book/Input/Actions/IA_ViewChange_AB.IA_ViewChange_AB"));
	if(IA_VIEWCHANGE_AB.Succeeded())
	{
		ViewChangeAction=IA_VIEWCHANGE_AB.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_KEYBOARDMODIFIERSHIFT_AB(TEXT("/Game/Book/Input/Actions/IA_KeyboardModifierShift_AB.IA_KeyboardModifierShift_AB"));
	if(IA_KEYBOARDMODIFIERSHIFT_AB.Succeeded())
	{
		KeyboardModifierShiftAction=IA_KEYBOARDMODIFIERSHIFT_AB.Object;
	}
	
	//입력 매핑 콘텍스트
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_DEFAULT_AB(TEXT("/Game/Book/Input/IMC_Default_AB.IMC_Default_AB"));
	if(IMC_DEFAULT_AB.Succeeded())
	{
		DefaultMappingContext=IMC_DEFAULT_AB.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_KEYBOARD_AB(TEXT("/Game/Book/Input/IMC_Keyboard_AB.IMC_Keyboard_AB"));
	if(IMC_KEYBOARD_AB.Succeeded())
	{
		KeboardMappingContext=IMC_KEYBOARD_AB.Object;
	}

	FName WeaponSocket(TEXT("hand_rSocket"));
	if(GetMesh()->DoesSocketExist(WeaponSocket))
	{
		Weapon=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight"));
		if(SK_WEAPON.Succeeded())
		{
			Weapon->SetSkeletalMesh(SK_WEAPON.Object);
		}

		Weapon->SetupAttachment(GetMesh(), WeaponSocket);
	}
	
	SetControlMode(EControlMode::DIABLO);

	ArmLengthSpeed=3.0f;
	ArmRotationSpeed=10.0f;
	GetCharacterMovement()->JumpZVelocity=800.0f;

	IsAttacking=false;

	MaxCombo=4;
	AttackEndComboState();

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ABCharacter"));

	AttackRange=200.0f;
	AttackRadius=50.0f;
}

// Called when the game starts or when spawned
void AABCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context

	// Make sure that we have a valid PlayerController
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
			Subsystem->ClearAllMappings();
			
			// Add each mapping context, along with their priority values. Higher values outprioritize lower values.
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
			Subsystem->AddMappingContext(KeboardMappingContext, 100);
			
		}
	}
	
}

void AABCharacter::SetControlMode(EControlMode NewControlMode)
{
	CurrentControlMode=NewControlMode;
	
	switch(CurrentControlMode)
	{
	case EControlMode::GTA:
		//SpringArm->TargetArmLength=450.0f;
		//SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		ArmLengthTo=450.0f;
		SpringArm->bUsePawnControlRotation=true;
		SpringArm->bInheritPitch=true;
		SpringArm->bInheritRoll=true;
		SpringArm->bInheritYaw=true;
		SpringArm->bDoCollisionTest=true;
		bUseControllerRotationYaw=false;
		GetCharacterMovement()->bOrientRotationToMovement=true;
		GetCharacterMovement()->bUseControllerDesiredRotation=false;
		GetCharacterMovement()->RotationRate=FRotator(0.0f, 720.0f, 0.0f);
		break;
	case EControlMode::DIABLO:
		//SpringArm->TargetArmLength=800.0f;
		//SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		ArmLengthTo=800.0f;
		ArmRotationTo=FRotator(-45.0f, 0.0f, 0.0f);
		SpringArm->bUsePawnControlRotation=false;
		SpringArm->bInheritPitch=false;
		SpringArm->bInheritRoll=false;
		SpringArm->bInheritYaw=false;
		SpringArm->bDoCollisionTest=false;
		bUseControllerRotationYaw=false;
		GetCharacterMovement()->bOrientRotationToMovement=false;
		GetCharacterMovement()->bUseControllerDesiredRotation=true;
		GetCharacterMovement()->RotationRate=FRotator(0.0f, 720.0f, 0.0f);
		break;
	}
}

// Called every frame
void AABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArm->TargetArmLength=FMath::FInterpTo(SpringArm->TargetArmLength, ArmLengthTo, DeltaTime, ArmLengthSpeed);

	switch(CurrentControlMode)
	{
	case EControlMode::DIABLO:
		SpringArm->SetRelativeRotation(FMath::RInterpTo(SpringArm->GetRelativeRotation(), ArmRotationTo, DeltaTime, ArmRotationSpeed));
		break;
	}
	
	switch(CurrentControlMode)
	{
	case EControlMode::DIABLO:
		if(DirectionToMove.SizeSquared()>0.0f)
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(DirectionToMove).Rotator());
			AddMovementInput(DirectionToMove);
		}
		break;
	}
}

void AABCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABAnim=Cast<UABAnimInstance>(GetMesh()->GetAnimInstance());
	ABCHECK(nullptr!=ABAnim);

	ABAnim->OnMontageEnded.AddDynamic(this, &AABCharacter::OnAttackMontageEnded);

	ABAnim->OnNextAttackCheck.AddLambda([this]()->void
	{
		ABLOG(Warning, TEXT("OnNextAttackCheck"));
		CanNextCombo=false;

		if(IsComboInputOn)
		{
			AttackStartComboState();
			ABAnim->JumpToAttackMontageSection(CurrentCombo);
		}
	});

	ABAnim->OnAttackHitCheck.AddUObject(this, &AABCharacter::AttackCheck);
}

float AABCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	float FinalDamage=Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ABLOG(Warning, TEXT("Actor : %s took Damage : %f"), *GetName(), FinalDamage);

	if(FinalDamage>0.0f)
	{
		ABAnim->SetDeadAnim();
		SetActorEnableCollision(false);
	}
	
	return FinalDamage;
}

// Called to bind functionality to input
void AABCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// This calls the handler function (a UFUNCTION) by name on every tick while the input conditions are met, such as when holding a movement key down.
		//입력 액션 UpDown
		if (UpDownAction)
		{
			EnhancedInputComponent->BindAction(UpDownAction, ETriggerEvent::Triggered, this, &AABCharacter::UpDown);	
			EnhancedInputComponent->BindAction(UpDownAction, ETriggerEvent::Completed, this, &AABCharacter::UpDown);	
		}
		//입력 액션 LeftRight
		if (LeftRightAction)
		{
			EnhancedInputComponent->BindAction(LeftRightAction, ETriggerEvent::Triggered, this, &AABCharacter::LeftRight);
			EnhancedInputComponent->BindAction(LeftRightAction, ETriggerEvent::Completed, this, &AABCharacter::LeftRight);
		}
		//입력 액션 LookUp
		if (LookUpAction)
		{
			EnhancedInputComponent->BindAction(LookUpAction, ETriggerEvent::Triggered, this, &AABCharacter::LookUp);
		}
		//입력 액션 Turn
		if (TurnAction)
		{
			EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &AABCharacter::Turn);
		}
		//입력 액션 Jump
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AABCharacter::Jump);
		}
		//입력 액션 Attack
		if (AttackAction)
		{
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AABCharacter::Attack);
		}
		//입력 액션 ViewChange
		if (ViewChangeAction)
		{
			EnhancedInputComponent->BindAction(ViewChangeAction, ETriggerEvent::Started, this, &AABCharacter::ViewChange);
		}
	}
	
}

void AABCharacter::UpDown(const FInputActionValue& Value)
{
	switch(CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), Value.GetMagnitude());
		break;
	case EControlMode::DIABLO:
		DirectionToMove.X=Value.GetMagnitude();
		break;
	}
}

void AABCharacter::LeftRight(const FInputActionValue& Value)
{
	switch(CurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), Value.GetMagnitude());
		break;
	case EControlMode::DIABLO:
		DirectionToMove.Y=Value.GetMagnitude();
		break;
	}
}

void AABCharacter::LookUp(const FInputActionValue& Value)
{
	switch(CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerPitchInput(Value.GetMagnitude());
		break;
	}
}

void AABCharacter::Turn(const FInputActionValue& Value)
{
	switch(CurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerYawInput(Value.GetMagnitude());
		break;
	}
}

void AABCharacter::ViewChange()
{
	switch(CurrentControlMode)
	{
	case EControlMode::GTA:
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIABLO);
		break;
	case EControlMode::DIABLO:
		GetController()->SetControlRotation(SpringArm->GetRelativeRotation());
		SetControlMode(EControlMode::GTA);
		break;
	}
}

void AABCharacter::Attack()
{
	if(IsAttacking)
	{
		ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 1, MaxCombo));
		if(CanNextCombo)
		{
			IsComboInputOn=true;
		}
	}
	else
	{
		ABCHECK(CurrentCombo==0);
		AttackStartComboState();
		ABAnim->PlayAttackMontage();
		ABAnim->JumpToAttackMontageSection(CurrentCombo);
		IsAttacking=true;
	}
}

void AABCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	ABCHECK(IsAttacking);
	ABCHECK(CurrentCombo>0);
	IsAttacking=false;
	AttackEndComboState();
}

void AABCharacter::AttackStartComboState()
{
	CanNextCombo=true;
	IsComboInputOn=false;
	ABCHECK(FMath::IsWithinInclusive<int32>(CurrentCombo, 0, MaxCombo-1));
	CurrentCombo=FMath::Clamp<int32>(CurrentCombo+1, 1, MaxCombo);
}

void AABCharacter::AttackEndComboState()
{
	IsComboInputOn=false;
	CanNextCombo=false;
	CurrentCombo=0;
}

void AABCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);
	bool bResult=GetWorld()->SweepSingleByChannel(
	HitResult,
	GetActorLocation(),
	GetActorLocation()+GetActorForwardVector()*200.0f,
	FQuat::Identity,
	ECollisionChannel::ECC_GameTraceChannel2,
	FCollisionShape::MakeSphere(50.0f),
	Params);

#if ENABLE_DRAW_DEBUG

	FVector TraceVec=GetActorForwardVector() *AttackRange;
	FVector Center=GetActorLocation()+TraceVec*0.5f;
	float HalfHeight=AttackRange*0.5f+AttackRadius;
	FQuat CapsuleRot=FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor=bResult?FColor::Green:FColor::Red;
	float DebugLifeTime=5.0f;

	DrawDebugCapsule(GetWorld(),
		Center,
		HalfHeight,
		AttackRadius,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime);
#endif
	
	if(bResult)
	{
		if(IsValid(HitResult.GetActor()))
		{
			ABLOG(Warning, TEXT("Hit ACtor Name: %s"), *HitResult.GetActor()->GetName());

			FDamageEvent DamageEvent;
			HitResult.GetActor()->TakeDamage(50.0f, DamageEvent, GetController(), this);
		}
	}
}
