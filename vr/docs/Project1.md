# Zombie Defender Outline

Sounds
- BGM
- zombie moan
- zombie killed
- player hit

Environment
- ground
- skybox
- obstacles
- Navmesh

Zombie: Animations
- Spawn
- Walk
- Attack
- Die

Zombie: Logic
- Bool isAlive;
- float minSpawn, maxSpawn;
- float timeTilSpawn = Random.Range(minSpawn, maxSpawn);
- States { IDLE, SPAWN, WALK, DIE, ATTACK }
  - Methods for each state and trigger animations
- Spawn interval

VR:
- Teleportation
- Grabbing
  - Bool hasWeapon;
- Throwing

Start Menu
- Instructions
- Button to move to next scene

Game end moves to start menu

Scoring system for number zombies killed and time survived

Game end screen

static class to hold persistent data
- int zombieCount {get; set;}
- int zombiesKilled {get; set;}
- float timePassed {get;}
