// Copyright John Doe.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/EngineTypes.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber final : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	auto BeginPlay() -> void override;

public:
	// Called every frame
	auto TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) -> void
	override;

private:
	// How far ahead of the player can we reach in cm
	float Reach = 100.f;
	
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	UInputComponent* InputComponent = nullptr;

	// Ray-cast and grab what's in reach
	auto Grab() -> void;

	// Called when grab is released
	auto Release() -> void;

	// Returns current end of reach line
	auto GetReachLineEnd() const -> FVector;

	// Returns current start of reach line
	auto GetReachLineStart() const -> FVector;

	// Find attached physics handle
	auto FindPhysicsHandleComponent() -> void;

	// Setup (assumed) attached input component
	auto SetupInputComponent() -> void;

	// Return hit for first physics body in reach
	auto GetFirstPhysicsBodyInReach() const -> FHitResult;
};
