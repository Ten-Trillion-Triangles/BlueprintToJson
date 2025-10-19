# Blueprint Struct Json
An Unreal Engine plugin that enables seamless serialization and deserialization of Blueprint structs to/from JSON format with wildcard pin support.

## Features

- **Wildcard Pin Support**: Use any Blueprint struct type with dynamic wildcard pins
- **Bidirectional Conversion**: Convert structs to JSON and JSON back to structs
- **DataTable Integration**: Replace DataTable rows with struct data
- **Blueprint Native**: Fully accessible from Blueprints without C++ knowledge
- **Type Safety**: Automatic type validation and error handling
- **Performance Optimized**: Uses Unreal's native JSON conversion systems

## Installation

### Option 1: Plugin Installation
1. Copy the `BlueprintStructJson` folder to your project's `Plugins` directory
2. Regenerate project files
3. Build your project
4. Enable the plugin in the Unreal Editor (Edit → Plugins → Utilities → Blueprint Struct Json)

### Option 2: Engine Plugin
1. Copy to your engine's `Engine/Plugins` directory
2. The plugin will be available for all projects

## Usage

### Blueprint Functions

The plugin provides three main Blueprint functions accessible from the **Blueprint Struct Json** category:

#### 1. Struct To Json
```cpp
// Converts any Blueprint struct to JSON string
bool StructToJson(Struct, OutJsonString)
```

**Parameters:**
- `Struct` (Wildcard): Any Blueprint struct to convert
- `OutJsonString` (String): Resulting JSON string

**Returns:** `bool` - Success/failure status

**Example Usage:**
```
MyPlayerData (struct) → Struct To Json → JSON String Output
```

#### 2. Json To Struct  
```cpp
// Converts JSON string back to Blueprint struct
bool JsonToStruct(JsonString, OutStruct)
```

**Parameters:**
- `JsonString` (String): JSON string to parse
- `OutStruct` (Wildcard): Output struct (must match JSON structure)

**Returns:** `bool` - Success/failure status

**Example Usage:**
```
JSON String → Json To Struct → MyPlayerData (struct)
```

#### 3. Replace DataTable Row
```cpp
// Replaces a DataTable row with struct data
bool ReplaceDataTableRow(DataTable, RowName, RowData)
```

**Parameters:**
- `DataTable` (DataTable): Target DataTable to modify
- `RowName` (Name): Name of the row to replace
- `RowData` (Wildcard): Struct data to insert

**Returns:** `bool` - Success/failure status

## Examples

### Basic Struct Serialization

<img width="806" height="316" alt="image" src="https://github.com/user-attachments/assets/db5fdba9-4337-45f8-a953-4777f5df504a" />


1. **Create a Blueprint Struct** (e.g., `PlayerData`):
   ```
   PlayerData:
   - Name (String)
   - Level (Integer)
   - Health (Float)
   - Position (Vector)
   ```

2. **Convert to JSON**:
   ```
   PlayerData Instance → Struct To Json → JSON Output
   ```
   
   Result:
   ```json
   {
     "Name": "Player1",
     "Level": 25,
     "Health": 100.0,
     "Position": {"X": 10.0, "Y": 20.0, "Z": 30.0}
   }
   ```

3. **Convert back from JSON**:
   ```
   JSON String → Json To Struct → PlayerData Instance
   ```

### DataTable Integration

```
1. Create DataTable with struct type
2. Use Replace DataTable Row to update entries
3. Struct data automatically validates against table schema
```

### Save/Load System Example

```
Save Game:
Player Data → Struct To Json → Save to File

Load Game:
Load from File → Json To Struct → Player Data
```

## Technical Details


### Supported Types

The plugin supports all standard Unreal Engine types:
- **Primitives**: bool, int32, float, FString, FName
- **Math Types**: FVector, FRotator, FTransform, FColor, etc.
- **Engine Types**: UObject references, TSoftObjectPtr, etc.
- **Containers**: TArray, TMap, TSet (with supported element types)
- **Nested Structs**: Full support for complex nested structures

### Error Handling

- Returns `false` for invalid operations
- Validates struct definitions at runtime
- Handles malformed JSON gracefully
- Logs warnings for debugging

## Building from Source

### Prerequisites
- Unreal Engine 4.25+ or 5.x
- Visual Studio 2019+ (Windows) or Xcode (macOS)

### Dependencies
- **Core**: Unreal Engine core systems
- **CoreUObject**: UObject system
- **Engine**: Engine functionality
- **Json**: JSON parsing and generation
- **JsonUtilities**: High-level JSON conversion utilities

### Build Steps
```bash
# Generate project files
./GenerateProjectFiles.sh  # Linux/Mac
# or
GenerateProjectFiles.bat   # Windows

# Build project (plugin builds automatically)
```
