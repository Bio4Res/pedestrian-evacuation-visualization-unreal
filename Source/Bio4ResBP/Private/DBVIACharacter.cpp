// Fill out your copyright notice in the Description page of Project Settings.


#pragma once
#include "DBVIACharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "Components/CapsuleComponent.h"



// Sets default values
ADBVIACharacter::ADBVIACharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADBVIACharacter::BeginPlay()
{
	Super::BeginPlay();
	// scale the character to the 50% of its size
	SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
	
	// modify the z coordinate of the mesh -90.0f to fit in the capsule
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));



	// show log message with the id of the character
	UE_LOG(LogTemp, Warning, TEXT("Character %s"), *GetName());
	// Create a text component
	InitializeTextRenderComponent();
	// make the character visible	
	SetActorHiddenInGame(false);
	// Create PositionToMove array
	PositionsToMove.SetNum(1);
	// cancel collision with other characters
GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);


}


void ADBVIACharacter::SetId(int ID)
{
	// Set the text to display
	TextRenderComponent->SetText(FText::FromString(FString::FromInt(ID)));
}

void ADBVIACharacter::InitializeTextRenderComponent()
{
	// Create a text component
	TextRenderComponent = NewObject<UTextRenderComponent>(this);
	TextRenderComponent->RegisterComponent();
	// Set the text to display
// Create a variable FText and assign the value "ID"

	TextRenderComponent->SetText(FText::FromString("ID"));
	// Set the position of the text
	TextRenderComponent->SetRelativeLocation(FVector(0.0f, 10.0f, 90.0f));
	// Set the rotation of the text 90 degrees in the z axis
	// https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Math/FQuat/RotateVector/
	TextRenderComponent->SetRelativeRotation(FQuat(FRotator(0.0f, 90.0f, 0.0f)));

	// Set the scale of the text
	TextRenderComponent->SetWorldSize(17.0f);
	// Set the color of the text
	TextRenderComponent->SetTextRenderColor(FColor::Black);
	// Attach the text component at the root
	TextRenderComponent->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);


	// Set the text to be visible
	TextRenderComponent->SetVisibility(true);
	// Set the text to be visible in game
	TextRenderComponent->SetHiddenInGame(false);
}

// Called every frame
void ADBVIACharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// show log message with its current position
//UE_LOG(LogTemp, Warning, TEXT("Character %s is at position %s"), *GetName(), *GetActorLocation().ToString());

}

// Called to bind functionality to input
void ADBVIACharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
// Create method to move the character
void ADBVIACharacter::MoveToLocation(FVector Location) {

	// I want to use the method MoveToLocation from the class AAIController
	// I need to cast the controller to AAIController
	AAIController* AIController = Cast<AAIController>(GetController());
	// Calculate distance to the target
	// https://docs.unrealengine.com/5.3/en-US/API/Runtime/Core/Math/FVector/Distance/
	// If distance is less than 100.0f, stop the character
	if (FVector::Distance(GetActorLocation(), Location) > 0.0f) {

		// 
		// I want to use the method MoveToLocation from the class AAIController
		// https://docs.unrealengine.com/5.3/en-US/API/Runtime/AIModule/AAIController/MoveToLocation/ 
		if (AIController) {
			// Orient the character to the location
			FRotator Rotation = (Location - GetActorLocation()).Rotation();
			// Rotate 90 degrees in the z axis (it is a fix to the orientation)
			Rotation.Yaw -= 90.0f;


			// desactivate User Controller Rotation Yaw
			AIController->GetCharacter()->bUseControllerRotationYaw = false;
			// desactivate Orient Rotation To Movement
			AIController->GetCharacter()->GetCharacterMovement()->bOrientRotationToMovement = false;
			// activate Use Controller Desired Rotation
			AIController->GetCharacter()->GetCharacterMovement()->bUseControllerDesiredRotation = true;
			// change rotation rate
			AIController->GetCharacter()->GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 300.0f);
			// set actor rotation
			AIController->GetCharacter()->SetActorRotation(Rotation);

			AIController->MoveToLocation(Location);
			
			

		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Character %s has no AIController"), *GetName());
		}
	}
	else {
		// Show log message saying that the character is close to the target
		UE_LOG(LogTemp, Warning, TEXT("Character %s is close to the target"), *GetName());
	}

	// I want to use the method MoveToLocation from the class AAIController but orienting the character to the target
	// I need to cast the controller to AAIController
	//AAIController* AIController = Cast<AAIController>(GetController());
	// I want to use the method MoveToLocation from the class AAIController orienting the character to the target
	// https://docs.unrealengine.com/5.3/en-US/API/Runtime/AIModule/AAIController/MoveToLocation/
	//if (AIController) {
	//	











}

void ADBVIACharacter::SetPositionsToMove(FVector Position, int Time)
{

	// Check if the position is valid if not, make it valid incrementing the size of the array
	if (PositionsToMove.Num() <= Time) {
		PositionsToMove.SetNum(Time + 1);
	}
	// Add the position to move in the index Time (converted to int)
	PositionsToMove[Time] = Position;

}


void ADBVIACharacter::MoveCharacter(int Time)
{

	// Check if the position is valid if not show a log message and hide the character
	if (PositionsToMove.Num() <= Time) {
		UE_LOG(LogTemp, Warning, TEXT("Character %s has no position to move at time %d"), *GetName(), Time);
		SetActorHiddenInGame(true);
	}
	else {
		// move the character to the position in the index Time (converted to int)
		MoveToLocation(PositionsToMove[Time]);
		SetActorHiddenInGame(false);
	}
}




