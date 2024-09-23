# snake_game
This C++ snake game pits the player-controlled snake (@) against a random-moving enemy snake (%). The objective is to grow by eating two types of food:

X: Adds 1 to the snake’s length.
$: Adds 3 to the snake’s length.
Players need to avoid hitting walls, which results in instant death. The game introduces a competitive mechanic where if a player’s head touches the enemy's body:

If the player's snake is longer, the enemy snake is consumed, adding its length to the player’s snake.
If the player's snake is shorter, the player dies from "toothache," and the game ends.
the same rules apply to enemy snake.
Colliding heads results in both snakes dying, adding a layer of strategy to the gameplay. These mechanics make for a fun, engaging, and competitive snake experience.
