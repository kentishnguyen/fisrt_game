// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "DodgeballProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SightSource = CreateDefaultSubobject<USceneComponent>(TEXT("Sight Source"));
	SightSource->SetupAttachment(RootComponent);
}

bool AEnemyCharacter::LookAtActor(AActor* TargetActor)
{
	// If TargetActor is nullptr, no valid actor
	// to check.
	if (TargetActor == nullptr)
		return false;

	if (CanSeeActor(TargetActor))
	{
		FVector Start = GetActorLocation();
		FVector End = TargetActor->GetActorLocation();
		// Calculate the required rotation for the start
		// point to face the end point here
		FRotator LookAtRotation =
			UKismetMathLibrary::FindLookAtRotation(Start, End);

		// Set the enemy character's rotation to that rotation
		SetActorRotation(LookAtRotation);

		return true;
	}
	return false;
}

bool AEnemyCharacter::CanSeeActor(const AActor* TargetActor) const
{
	// If TargetActor is nullptr, no valid actor
	// to check.
	if (TargetActor == nullptr)
		return false;

	// Object for storing the result of Line Trace
	FHitResult Hit;

	// Where the Line Trace starts and ends
	FVector Start = SightSource->GetComponentLocation();
	FVector End = TargetActor->GetActorLocation();

	// The trace channel we want to compare against
	ECollisionChannel Channel = ECollisionChannel::ECC_GameTraceChannel1;

	// Tell the Line Trace to ignore the actor that is
	// executing this Line Trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	// Ignore the target we are checking for
	QueryParams.AddIgnoredActor(TargetActor);

	// Execute the Line Trace
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, Channel, QueryParams);

	// Show the Line Trace inside the game
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	// If there were a blocking hit, we can't see target
	return !Hit.bBlockingHit;
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::ThrowDodgeball()
{
	if (DodgeballClass == nullptr)
	{
		return;
	}

	FVector ForwardVector = GetActorForwardVector();
	float SpawnDistance = 40.0F;
	FVector SpawnLocation = GetActorLocation() + (ForwardVector * SpawnDistance);
	// Spawn new dodgeball object
	//GetWorld()->SpawnActor<ADodgeballProjectile>(DodgeballClass, SpawnLocation, GetActorRotation());

	FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

	ADodgeballProjectile* Projectile = GetWorld()->SpawnActorDeferred<ADodgeballProjectile>(DodgeballClass, SpawnTransform);

	Projectile->GetProjectileMovementComponent()->InitialSpeed = 2200.0F;
	Projectile->FinishSpawning(SpawnTransform);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Fetch the character currently being controlled by
	// the player
	ACharacter* PlayerCharacter =
		UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	// Look at the player character every frame!
	bCanSeePlayer = LookAtActor(PlayerCharacter);

	if (bCanSeePlayer != bPreviousCanSeePlayer)
	{
		if (bCanSeePlayer)
			// Start throwing dodgeballs
			GetWorldTimerManager().SetTimer(ThrowTimerHandle, this, &AEnemyCharacter::ThrowDodgeball, ThrowingInterval, true, ThrowingDelay);
		else
			// Stop throwing dodgeballs
			GetWorldTimerManager().ClearTimer(ThrowTimerHandle);
	}

	bPreviousCanSeePlayer = bCanSeePlayer;
}
