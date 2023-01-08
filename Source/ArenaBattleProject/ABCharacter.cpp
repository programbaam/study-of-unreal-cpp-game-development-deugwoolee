// Fill out your copyright notice in the Description page of Project Settings.


#include "ABCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Components/CapsuleComponent.h"

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
	
	//입력 매핑 콘텍스트
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_DEFAULT_AB(TEXT("/Game/Book/Input/IMC_Default_AB.IMC_Default_AB"));
	if(IMC_DEFAULT_AB.Succeeded())
	{
		DefaultMappingContext=IMC_DEFAULT_AB.Object;
	}

	SetControlMod(0);
	
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
		}
	}
	
}

void AABCharacter::SetControlMod(int32 ControlMode)
{
	if(ControlMode==0)
	{
		SpringArm->TargetArmLength=450.0f;
		SpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		SpringArm->bUsePawnControlRotation=true;
		SpringArm->bInheritPitch=true;
		SpringArm->bInheritRoll=true;
		SpringArm->bInheritYaw=true;
		SpringArm->bDoCollisionTest=true;
		bUseControllerRotationYaw=false;
		GetCharacterMovement()->bOrientRotationToMovement=true;
		GetCharacterMovement()->RotationRate=FRotator(0.0f, 720.0f, 0.0f);
	}
}

// Called every frame
void AABCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		}
		//입력 액션 LeftRight
		if (LeftRightAction)
		{
			EnhancedInputComponent->BindAction(LeftRightAction, ETriggerEvent::Triggered, this, &AABCharacter::LeftRight);
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
	}
	
}

void AABCharacter::UpDown(const FInputActionValue& Value)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), Value.GetMagnitude());
}

void AABCharacter::LeftRight(const FInputActionValue& Value)
{
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), Value.GetMagnitude());
}

void AABCharacter::LookUp(const FInputActionValue& Value)
{
	AddControllerPitchInput(Value.GetMagnitude());
}

void AABCharacter::Turn(const FInputActionValue& Value)
{
	AddControllerYawInput(Value.GetMagnitude());
}

