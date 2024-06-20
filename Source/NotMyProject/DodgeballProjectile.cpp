// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeballProjectile.h"
#include "Components/SphereComponent.h"
#include "NotMyProjectCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Sets default values
ADodgeballProjectile::ADodgeballProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the SphereComponent object
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));

	// Set its radius to 35 cm
	SphereComponent->SetSphereRadius(35.0F);

	// Set its Collision Preset to the Dodgeball preset we created
	SphereComponent->SetCollisionProfileName(FName("Dodgeball"));

	// Simulate physics
	SphereComponent->SetSimulatePhysics(true);

	// Simulation generates Hit events
	SphereComponent->SetNotifyRigidBodyCollision(true);

	// Listen to the onComponentHit even by binding it to a custom function for OnHit
	SphereComponent->OnComponentHit.AddDynamic(this, &ADodgeballProjectile::OnHit);

	// Set this Sphere Component as the root component
	// otherwise collision will not behave correctly!
	RootComponent = SphereComponent;

	// Create the ProjectileMovement object
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	// Set the initial speed to 1500 units
	ProjectileMovement->InitialSpeed = 1500.0F;
}

// Called when the game starts or when spawned
void ADodgeballProjectile::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(5.0F);	
}

// Called every frame
void ADodgeballProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADodgeballProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<ANotMyProjectCharacter>(otherActor) != nullptr)
		Destroy();
}