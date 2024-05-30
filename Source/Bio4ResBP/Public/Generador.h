// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"
#include "DBVPositionStr.h"
#include "DBVIACharacter.h"
#include "Generador.generated.h"

UCLASS()
class BIO4RESBP_API AGenerador : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGenerador();
	// Function to spawn the actors this is going to be used to test the characters
	UFUNCTION(BlueprintCallable, Category = "DBV")
	void SpawnActors();
	// Function to spawn one actor will receive an id of the character to spawn and the position
	// it will be save in the array SpawnedCharacters
	UFUNCTION(BlueprintCallable, Category = "DBV")
	void SpawnActor(int id, FVector Position);

	//  Function to spawn scene components
	UFUNCTION(BlueprintCallable, Category = "DBV")
	void SpawnSceneComponents();
	// Function to read the simulation file
	UFUNCTION(BlueprintCallable, Category = "DBV")
	void ReadSimulationFile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void MoveCharacters();

	// Array of actors to spawn
	UPROPERTY(EditAnywhere, Category = "DBV|Scene")
	TSubclassOf<AActor> WhatToSpawn;
	// Create a type struct that contains information about coordinates x and y 
	// and width and height for the Actors to spawn	

	// skeletal mesh to spawn
	UPROPERTY(EditAnywhere, Category = "DBV|Character")
	USkeletalMesh* SkeletalMeshToSpawn;
	// Add the animation blueprint to the skeletal mesh
	UPROPERTY(EditAnywhere, Category = "DBV|Character")
	UClass* AnimBlueprintToSpawn;
	// Add time to move characters
	UPROPERTY(EditAnywhere, Category = "DBV|Simulation")
	float TimeToMoveCharacters = 5.0f;
	// Add time to move characters
	UPROPERTY(EditAnywhere, Category = "DBV|Simulation")
	float InitialTime = 0.0f;
	// Add simulation time
	UPROPERTY(EditAnywhere, Category = "DBV|Simulation")
	int CurrentSimulationTime = 0;
	// method to read the CurrentSimulationTime
	UFUNCTION(BlueprintCallable, Category = "DBV|Simulation")
	int GetCurrentSimulationTime();
	// Add variable to store the max simulation time
	UPROPERTY(EditAnywhere, Category = "DBV|Simulation")
	int MaxSimulationTime = 0;
	// Method to read the MaxSimulationTime
	UFUNCTION(BlueprintCallable, Category = "DBV|Simulation")
	int GetMaxSimulationTime();

	// Add property for CellDimension
	UPROPERTY(EditAnywhere, Category = "DBV|Scene")
	float CellDimension = 100.0f;

	// Add property SimulationCellDimension
	UPROPERTY(EditAnywhere, Category = "DBV|Simulation")
	float SimulationCellDimension = 100.0f;


	// Add boolean SimulationStarted initialized in false
	UPROPERTY(EditAnywhere, Category = "DBV|Simulation")
	bool SimulationStarted = false;
	// Add function to start the simulation
	UFUNCTION(BlueprintCallable, Category = "DBV|Simulation")
	void StartSimulation();
	// Add function to stop the simulation
	UFUNCTION(BlueprintCallable, Category = "DBV|Simulation")
	void StopSimulation();


	// Array of actors to spawn this dont need to be editable
	UPROPERTY(EditAnywhere, Category = "DBV|Scene")
	TArray<ADBVIACharacter*> SpawnedCharacters;

	// add a location to go
	UPROPERTY(EditAnywhere, Category = "DBV|Character")
	FVector LocationToGo = FVector(0.0f, 0.0f, 0.0f);







	// Array of spawn points for the characters
	UPROPERTY(EditAnywhere, Category = "DBV|Character")
	TArray<FVector> CharactersSpawnPoints;

	// Array of DBVPositionStr to spawn
	UPROPERTY(EditAnywhere, Category = "DBV|Scene")
	TArray<FDBVPositionStr> DBVPositionStr;


	// Array of locations to spawn
	UPROPERTY(EditAnywhere, Category = "DBV|Scene")
	TArray<FVector> SpawnPoints;

	// Direction of the file to read
	// The format must be Content/DBV/JSON/Obstacles.csv
	// because in DBVReadWriteFile.cpp we use the method GetProjectFilePath
	// to get the full path of the file
	UPROPERTY(EditAnywhere, Category = "DBV|Scene")
	FString CSVFilePath = "Content/DBV/JSON/Obstacles.csv"; 
	// The file path of the simulation file with the trace of positions for the characters
	UPROPERTY(EditAnywhere, Category = "DBV|Simulation")
	FString SimulationFilePath = "Content/DBV/JSON/simulation.csv";
};
