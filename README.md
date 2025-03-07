# 2nd_Insem_project_Tetris-


## TABLE AND CONTENTS:

-[Description](#Description)
**🎮 Classic Tetris Game**  
Tetris is a tile-matching puzzle game where the player manipulates falling **tetrominoes** (shapes made of four blocks) to create complete horizontal lines. Our Tetris game runs on a **grid of size 10x20**, where pieces spawn at the top and gradually fall downward. The player can rotate and move the pieces left or right using **keyboard inputs** (W/A/S/D or arrow keys). Pressing **down accelerates** the falling speed of the piece.  
🛠 **Implementation Details:**  
🔹 **Object-Oriented Approach**: Classes for **Tetrominoes, Game Board, and Game Controller**.  
🔹 **Grid Representation**: A **2D array** stores the board, and tetrominoes are handled using **vector-based rotation matrices**.  
🔹 **Collision Handling**: Ensures blocks **lock** in place and prevents movement outside boundaries.  
🔹 **Scoring System**: **Points increase** based on the number of lines cleared simultaneously.  
🔹 **Game Over & Score Display**: The final score appears in the **terminal** after the game ends.  

This project uses **loops, conditionals, and functions** to create an engaging **Tetris experience** with smooth controls and dynamic difficulty! 🚀

-[installation](#installation)
To run our game click on the link given below :
[`tetris.cpp`](./tetris.cpp).  

-[Game Manual](#Game-Manual)
✅ *Game Rules & Mechanics:*  
🟦 The goal is to *clear lines* by forming unbroken horizontal rows.  
🟧 When a row is completed, it *disappears*, and the blocks above shift downward.  
🟩 The game *ends when the stack reaches the top* of the grid.  
🟥 Speed *increases after every 10 cleared lines*, making the game progressively harder.  
[🎥 Watch the Demo]()



-[Team](#Team)
Diya Bhuva    - 202401410
Neeti Gunsai  - 202401423
Madhav Parmar - 202401260
Tirth Ditani  - 202401417

