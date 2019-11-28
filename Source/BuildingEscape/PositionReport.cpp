// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReport.h"
#include "GameFramework/Actor.h"
#include "BuildingEscape.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
auto UPositionReport::BeginPlay() -> void
{
	Super::BeginPlay();
	
	const auto ObjectName = GetOwner()->GetName();
	const auto ObjectPos = GetOwner()->GetTransform().GetLocation().ToString(); // Find transformation of actor by it's location
}


// Called every frame
auto UPositionReport::TickComponent(const float DeltaTime, const ELevelTick TickType,
                                    FActorComponentTickFunction* ThisTickFunction) -> void
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

