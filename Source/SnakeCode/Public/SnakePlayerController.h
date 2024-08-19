// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameMenu.h"
#include "SnakePlayerController.generated.h"


/**
 * 
 */
UCLASS()
class SNAKECODE_API ASnakePlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;

	AActor* GameCam;
	AActor* MenuCam;

	TSubclassOf<UGameMenu> GameMenuClass;
	UGameMenu* GameMenuInstance;
public:
	AActor* GetMenuCam(){ return MenuCam; }
	AActor* GetGameCam() { return GameCam; }


	ASnakePlayerController();
	
};
