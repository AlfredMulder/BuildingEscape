// Copyright John Doe.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor final : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	auto BeginPlay() -> void override;

public:
	// Called every frame
	auto TickComponent(float DeltaTime, ELevelTick TickType,
	                   FActorComponentTickFunction* ThisTickFunction) -> void override;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnOpen;

	UPROPERTY(BlueprintAssignable)
	FDoorEvent OnClose;

private:
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	// The owning door.
	AActor* Owner = nullptr;

	float TriggerMass = 90.f;
	
	// Returns total mss in kg
	auto GetTotalMassOfActorsOnPlate() const -> float;
};
