// Copyright John Doe.


#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

/// Look for attached Physics Handle
auto UGrabber::FindPhysicsHandleComponent() -> void
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Physics Handle component"), *GetOwner()->GetName())
	}
}

/// Look for attached Input Component (only appears at run time)
auto UGrabber::SetupInputComponent() -> void
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		/// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing Input component"), *GetOwner()->GetName())
	}
}

// Called when the game starts
auto UGrabber::BeginPlay() -> void
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

auto UGrabber::Grab() -> void
{
	/// LINE TRACE and see if we reach any actors with physics body collision channel set
	const auto HitResult = GetFirstPhysicsBodyInReach();
	const auto ComponentToGrab = HitResult.GetComponent(); // Gets the mesh in our case
	const auto ActorHit = HitResult.GetActor();

	/// If we hit something then attach a physics handle
	if(ActorHit)
	{
		if (!PhysicsHandle) { return; }
		PhysicsHandle->GrabComponentAtLocation(
            ComponentToGrab,
            NAME_None, // No bones needed
            GetOwner()->GetActorLocation()
        );
	}
}

auto UGrabber::Release() -> void
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}

auto UGrabber::GetReachLineStart() const -> FVector
{
	/// Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation;
}

auto UGrabber::GetReachLineEnd() const -> FVector
{

	/// Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

// Called every frame
auto UGrabber::TickComponent(const float DeltaTime, const ELevelTick TickType,
                             FActorComponentTickFunction* ThisTickFunction) -> void
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!PhysicsHandle) { return; }
	// If the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object that we're holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
	
}

auto UGrabber::GetFirstPhysicsBodyInReach() const -> FHitResult

{
	/// Line-trace (AKA ray-cast) out to reach distance
	FHitResult HitResult;
	/// Setup query parameters
	const FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECC_PhysicsBody),
		TraceParameters
	);

	/// See what we hit
	const auto ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *(ActorHit->GetName()))
	}
	
	return HitResult;
}
