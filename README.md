Sudoku Tournament Manager
This project is a console-based Sudoku game simulator written in C. It allows multiple players to participate in a Sudoku competition where they each attempt to solve a randomly generated board. Players are evaluated based on how many cells they start with filled and whether they complete the board without conflicts.
🎮 Features
- Randomly generates partially filled Sudoku boards
- Computes legal values for each empty cell using constraint logic
- Allows players to take turns solving their board with interactive input
- Simulates a tournament using a binary tree structure
- Maintains and displays a final winners list
🧠 How It Works

1. User is prompted to enter the number of players and their names.
2. Each player receives a random valid Sudoku board with a random number of filled cells (1–20).
3. Possible legal digits for each empty cell are computed.
4. Players are sorted by number of filled cells (ascending) and then alphabetically.
5. A complete binary tree is built from the sorted list.
6. The game progresses by in-order traversal of the tree:
   - Each player attempts to solve their board.
   - If successful, they are added to the winners list.
   - If not, they are eliminated.
7. At the end, the winners list is printed with completed boards.

🗓️ This project was created in 2024 as part of a C programming course.
