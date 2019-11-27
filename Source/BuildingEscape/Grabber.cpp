// Copyright John Doe.


#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
auto UGrabber::BeginPlay() -> void
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("is at !"));
	
}


// Called every frame
auto UGrabber::TickComponent(const float DeltaTime, const ELevelTick TickType,
                             FActorComponentTickFunction* ThisTickFunction) -> void
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	// TODO Log out to test
	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Position: %s"),
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString()
	);

	const auto LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	
	//Draw a red trace in the world to visualize

	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0.f,
		10.f
	);
	
	// Ray-cast out to reach distance

	// See what we hit
}

