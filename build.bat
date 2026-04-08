@echo off
echo Building DND_PROJECT...

"c:\Program Files\CodeBlocks\MinGW\bin\g++.exe" -fdiagnostics-color=always -g -I./include src/P_main.cpp src/P_Character.cpp src/P_CharacterManager.cpp src/P_Inventory.cpp src/P_Item.cpp src/P_Weapon.cpp src/P_Armor.cpp src/P_Gear.cpp src/P_spells.cpp src/P_SpellBook.cpp src/P_SpellSlots.cpp src/P_Wallet.cpp -static -o DND_PROJECT.exe

if %errorlevel% == 0 (
    echo Build successful! Running program...
    DND_PROJECT.exe
) else (
    echo Build failed.
    pause
)
