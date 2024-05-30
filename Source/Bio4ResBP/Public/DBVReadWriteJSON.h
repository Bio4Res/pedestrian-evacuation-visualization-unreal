// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonReader.h"
#include "Templates/SharedPointer.h"

#include "DBVReadWriteJSON.generated.h"

/**
 * 
 */
UCLASS()
class BIO4RESBP_API UDBVReadWriteJSON : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//UFUNCTION(BlueprintCallable, Category = "DBV") 
	static TSharedPtr<FJsonObject> DBVReadJSON(FString JSonFilePath, bool& bOutSuccess, FString& MessageOut);
	//UFUNCTION(BlueprintCallable, Category = "DBV")
	static void WriteJson(FString JsonFilePath, TSharedPtr <FJsonObject> JSONObject, bool& bOutSucess, FString& MessageOut);



};
