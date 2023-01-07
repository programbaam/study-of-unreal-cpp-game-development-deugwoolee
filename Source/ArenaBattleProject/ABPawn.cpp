// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

// Sets default values
AABPawn::AABPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule=CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	Mesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	Movement=CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	SpringArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	Camera=CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent=Capsule;
	Mesh->SetupAttachment(Capsule);
	SpringArm->SetupAttachment(Capsule);
	Camera->SetupAttachment(SpringArm);

	Capsule->SetCapsuleHalfHeight(88.0f);
	Capsule->SetCapsuleRadius(34.0f);
	Mesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	SpringArm->TargetArmLength=400.0f;
	SpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if(SK_CARDBOARD.Succeeded())
	{
		Mesh->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_DEFAULT_AB(TEXT("/Game/Book/Input/IMC_Default_AB.IMC_Default_AB"));
	if(IMC_DEFAULT_AB.Succeeded())
	{
		DefaultMappingContext=IMC_DEFAULT_AB.Object;
	}
	
}

// Called when the game starts or when spawned
void AABPawn::BeginPlay()
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

// Called every frame
void AABPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AABPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void AABPawn::PossessedBy(AController* NewController)
{
	ABLOG_S(Warning);
	Super::PossessedBy(NewController);
}


// Called to bind functionality to input
void AABPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// This calls the handler function (a UFUNCTION) by name on every tick while the input conditions are met, such as when holding a movement key down.
		if (DefaultMappingContext->GetMapping(0).Action)
		{
			EnhancedInputComponent->BindAction(DefaultMappingContext->GetMapping(0).Action, ETriggerEvent::Triggered, this, &AABPawn::UpDown);	
		}
		if (DefaultMappingContext->GetMapping(1).Action)
		{
			EnhancedInputComponent->BindAction(DefaultMappingContext->GetMapping(1).Action, ETriggerEvent::Triggered, this, &AABPawn::LeftRight);
		}
	}
}

void AABPawn::UpDown(const FInputActionValue& Value)
{
	AddMovementInput(GetActorForwardVector(), Value.GetMagnitude());
}

void AABPawn::LeftRight(const FInputActionValue& Value)
{
	AddMovementInput(GetActorRightVector(), Value.GetMagnitude());
}


