# MiniProjet

MiniProjet university project (2nd year) for algorithms, it is a C++ console application that generates and analyzes a parcel map. Each parcel belongs to one of four land-use types, and the program lets the user display the map, extract connected objects, extract full themes, and calculate statistics.

The application is written in C++ and built with Visual Studio.

## Preview

![Application startup](<assets/screenshots/Screenshot 2026-06-05 220021.png>)

## Land-Use Types

| Number | Type |
| --- | --- |
| `1` | Agricole |
| `2` | Habitation |
| `3` | Forets |
| `4` | Industrielle |

## Features

### 1. Create a Map

Generates a new square map using random parcel types. The map is displayed directly after creation.

Menu option:

```text
1- Cree une carte.
```

![Create map](<assets/screenshots/Screenshot 2026-06-05 220043.png>)

### 2. Display the Current Map

Prints the current generated map in the console. Each number represents the nature/type of a parcel.

Menu option:

```text
2- Afficher la carte
```

![Display map](<assets/screenshots/Screenshot 2026-06-05 220043.png>)

### 3. Extract and Display an Object

Extracts an object starting from a selected parcel position. An object is a connected group of parcels that share the same nature.

Menu option:

```text
3- Extraire et afficher un objet
```

Example input:

```text
x = 1
y = 2
```

![Extract object](<assets/screenshots/Screenshot 2026-06-05 220054.png>)

### 4. Extract and Display a Theme

Extracts all parcels that belong to a selected land-use type, then displays only that theme.

Menu option:

```text
4- Extraire et afficher un theme
```

Example input:

```text
Donner une nature a extraire (entre 1 et 4) : 2
```

![Extract theme](<assets/screenshots/Screenshot 2026-06-05 220115.png>)

### 5. Display Statistics

Displays the number of parcels for each type, the percentage of the total surface, and a simple console progress bar.

Menu option:

```text
5- Afficher des statistiques
```

![Statistics](<assets/screenshots/Screenshot 2026-06-05 220238.png>)

## Project Structure

```text
MiniProjet/
├── MiniProjet.cpp          # Visual Studio entry source file
├── mainFunctions.cpp       # Main application logic and console interface
├── mainFunctions.h         # Header file
├── MiniProjet.sln          # Visual Studio solution
├── MiniProjet.vcxproj      # Visual Studio C++ project
└── assets/screenshots/     # README screenshots
```

## Requirements

- Windows
- Visual Studio with C++ build tools
- MSVC toolset `v143`
- Windows SDK 10.0 or newer

## Build and Run

### Option 1: Visual Studio

1. Open `MiniProjet.sln`.
2. Select `Debug` and `x64`.
3. Start the project with `Local Windows Debugger`.

### Option 2: Command Line

Build the solution:

```powershell
msbuild MiniProjet.sln /p:Configuration=Debug /p:Platform=x64
```

Run the executable:

```powershell
.\x64\Debug\MiniProjet.exe
```

## Usage

When the program starts, enter the size of the map:

```text
Donner la taille de la carte : 5
```

Then choose an action from the menu:

```text
1- Cree une carte.
2- Afficher la carte
3- Extraire et afficher un objet
4- Extraire et afficher un theme
5- Afficher des statistiques
0- Sortire de l'application
```

![Main menu](<assets/screenshots/Screenshot 2026-06-05 220031.png>)

Enter `0` to exit the program.

## Notes

- The program uses console colors to make map types easier to distinguish.
- The generated map is square, so the same value is used for both width and height.
- Statistics are calculated from the total number of parcels in the map.
