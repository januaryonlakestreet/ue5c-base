// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakePlayerController.h"
#include "CameraBase.h"
#include "Kismet/GameplayStatics.h"
#include "SnakeGameMode.h"
#include "SnakePawn.h"
#include "GameMenu.h"



ASnakePlayerController::ASnakePlayerController()
{
    ConstructorHelpers::FClassFinder<UGameMenu> GameMenuFinder(TEXT("/Game/ui/GameMenu"));
    GameMenuClass = GameMenuFinder.Class;
}

void ASnakePlayerController::BeginPlay()
{
    if (GEngine)
    {

        TArray<AActor*> FoundActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraBase::StaticClass(), FoundActors);

        if (FoundActors.Num() > 0)
        {
            for (int a = 0; a < FoundActors.Num(); a++)
            {
                if (FoundActors[a]->ActorHasTag(FName("GameCam")))
                {
                    GameCam = FoundActors[a];
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Found game cam"));
                }
                if (FoundActors[a]->ActorHasTag(FName("MenuCam")))
                {
                    MenuCam = FoundActors[a];
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Found Menu cam"));
                }
            }
           
        }
      
        GameMenuInstance = CreateWidget<UGameMenu>(GetWorld(), GameMenuClass);
        GameMenuInstance->AddToViewport();




        APawn* pwn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        if (pwn)
        {
           Possess(pwn);
        }
        

      
    }

}
