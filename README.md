# Mare Nostrum V3 — Unreal Engine 5 Port

## Overview
3D port of Mare Nostrum — a Roman Mediterranean strategy game. Port from p5.js (V2) to Unreal Engine 5.6.

## Prerequisites
- Unreal Engine 5.6 (install via Epic Games Launcher)
- Visual Studio 2022 with C++ game development workload
- ~100GB disk space for UE5

## Setup
1. Install UE 5.6 from Epic Games Launcher
2. Open Epic → Library → Launch UE 5.6
3. Create new project: Top Down template, C++, Starter Content
4. Name: MareNostrum, Location: this repo folder

## Game Design (from V2)
- 27 islands (8 faction capitals + 19 special)
- 8 factions: Rome, Carthage, Egypt, Greece, Persia, Gaul, Phoenicia, Sea People
- Conquest mode: build army, sail, invade, capture islands
- Victory: Military (6 capitals) / Economic (4 hubs + 100k gold) / Diplomatic (Senate + 4 allies)

## Architecture Plan
```
Source/MareNostrum/
  Core/           — Game state, save/load
  Islands/        — Island generation, rendering, LOD
  Ships/          — Ship movement, docking, sailing
  Combat/         — Army, invasion, garrison
  Factions/       — Faction data, AI, diplomacy
  Economy/        — Resources, trade, production
  UI/             — HUD, menus, panels (UMG)
  Audio/          — Music, ambient, narration
```

## Phase Plan
| Phase | Duration | Milestone |
|-------|----------|-----------|
| 1. Foundation | 4 weeks | World, player, sailing |
| 2. Core | 4 weeks | Islands, buildings, resources |
| 3. Gameplay | 4 weeks | Army, combat, AI |
| 4. Polish | 4 weeks | UI, audio, visuals |

## Repos
- V1 (original): github.com/amidadragon/mare-nostrum
- V2 (polished): github.com/amidadragon/mare-nostrum-v2
- V3 (Unreal): github.com/amidadragon/mare-nostrum-v3
