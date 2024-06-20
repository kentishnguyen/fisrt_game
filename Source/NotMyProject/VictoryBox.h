// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VictoryBox.generated.h"

UCLASS()
class NOTMYPROJECT_API AVictoryBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVictoryBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	// This SceneComponent property will act as the RootComponent,similar
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=VictoryBox, meta=(AllowPrivateAccess="true"))
	class USceneComponent* RootScene;

	// This box component will check for overlap events with the player character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=VictoryBox, meta=(AllowPrivateAccess="true"))
	class UBoxComponent* CollisionBox;
};
