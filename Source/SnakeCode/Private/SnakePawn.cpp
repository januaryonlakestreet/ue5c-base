// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePawn.h"
#include "SnakePlayerController.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASnakePawn::ASnakePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UInputMappingContext> PlayerMappingContextFinder(TEXT("/Game/input/InputMappingContext"));
	InputMapping = PlayerMappingContextFinder.Object;

	ConstructorHelpers::FObjectFinder<UInputAction> MoveActionFinder(TEXT("/Game/input/SpaceAction"));
	SpaceAction = MoveActionFinder.Object;
}

// Called when the game starts or when spawned
void ASnakePawn::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("BeginP!!!!lay has been called!"));

	ASnakePlayerController* spc = Cast<ASnakePlayerController>(this->GetController());
	if (spc)
	{
		spc->SetViewTarget(spc->GetMenuCam());
	}
		
	if (GetController() == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("not possessed!"));
	}
	ASnakePlayerController* PC = Cast<ASnakePlayerController>(GetController());
	if (PC && !PC->InputEnabled())
	{
		PC->EnableInput(PC);
	}



	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 1);
		}
	}
}

// Called every frame
void ASnakePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	
	// Ensure the input component is an EnhancedInputComponent
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind the Move Action
	EnhancedInputComponent->BindAction(SpaceAction, ETriggerEvent::Started, this, &ASnakePawn::SpaceActionEvent);
	
}

void ASnakePawn::SpaceActionEvent(const FInputActionValue& Values)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Space event has been called!"));
}



