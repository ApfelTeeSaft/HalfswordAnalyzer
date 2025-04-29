# HalfswordAnalyzer

**HalfswordAnalyzer** is a custom map handler for the game [**Halfsword**](https://store.steampowered.com/app/2397300/Half_Sword/), enabling **custom map loading** during gameplay via a Object Iteration that checks fo Objects of type `ULevel::StaticClass`.
The system tracks all available custom maps and provides a simple **ImGui** interface to select and load them.

> Current Game Version Info (as of April 28, 2025):  
> **AES Key for .pak decryption:**  
> `0xBCBF7B45A4A8150D06F7B955BC25EF5CE603470F508302CAD0EB48FEA2D91517`

---

## Features

- 🔹 **Custom Map Loading**: Load custom maps.
- 🔹 **ImGui Integration**: Select and load maps with an in-game menu.
- 🔹 **Custom Map Support**: Easily add new maps by dropping pak files in the Games Content.

---

## How It Works

- A **custom `.dll` file** provides a **Object Enumerator** tailored for HalfswordAnalyzer.
- This DLL **enumerates through all objects** inside the game's memory.
- Upon being executed, the code **scans all objects** for assets of type `ULevel::StaticClass`, and **registers them** for loading through the ImGui menu.

---

## Requirements

- ✅ The **HalfswordAnalyzer DLL**, which must replace:
  ```
  Half Sword Demo\Engine\Binaries\ThirdParty\NVIDIA\NVaftermath\Win64\GFSDK_Aftermath_Lib.x64.dll
  ```
  Replacing this DLL ensures the analyzer can initialize without requiring injection.

---

## Usage

1. Replace the existing `GFSDK_Aftermath_Lib.x64.dll` with the HalfswordAnalyzer DLL.
2. Launch the game normally.
3. The custom DLL will automatically scan for available maps.
4. Open the ImGui menu to browse and load maps (INSERT toggles the Menu).

---

## Disclaimer

HalfswordAnalyzer is an unofficial, community-driven project and is not affiliated with or endorsed by the developers of **Halfsword**.
