#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Containers/Array.h"
#include "DBVPositionStr.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct BIO4RESBP_API FDBVPositionStr
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DBV")
		int32 X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DBV")
		int32 Y;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DBV")
		int32 Width;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DBV")
		int32 Height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DBV")
		int32 ActorNumber;
};
