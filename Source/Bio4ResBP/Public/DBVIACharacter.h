// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TextRenderComponent.h"
#include "DBVIACharacter.generated.h"

UCLASS()
class BIO4RESBP_API ADBVIACharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADBVIACharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

	


	// Variable that contains the list of positions to move the character
	// where the index represent the time to move the character
	UPROPERTY(EditAnywhere, Category = "DBV|Character")
	TArray<FVector> PositionsToMove;

	// Add a variable for a text render component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DBV|Character")
	class UTextRenderComponent* TextRenderComponent;
	
	// Add method to initialize the text render component
	UFUNCTION(BlueprintCallable, Category = "DBV|Character")
	void InitializeTextRenderComponent();





public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Set ID
	UFUNCTION(BlueprintCallable, Category = "DBV|Character")
	void SetId(int ID);

	// Create method to move the character
	// This method will be called from the blueprint
	UFUNCTION(BlueprintCallable, Category = "DBV")
	void MoveToLocation(FVector Location);
	// Method to set the positions to move the character that receive a position and a time
	UFUNCTION(BlueprintCallable, Category = "DBV")
	void SetPositionsToMove(FVector Position, int Time);
	// Method to move the character to the position that receive a time
	UFUNCTION(BlueprintCallable, Category = "DBV")
	void MoveCharacter(int Time);


};
