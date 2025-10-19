#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/UserDefinedStruct.h"
#include "BlueprintStructJsonLibrary.generated.h"

UCLASS()
class BLUEPRINTSTRUCTJSON_API UBlueprintStructJsonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Blueprint Struct Json", CustomThunk, meta = (CustomStructureParam = "Struct"))
	static bool StructToJson(const UStruct* Struct, FString& OutJsonString);
	static bool Generic_StructToJson(const UStruct* StructDefinition, const void* Struct, FString& OutJsonString);
	DECLARE_FUNCTION(execStructToJson);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Struct Json", CustomThunk, meta = (CustomStructureParam = "OutStruct"))
	static bool JsonToStruct(const FString& JsonString, UStruct*& OutStruct);
	static bool Generic_JsonToStruct(const FString& JsonString, const UStruct* StructDefinition, void* OutStruct);
	DECLARE_FUNCTION(execJsonToStruct);

	UFUNCTION(BlueprintCallable, Category = "Blueprint Struct Json", CustomThunk, meta = (CustomStructureParam = "RowData"))
	static bool ReplaceDataTableRow(UDataTable* DataTable, FName RowName, const UStruct* RowData);
	static bool Generic_ReplaceDataTableRow(UDataTable* DataTable, FName RowName, const UStruct* StructDefinition, const void* RowData);
	DECLARE_FUNCTION(execReplaceDataTableRow);
};