// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeGameMode.h"
#include "SnakePlayerController.h"
#include "SnakePawn.h"
#include "UObject/ConstructorHelpers.h"
ASnakeGameMode::ASnakeGameMode()
{

    // Use Blueprint version of the SnakePawn
    ConstructorHelpers::FClassFinder<ASnakePawn> PlayerPawnBPClass(TEXT("/Game/blueprints/SnakePawn"));
   
    if (PlayerPawnBPClass.Succeeded())
    {
     
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
    else 
    {
      
        DefaultPawnClass = ASnakePawn::StaticClass();
    }

    PlayerControllerClass = ASnakePlayerController::StaticClass();
   
}

