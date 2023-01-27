// Fill out your copyright notice in the Description page of Project Settings.


#include "ABPlayerController.h"
#include "ABHUDWidget.h"
#include "ABPlayerState.h"
#include "ABCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "ABGameplayWidget.h"
#include "ABGameplayResultWidget.h"
#include "ABGameState.h"

AABPlayerController::AABPlayerController()
{
	static ConstructorHelpers::FClassFinder<UABHUDWidget> UI_HUD_C(TEXT("/Game/Book/UI/UI_HUD.UI_HUD_C"));
	if(UI_HUD_C.Succeeded())
	{
		HUDWidgetClass=UI_HUD_C.Class;
	}

	//입력 액션
	static ConstructorHelpers::FObjectFinder<UInputAction> IA_GAMEPAUSE_AB(TEXT("/Game/Book/Input/Actions/IA_GamePause_AB.IA_GamePause_AB"));
	if(IA_GAMEPAUSE_AB.Succeeded())
	{
		GamePauseAction=IA_GAMEPAUSE_AB.Object;
	}

	//입력 매핑 콘텍스트
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> IMC_PLAYERCONTROLLER_AB(TEXT("/Game/Book/Input/IMC_PlayerController_AB.IMC_PlayerController_AB"));
	if(IMC_PLAYERCONTROLLER_AB.Succeeded())
	{
		PlayerControllerMappingContext=IMC_PLAYERCONTROLLER_AB.Object;
	}

	static ConstructorHelpers::FClassFinder<UABGameplayWidget> UI_MENU_C(TEXT("/Game/Book/UI/UI_Menu.UI_Menu_C"));
	if(UI_MENU_C.Succeeded())
	{
		MenuWidgetClass=UI_MENU_C.Class;
	}

	static ConstructorHelpers::FClassFinder<UABGameplayResultWidget> UI_RESULT_C(TEXT("/Game/Book/UI/UI_Result.UI_Result_C"));
	if(UI_RESULT_C.Succeeded())
	{
		ResultWidgetClass=UI_RESULT_C.Class;
	}
}

UABHUDWidget* AABPlayerController::GetHUDWidget() const
{
	return HUDWidget;
}

void AABPlayerController::NPCKill(AABCharacter* KilledNPC) const
{
	ABPlayerState->AddExp(KilledNPC->GetExp());
}

void AABPlayerController::AddGameScore() const
{
	ABPlayerState->AddGameScore();
}

void AABPlayerController::ChangeInputMode(bool bGameMode)
{
	if(bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor=false;
	}
	else
	{
		SetInputMode(UIInputMode);
		bShowMouseCursor=true;
	}
}

void AABPlayerController::ShowResultUI()
{
	auto ABGameState=Cast<AABGameState>(UGameplayStatics::GetGameState(this));
	ABCHECK(nullptr!=ABGameState);
	ResultWidget->BindGameState(ABGameState);
	
	ResultWidget->AddToViewport();
	ChangeInputMode(false);
}

void AABPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// This calls the handler function (a UFUNCTION) by name on every tick while the input conditions are met, such as when holding a movement key down.
		//입력 액션 GamePause
		if (GamePauseAction)
		{
			EnhancedInputComponent->BindAction(GamePauseAction, ETriggerEvent::Started, this, &AABPlayerController::OnGamePause);	
		}
	}
}

void AABPlayerController::OnGamePause()
{
	MenuWidget=CreateWidget<UABGameplayWidget>(this, MenuWidgetClass);
	ABCHECK(nullptr!=MenuWidget);
	MenuWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
}

void AABPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ABLOG_S(Warning);
}

void AABPlayerController::OnPossess(APawn* aPawn)
{
	ABLOG_S(Warning);
	Super::OnPossess(aPawn);
}

void AABPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeInputMode(true);

	HUDWidget=CreateWidget<UABHUDWidget>(this, HUDWidgetClass);
	ABCHECK(nullptr!=HUDWidget);
	HUDWidget->AddToViewport();

	ResultWidget=CreateWidget<UABGameplayResultWidget>(this, ResultWidgetClass);
	ABCHECK(nullptr!=ResultWidget);

	ABPlayerState=Cast<AABPlayerState>(PlayerState);
	ABCHECK(nullptr!=ABPlayerState);
	HUDWidget->BindPlayerState(ABPlayerState);
	ABPlayerState->OnPlayerStateChanged.Broadcast();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover mappings.
		Subsystem->ClearAllMappings();
			
		// Add each mapping context, along with their priority values. Higher values outprioritize lower values.
		Subsystem->AddMappingContext(PlayerControllerMappingContext, 200);
			
	}
}
