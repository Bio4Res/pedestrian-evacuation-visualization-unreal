// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DBVReadWriteFile.generated.h"

/**
 *
 */
UCLASS()
class BIO4RESBP_API UDBVReadWriteFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "DBV")
	
	static void WriteStringToFile(FString FilePath, FString SaveText, bool& Success);

	UFUNCTION(BlueprintCallable, Category = "DBV")
		static void ReadStringFromFile(FString FilePath, FString& ReadTextOut, bool& SuccessOut);
		
	// Funcion para generar el path del fichero añadiendo el path del proyecto al path relativo
		UFUNCTION(BlueprintCallable, Category = "DBV")
		static FString GetProjectFilePath(FString FileName);

};
