// Fill out your copyright notice in the Description page of Project Settings.


#include "DBVReadWriteFile.h"
#include "HAL/PlatformFileManager.h"

// Comenta los parámetros
// FilePath: ruta del fichero
// FileName: nombre del fichero
// SaveText: texto a guardar en el fichero
// Success: true si se ha guardado correctamente, false en caso contrario


/**
* @param FilePath: ruta del fichero incluye el nombre del fichero
* @param SaveText: texto a guardar en el fichero
* @param Success: true si se ha guardado correctamente, false en caso contrario
* 
*/

void UDBVReadWriteFile::WriteStringToFile(FString FilePath, FString SaveText, bool& Success)
{
	Success = false;
	if (FFileHelper::SaveStringToFile(SaveText, *FilePath)) {
		Success = true;
		// Mostramos en la consola que se ha escrito correctamente y el nombre del fichero
		UE_LOG(LogTemp,Warning,TEXT("Fichero escrito correctamente %s"),*FilePath);
	}
	else {
		//	Mostramos en la consola que no se ha podido escribir en el fichero
		UE_LOG(LogTemp, Warning, TEXT("No se ha podido escribir %s"), *FilePath);
	}
}



/**
* @param FilePath: ruta relativa del fichero ejemplo: Content/DBV/JSON/Obstacles.csv
* @param ReadTextOut: texto leido del fichero
* @param SuccessOut: true si se ha leido correctamente, false en caso contrario
*/
void UDBVReadWriteFile::ReadStringFromFile(FString FilePath, FString& ReadTextOut, bool &SuccessOut)
{
	SuccessOut = false;
	UE_LOG(LogTemp, Warning, TEXT("UDBVReadWriteFile::ReadStringFromFile: Iniciando lectura"));
	// Create variable to store the full path of the file using the method GetProjectFilePath
	FilePath = GetProjectFilePath(FilePath);
	
	// Comprobar si el fichero existe
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath)){
		ReadTextOut = "";
		// intentamos leer el archivo en la cadena ReadTextOut	
		if (FFileHelper::LoadFileToString(ReadTextOut, *FilePath)) {
			SuccessOut = true;
				UE_LOG(LogTemp,Warning,TEXT("UDBVReadWriteFile::ReadStringFromFile Fichero leido correctamente %s. El contenido del fichero es:"),*FilePath);
				UE_LOG(LogTemp, Display, TEXT("%s"), *ReadTextOut);

		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("UDBVReadWriteFile::ReadStringFromFile No se ha podido leer %s"), *FilePath);
		}
			
		

	} else {
		// informar en log de que el fichero no existe
		UE_LOG(LogTemp, Warning, TEXT("UDBVReadWriteFile::ReadStringFromFile Fichero no encontrado %s"), *FilePath);
		
		
	}
	
		
		
		
}
/**
* @param FileName: Name of the parcial path of the file example: Content/DBV/JSON/Obstacles.csv
* @return FullPath: Full path of the file example: D:/Programacion/Unreal/Bio4ResBP/Content/DBV/JSON/Obstacles.csv
*/
FString UDBVReadWriteFile::GetProjectFilePath(FString FileName)
{
	// Get the base directory of the game
	FString BaseDir = FPaths::ProjectDir();
	// Convert to full path
	FString FullPath = FPaths::ConvertRelativePathToFull(BaseDir);
	// Add the filename 
	FullPath.Append(FileName);
	
	
	// show in console the full path
	//UE_LOG(LogTemp, Warning, TEXT("UDBVReadWriteFile::GetProjectFilePath: FullPath: %s"), *FullPath);
	// 
	// Return the full path
	return FullPath;
	}
