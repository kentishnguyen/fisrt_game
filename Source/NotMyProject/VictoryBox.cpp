// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryBox.h"
#include "Components/BoxComponent.h"
#include "NotMyProjectCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
// Sets default values
AVictoryBox::AVictoryBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = RootScene;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetupAttachment(RootComponent);
	// Set the BoxExtent property for the CollisionBox to 60 units in all axes
	// This will cause the BoxComponent to have a size of 120 units in all directions
	CollisionBox->SetBoxExtent(FVector(60.0F, 60.0F, 60.0F));
	// Offset its relative position on the Z-axis by 120 units
	CollisionBox->SetRelativeLocation(FVector(0.0F,0.0F, 120.0F));

}

// Called when the game starts or when spawned
void AVictoryBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVictoryBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


