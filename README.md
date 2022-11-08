# Side Scroller - Ikaruga

This is a small side scrolling shooter with a fancy game twist. The ship you control has two colors. The colors the ship can take affect its abilities.

## Build
Simply use cmake to build sources e.g.:  
`mkdir build`  
`cd build`  
`cmake ..`  
`make`  

### Dependecies
- Boost with components: filesystem, system and regex (min version 1.54.0)
- SDL2 (min version 2.0.4)
- SDL2_image (min version 2.0.1)
- SDL2_mixer (min version 2.0.1)
- Qt (min version 4.8.0)

## Play
- Editor: To run the editor you need provive the path to the res direcotry: `./editor /path/to/res`  
- Game: To run the game you need provive the path to the res direcotry: `./ikaruga /path/to/res`

### Movement
Use arrow keys to move, space to shoot and 'c' to change color.

### Colors
Your bullets launch with the same color as Your ship. Bullets will only deal damage to enemies with the same color as the bullet. E. g. a green 
 bullet will damage a green enemy but a red bullet won't. The same behavior applies for enemy bullets and Your ship.

### PowerUps
- Star: GodMode (You will take no damage for a specific time period)
- Cross: Health (You will gain a specific amount of health)
- Weapons: If you already have the same weapon, your weapon will upgrade itself to the next level (shoots more bullets). Else your weapon will change to the collected one.
