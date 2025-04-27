# HalfswordAnalyzer

**HalfswordAnalyzer** is a custom map handler for the game [**Halfsword**](https://store.steampowered.com/app/2585370/Halfsword/), enabling **custom map loading** during gameplay via a single `GameObject` spawned with `SpawnActor`.  
The system tracks all available custom maps and provides a simple **ImGui** interface to select and load them.

> Current Game Version Info (as of April 28, 2025):  
> **AES Key for .pak decryption:**  
> `0xBCBF7B45A4A8150D06F7B955BC25EF5CE603470F508302CAD0EB48FEA2D91517`

---

## Features

- 🔹 **Custom Map Loading**: Load custom maps.
- 🔹 **Single Actor Management**: A `SpawnActor` instance manages all map references.
- 🔹 **ImGui Integration**: Select and load maps with an in-game menu.
- 🔹 **Custom Map Support**: Easily add new maps by dropping definition files into the designated folder.

---

## How It Works

- A **custom `.pak` file** provides a **GameObject** tailored for HalfswordAnalyzer.
- This GameObject **references a specific folder** inside the game's Content directory where **map definition assets** are placed.
- Upon being spawned, the object **scans that folder** for assets of type `Level`, and **registers them** for loading through the ImGui menu.
- A **custom DLL** handles spawning the GameObject at runtime via `SpawnActor`.

---

## Requirements

- ✅ The **custom `.pak` file** containing the GameObject and necessary folder structure (once i have it done).
- ✅ The **HalfswordAnalyzer DLL**, which must replace:
  ```
  Half Sword Demo\Engine\Binaries\ThirdParty\NVIDIA\NVaftermath\Win64\GFSDK_Aftermath_Lib.x64.dll
  ```
  Replacing this DLL ensures the analyzer can spawn the GameObject as early and reliably as possible during the game's startup.

---

## Usage

1. Install the custom `.pak` file into the game's `Paks` directory (pak is not released yet).
2. Replace the existing `GFSDK_Aftermath_Lib.x64.dll` with the HalfswordAnalyzer DLL.
3. Launch the game normally.
4. The custom GameObject will automatically scan for available maps (once i get the pak ready).
5. Open the ImGui menu to browse and load maps (once i have imgui setup).

---

## Planned Features

- [ ] Display additional map metadata (author name, description, etc.)
- [ ] Add "Favorites" for quick-access maps
- [ ] Implement actual ImGUI Interface (currently everything is being handled by the Developer Console)

---

## Disclaimer

HalfswordAnalyzer is an unofficial, community-driven project and is not affiliated with or endorsed by the developers of **Halfsword**.