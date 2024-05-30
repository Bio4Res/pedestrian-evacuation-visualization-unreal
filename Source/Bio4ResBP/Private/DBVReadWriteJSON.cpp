// Fill out your copyright notice in the Description page of Project Settings.


#include "DBVReadWriteJSON.h"
#include "DBVReadWriteFile.h"

 TSharedPtr<FJsonObject> UDBVReadWriteJSON::DBVReadJSON(FString JSonFilePath, bool& bOutSuccess, FString& MessageOut) {
	TSharedPtr<FJsonObject> Res = nullptr;
	FString ReadTextOut;
	
	UDBVReadWriteFile::ReadStringFromFile(JSonFilePath, ReadTextOut, bOutSuccess);

	// Si no se lee correctamente
	if (bOutSuccess) {
		
		// Para convertir la cadena a json se utiliza Deserialize
		if (FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(ReadTextOut), Res)) {
			bOutSuccess = true;
			MessageOut = "Cadena convertida a json";
			

		}
		else {
			bOutSuccess = false;
			MessageOut = "Error al convertir la cadena a json";
		}
	}
	return Res;
	
}
 void WriteJson(FString JsonFilePath, TSharedPtr <FJsonObject> JSONObject, bool& bOutSuccess, FString& MessageOut) {
	FString JSONString;
	if (FJsonSerializer::Serialize(JSONObject.ToSharedRef(), TJsonWriterFactory<>::Create(&JSONString,0))) {
		bOutSuccess = true;
		MessageOut = "Json convertido a cadena";
		UDBVReadWriteFile::WriteStringToFile(JsonFilePath, JSONString, bOutSuccess);
	}
	else {
		bOutSuccess = false;
		MessageOut = "Error al convertir el json a cadena";
	}
}
