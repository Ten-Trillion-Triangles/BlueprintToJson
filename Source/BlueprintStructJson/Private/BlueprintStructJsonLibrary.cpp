#include "BlueprintStructJsonLibrary.h"
#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "UObject/UnrealType.h"
#include "Engine/DataTable.h"

bool UBlueprintStructJsonLibrary::StructToJson(const UStruct* Struct, FString& OutJsonString)
{
	check(0);
	return false;
}

bool UBlueprintStructJsonLibrary::Generic_StructToJson(const UStruct* StructDefinition, const void* Struct, FString& OutJsonString)
{
	if (!StructDefinition || !Struct)
	{
		return false;
	}

	return FJsonObjectConverter::UStructToJsonObjectString(StructDefinition, Struct, OutJsonString, 0, 0);
}

DEFINE_FUNCTION(UBlueprintStructJsonLibrary::execStructToJson)
{
	Stack.StepCompiledIn<FStructProperty>(NULL);
	void* InStruct = Stack.MostRecentPropertyAddress;
	FStructProperty* StructProp = CastField<FStructProperty>(Stack.MostRecentProperty);

	P_GET_PROPERTY_REF(FStrProperty, OutJsonString);
	P_FINISH;

	bool bSuccess = false;
	if (StructProp && InStruct)
	{
		P_NATIVE_BEGIN;
		bSuccess = Generic_StructToJson(StructProp->Struct, InStruct, OutJsonString);
		P_NATIVE_END;
	}
	*(bool*)RESULT_PARAM = bSuccess;
}

bool UBlueprintStructJsonLibrary::JsonToStruct(const FString& JsonString, UStruct*& OutStruct)
{
	check(0);
	return false;
}

bool UBlueprintStructJsonLibrary::Generic_JsonToStruct(const FString& JsonString, const UStruct* StructDefinition, void* OutStruct)
{
	if (JsonString.IsEmpty() || !StructDefinition || !OutStruct)
	{
		return false;
	}

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonString);
	if (!FJsonSerializer::Deserialize(JsonReader, JsonObject) || !JsonObject.IsValid())
	{
		return false;
	}

	return FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), StructDefinition, OutStruct, 0, 0);
}

DEFINE_FUNCTION(UBlueprintStructJsonLibrary::execJsonToStruct)
{
	P_GET_PROPERTY(FStrProperty, JsonString);

	Stack.StepCompiledIn<FStructProperty>(NULL);
	void* OutStruct = Stack.MostRecentPropertyAddress;
	FStructProperty* StructProp = CastField<FStructProperty>(Stack.MostRecentProperty);

	P_FINISH;

	bool bSuccess = false;
	if (StructProp && OutStruct)
	{
		P_NATIVE_BEGIN;
		bSuccess = Generic_JsonToStruct(JsonString, StructProp->Struct, OutStruct);
		P_NATIVE_END;
	}
	*(bool*)RESULT_PARAM = bSuccess;
}

bool UBlueprintStructJsonLibrary::ReplaceDataTableRow(UDataTable* DataTable, FName RowName, const UStruct* RowData)
{
	check(0);
	return false;
}

bool UBlueprintStructJsonLibrary::Generic_ReplaceDataTableRow(UDataTable* DataTable, FName RowName, const UStruct* StructDefinition, const void* RowData)
{
	if (!DataTable || !StructDefinition || !RowData || RowName.IsNone())
	{
		return false;
	}

	if (DataTable->GetRowStruct() != StructDefinition)
	{
		return false;
	}

	DataTable->AddRow(RowName, static_cast<const uint8*>(RowData), static_cast<const UScriptStruct*>(StructDefinition));
	return true;
}

DEFINE_FUNCTION(UBlueprintStructJsonLibrary::execReplaceDataTableRow)
{
	P_GET_OBJECT(UDataTable, DataTable);
	P_GET_PROPERTY(FNameProperty, RowName);

	Stack.StepCompiledIn<FStructProperty>(NULL);
	void* RowData = Stack.MostRecentPropertyAddress;
	FStructProperty* StructProp = CastField<FStructProperty>(Stack.MostRecentProperty);

	P_FINISH;

	bool bSuccess = false;
	if (StructProp && RowData)
	{
		P_NATIVE_BEGIN;
		bSuccess = Generic_ReplaceDataTableRow(DataTable, RowName, StructProp->Struct, RowData);
		P_NATIVE_END;
	}
	*(bool*)RESULT_PARAM = bSuccess;
}