// Fill out your copyright notice in the Description page of Project Settings.

#include "Generador.h"
#include "DBVReadWriteFile.h"
#include "Misc/FileHelper.h"
#include "Containers/UnrealString.h"



// Sets default values
AGenerador::AGenerador()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
// Function to spawn the actors (characters) that are going to be controlled byt
// the simulation file.
// The character are included in the arra of SpawnedCharacters
void AGenerador::SpawnActors()
{
	// Create an array of spawn actors with the same size of the array CharactersSpawnPoints
	SpawnedCharacters.SetNum(CharactersSpawnPoints.Num());


	// for each element in the array CharactersSpawnPoints, spawn a character and associate the skeletal mesh and the animation
	for (int i = 0; i < CharactersSpawnPoints.Num(); i++) {
		// spawn the actor calling the function SpawnActor
		SpawnActor(i, CharactersSpawnPoints[i]);
	}
}

void AGenerador::SpawnActor(int id, FVector Position)
{
	// Modify the size of the array if the id is greater than the size of the array
	// This prevent the array to be out of bounds
	if (id >= SpawnedCharacters.Num()) {
		SpawnedCharacters.SetNum(id + 1);

	}

	// try to spawn the actor and catch the exception if the actor is not spawned
	//try {
		// Create here all the code to spawn the actor included previously in the function SpawnActors
		SpawnedCharacters[id] = GetWorld()->SpawnActor<ADBVIACharacter>(ADBVIACharacter::StaticClass(), Position, FRotator::ZeroRotator);
		if (SpawnedCharacters[id]==nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("AGenerador::SpawnActor is null SpawnedCharacters[%d] is NOT loaded"), id);
			
		}
		else {


			// asociate the skeletal mesh to SKM_Manny
				// show if the skeletal mesh is loaded
			if (SkeletalMeshToSpawn) {
				UE_LOG(LogTemp, Warning, TEXT("AGenerador::BeginPlay SkeletalMeshToSpawn is loaded"));
				SpawnedCharacters[id]->GetMesh()->SetSkeletalMesh(SkeletalMeshToSpawn);
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("AGenerador::BeginPlay SkeletalMeshToSpawn is NOT loaded"));
			}
			// change the skeletal mesh of the spawned actor
			// SpawnedCharacter->GetMesh()->SetSkeletalMesh(SkeletalMeshToSpawn);
			// change the animation of the spawned actor
			//SpawnedCharacters[i]->GetMesh()->SetAnimationMode(EAnimationMode::AnimationSingleNode);
			SpawnedCharacters[id]->GetMesh()->SetAnimationMode(EAnimationMode::AnimationCustomMode);
			SpawnedCharacters[id]->GetMesh()->SetAnimInstanceClass(AnimBlueprintToSpawn);
			// set ai controller
			SpawnedCharacters[id]->SpawnDefaultController();
			// set the id of the character
			SpawnedCharacters[id]->SetId(id);
		}
		/*
	}
	catch (...) {
		// Show a message in the output log if the actor is not spawned
		UE_LOG(LogTemp, Warning, TEXT("AGenerador::SpawnActor::No se pudo spawnear el actor %d"), id);
	}*/


	



}

// Function to spawn the scene components that are located in the file CSVFilePath
// This will be done only once at the beginning of the simulation
void AGenerador::SpawnSceneComponents()
{
	// recorrer array de ubicaciones para hacer spawn
	for (int i = 0; i < SpawnPoints.Num(); i++)
	{
		// spawn actor
		GetWorld()->SpawnActor<AActor>(WhatToSpawn, SpawnPoints[i], FRotator::ZeroRotator);
	}

	// Leemos un archivo .csv con las coordenadas

	FString CSVFileContent;
	FString MessageOut;
	bool bOutSuccess = false;
	// Read CSV file using ReadStringFromFile function
	UDBVReadWriteFile::ReadStringFromFile(CSVFilePath, CSVFileContent, bOutSuccess);
	// If the file is read correctly
	if (bOutSuccess) {
		// cell dimension is 0,25x0,25. We set it to 25
		// Set the cell dimension to 25
		//float CellDimension = 100;
		
		// Log reporting that the file was opened
		UE_LOG(LogTemp, Warning, TEXT("AGenerador::BeginPlay Se abrio el fichero: %s"), &CSVFilePath);
		// Split the CSVFilePath content into an array of strings
		TArray<FString> LinesOfFile;
		// For each line readed in DBVPositionStr we create a new string
		CSVFileContent.ParseIntoArray(LinesOfFile, TEXT("\n"));
		// In each line we find 4 values separated by commas 
	   // The first value is the coordinate X of the actor to spawn
	   // The second value is the coordinate Y of the actor to spawn
	   // The third value is the width of the actor to spawn
	   // The fourth value is the height of the actor to spawn
		TArray<FString> elem;
		for (int i = 0; i < LinesOfFile.Num(); i++) {
			LinesOfFile[i].ParseIntoArray(elem, TEXT(","));
			// Convert the string to float
			float X = FCString::Atof(*elem[0]) * CellDimension;
			float Y = FCString::Atof(*elem[1]) * CellDimension;
			float Width = FCString::Atof(*elem[2]);
			float Height = FCString::Atof(*elem[3]);
			// Show values y in the output log
			UE_LOG(LogTemp, Warning, TEXT("X: %f, Y: %f, Width: %f, Height: %f"), X, Y, Width, Height);
			
			// Sqpawn the actor to the position X and Y
			// We are going to spawn the actor in the position X and Y  (Y is Unreal - Y in Java thats why we multiply by -1 when spawn)
			AActor* coord = GetWorld()->SpawnActor<AActor>(WhatToSpawn, FVector(X+(Width-1)*CellDimension/2,-( Y+(Height-1)*CellDimension/2), 0), FRotator::ZeroRotator);
			// Then resize the actor to the width and height
			coord->SetActorScale3D(FVector(Width, Height, 1));
			/*
			//Spawn	the actor
			for (int j = 0; j < Width; j++) {
				for (int k = 0; k < Height; k++) {
					AActor *coord=GetWorld()->SpawnActor<AActor>(WhatToSpawn, FVector(X + j * CellDimension, Y + k * CellDimension, 0), FRotator::ZeroRotator);
					// we resize the coord to the CellDimension
					//coord->SetActorScale3D(FVector(0.25, 0.25, 0.25));
					

				}
			}
			*/
		}
		// llamar a UDBVReadWriteFile::GetProjectFilePath para obtener la ruta completa del fichero y asignarla a FullFilePath
		//FString FullFilePath = UDBVReadWriteFile::GetProjectFilePath(CSVFilePath);


        
	}
	else {
		// Log reporting that the file couldn't be opened
		UE_LOG(LogTemp, Warning, TEXT("AGenerador::SpawnSceneComponents::No se pudo abrir el fichero: %s "), *CSVFilePath);

	}

}

void AGenerador::ReadSimulationFile()
{
	// The simulation file has the following format with two different types of lines
	// The lines with only one number represent the time elapsed. We call this type of line TimeLine: 0.0 
	// The other lines represent the id of the character and the position x and y. We call this typeof line CharPosLine: 1,46,17
	// The file is located in the path SimulationFilePath
	// We are going to use the method ReadStringFromFile from the class UDBVReadWriteFile to read each line of the file
	// Declare variables to store the content of the file and the success of the operation
	FString SimulationFileContent;
	// Create local variable to store the current time initialized to 0
	int CurrentTime = 0;
	bool bOutSuccess = false;
	// show message in console saying loading file started and showing the current hour, minutes and seconds
	UE_LOG(LogTemp, Warning, TEXT("AGenerador::ReadSimulationFile::Loading file started at %s"), *FDateTime::Now().ToString());
	
	// Read the file using the method ReadStringFromFile
	UDBVReadWriteFile::ReadStringFromFile(SimulationFilePath, SimulationFileContent, bOutSuccess);
	// If the file is read correctly
	if (bOutSuccess) {
		// Log reporting that the file was opened
		UE_LOG(LogTemp, Warning, TEXT("AGenerador::ReadSimulationFile Se abrio el fichero: %s"), *SimulationFilePath);
		// Split the SimulationFileContent into an array of strings
		TArray<FString> LinesOfFile;
		SimulationFileContent.ParseIntoArray(LinesOfFile, TEXT("\n"));
		// For each line in the file
		for (int i = 0; i < LinesOfFile.Num(); i++) {
			// Split the line into an array of strings
			TArray<FString> elem;
			LinesOfFile[i].ParseIntoArray(elem, TEXT(","));
			// If the line is a TimeLine
			if (elem.Num() == 1) {
				// Show the time in the output log
				UE_LOG(LogTemp, Warning, TEXT("Time: %s"), *LinesOfFile[i]);
				// update the current time to this value
				CurrentTime = FCString::Atoi(*LinesOfFile[i]);
				// if the current time is greater than the max simulation time then update the max simulation time
				if (CurrentTime > MaxSimulationTime) {
					MaxSimulationTime = CurrentTime;
				}
			}
			else {
				// If the line is a CharPosLine
				
				// Convert the string to int
				int id = FCString::Atoi(*elem[0]);
				float X = FCString::Atof(*elem[1])*SimulationCellDimension;
				float Y = FCString::Atof(*elem[2])*(-SimulationCellDimension);
				// Show the id and the position in the output log
				UE_LOG(LogTemp, Warning, TEXT("id: %d, X: %f, Y: %f"), id, X, Y);
				// check if the id is a position valid in the array of characters
				// if not , make it valid incrementing the size of the array
				if (id >= SpawnedCharacters.Num()) {
					SpawnedCharacters.SetNum(id + 1);
				}
				// if the character is null then spawn the character
				if (SpawnedCharacters[id] == nullptr) {
					SpawnActor(id, FVector(X, Y, 0));
				}				
				// Create a position and add it to the array of positions of the character in the current time
				// It is possible that the charecter is not spawned yet because there is a collision with another character 
				// or with the scene components
				if (SpawnedCharacters[id])
				{
				 SpawnedCharacters[id]->SetPositionsToMove(FVector(X, Y, 0), CurrentTime);
				}
				


			}
		}
	}
	else {
		// Log reporting that the file couldn't be opened
		UE_LOG(LogTemp, Warning, TEXT("AGenerador::ReadSimulationFile::No se pudo abrir el fichero: %s "), *SimulationFilePath);
	}
	
	// show message in console saying loading file started and showing the current hour, minutes and seconds
	UE_LOG(LogTemp, Warning, TEXT("AGenerador::ReadSimulationFile::Loading file finished at %s"), *FDateTime::Now().ToString());


}

// Called when the game starts or when spawned
void AGenerador::BeginPlay()
{
	// i want to spawn two DBVIACharacter in the same location
	// GetWorld()->SpawnActor<ADBVICharacter>(WhatToSpawn, FVector(0, 0, 0), FRotator::ZeroRotator);
	Super::BeginPlay();

	// Create array SpawnedCharacters
	SpawnedCharacters.SetNum(CharactersSpawnPoints.Num());

	//SpawnActors();

	SpawnSceneComponents();

	ReadSimulationFile();


}

// Called every frame
void AGenerador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (SimulationStarted) {
		// show delta time minus initial time
		//UE_LOG(LogTemp, Warning, TEXT("AGenerador::Tick DeltaTime: %f"), InitialTime);
		if (DeltaTime + InitialTime > TimeToMoveCharacters) {
			InitialTime = 0;
			CurrentSimulationTime++;
			// show message time to move characters
			UE_LOG(LogTemp, Warning, TEXT("AGenerador::Tick Time to move characters"));
			MoveCharacters();
		}
		else {
			InitialTime += DeltaTime;
		}
	}
	// if delta time is greater than time to move characters




}
void AGenerador::MoveCharacters() {

		
	// 
	// for each character in the array of characters
	for (int i = 0; i < SpawnedCharacters.Num(); i++) {
		// modify location to go to a random location X and Y with a range of 2000	
		LocationToGo.X = FMath::RandRange(0, 2000);
		LocationToGo.Y = FMath::RandRange(0, 2000);
		// move the character to the next random position with a range of 100 in x and y over the current position
//SpawnedCharacters[i]->MoveToLocation(FVector(SpawnedCharacters[i]->GetActorLocation().X + FMath::RandRange(0, 100), SpawnedCharacters[i]->GetActorLocation().Y + FMath::RandRange(0, 500), SpawnedCharacters[i]->GetActorLocation().Z));
		//SpawnedCharacters[i]->MoveToLocation(LocationToGo); // I don't know why this doesn't work

		// We must always check that the character is not null before moving it
		// Sometimes the character is not spawned yet because there is a collision with another character or with the scene components
		if (SpawnedCharacters[i]) {
			// Move the character to the next position
			SpawnedCharacters[i]->MoveCharacter(CurrentSimulationTime);
		}
	}
}
void AGenerador::StartSimulation() {
	// show message simulation started
	UE_LOG(LogTemp, Warning, TEXT("AGenerador::StartSimulation Simulation started"));
	// set the boolean SimulationStarted to true
	SimulationStarted = true;
}
void AGenerador::StopSimulation() {
	// show message simulation stopped
	UE_LOG(LogTemp, Warning, TEXT("AGenerador::StopSimulation Simulation stopped"));
	// set the boolean SimulationStarted to false
	SimulationStarted = false;
}
int AGenerador::GetCurrentSimulationTime() {
	// return the current simulation time
	return CurrentSimulationTime;
}
int AGenerador::GetMaxSimulationTime() {
	// return the max simulation time
	return MaxSimulationTime;
}
