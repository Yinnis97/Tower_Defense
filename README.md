# Tower Defense

## Table of Contents
- [Overview](#overview)
- [Setup Instructions](#setup-instructions)
- [How To Play](#how-to-play)
- [Bugs and WiP](#bugs-and-wip)
- [Sources](#sources)


## Overview 
**Type of Project** : Game  
**Type of Game**    : Tower Defence      
**Language**        : C++   
**Libraries**       : SFML  


## Setup Instructions

**Option 1 : .Exe**        
1. On the right check the latest release and download the TowerDefense-Windows.Zip file.    

2. Unzip the .Zip file. 

3. Start the .Exe.     

**Option 2 : cmake**
1. On the right check the latest release and download the TowerDefense-Windows.Zip file.    
2. Unzip the .Zip file. 
3. Open the command line and enter the following commands:

    ```cmd
    cmake -B build -A Win32 -DCMAKE_BUILD_TYPE=Release
    ```
    ```cmd
    cmake --build build --config Release
    ```
4. A build folder should now be available.  
5. Open the build folder and navigate to the release folder.    
6. Start the .Exe.  

## How To Play

### Introduction
In this Tower Defense Game your goal is to stop enemies from reaching the end of the path.  
You'll achieve this by placing towers and defeating those enemies before they reach the end.    

### **Enemies**

**There are 4 types of enemies in the latest version of the game.** 

- **1. Normal**        
    - Lowest hitpoints  
    - Their spawnrate is very high (85% chance).

- **2. Magic**        
    - Average hitpoints     
    - Their spawnrate is low (10% chance).
    
- **3. Rare**        
    - High hitpoints    
    - Their spawnrate is very low (5% chance).

- **4. Boss**        
    - Extremly High hitpoints    
    - Their spawnrate varies depending on the game.

### **Towers**

**There are 3 types of towers in the latest version of the game.**  

- **1. Turret Tower**     
    - High rate of fire     
    - Low damage per bullet     
    - Average bullet velocity     
    - Low costs 

- **2. Rocket Tower**     
    - Low rate of fire  
    - Average damage per bullet     
    - Very slow bullet velocity      
    - Average costs     

- **3. Sniper Tower**          
    - Low rate of fire      
    - Very high damage per bullet       
    - Very fast bullet velocity     
    - High costs    


### **Upgrades & Currency & Loot**

- The game has a random loot system, this means that drops are random.    
- Player gains XP and loot (gold,silver,copper) by killing enemies.   
- Towers can be upgraded by using gold,silver or copper.  
- Enemies level up over time. 
- Enemies can also drop rare materials (Sapphire).  

## Bugs and WiP

- **The game is still in a rough state and is still being worked on.**

- **Things to do**      
    - Make use of player level.
    - Use of rare materials
    - Boss spawning interval
    - Much more...


- If you've found a bug or any problems please feel free to make an issue.

## Sources

[SFML Website](https://www.sfml-dev.org/)