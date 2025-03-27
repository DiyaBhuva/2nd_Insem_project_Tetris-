# CLASSIC TETRIS GAME-


## TABLE AND CONTENTS:

-[Description](#Description)

Tetris is a legendary tile-matching puzzle game where players manipulate falling tetrominoes (shapes made of four blocks) to create complete horizontal lines. Our implementation of Tetris features a 10x20 grid, where pieces spawn at the top and descend gradually. Players can control the tetrominoes using the keyboard to rotate, move left or right, and accelerate their fall.

🛠 Implementation Details:

~ Object-Oriented Design: Separate classes for Tetrominoes, Game Board, and Game Controller ensure modularity and clean code structure.

~ Grid Representation: A 2D array models the game board, while tetromino rotations use vector-based transformation matrices.

~ Collision Handling: Ensures tetrominoes lock in place and do not move outside the play area.

~ Scoring System: Scores increase based on the number of lines cleared simultaneously.

~ Game Over & Score Display: The final score appears in the terminal after the game ends.

~ Dynamic Difficulty: The falling speed increases after every 10 cleared lines, making the game progressively more challenging.

~ High Score Tracking: The highest score achieved in a session is stored and displayed.

~ Play Again Feature: Players can restart the game without closing and reopening the program.

~ Hard Drop (Instant Drop): Pressing the Space bar instantly drops the current piece to the bottom.

~ Exit Option: Players can press Esc to exit the game anytime.


-[installation](#installation)


To run our game, click on the link below and execute the file in your C++ environment:
👉[`tetris.cpp`](./tetris.cpp).  

-[Game Manual](#Game-Manual)

🎮 Game Manual

✅ Game Rules & Mechanics:

🟦 The objective is to clear lines by forming unbroken horizontal rows.

🟧 When a row is completed, it disappears, and blocks above it shift downward.

🟩 The game ends when the tetromino stack reaches the top of the grid.

🟥 Speed increases after every 10 cleared lines, adding more challenge.

🔺 Press Space for a hard drop, instantly placing the piece at the lowest possible position.

⏬ Press the Down Arrow to accelerate a piece’s fall.

🔄 Rotate the tetromino using W or the Up Arrow.

◀ Move left with A or the Left Arrow.

▶ Move right with D or the Right Arrow.

❌ Press Esc to pause the game anytime and press 'Y' to resume game or press 'N' to end the game .

🔄 After the game is over press 'Y' to play again or press 'N' to end the game .

[🎥 Watch the Demo](https://github.com/DiyaBhuva/2nd_Insem_project_Tetris-/blob/main/tetris_game%20(1).mp4)



-[Team](#Team)



Diya Bhuva    - 202401410

Neeti Gunsai  - 202401423


Madhav Parmar - 202401260


Tirth Ditani  - 202401417

