# CSCI 1300 Final Project
# Journey Through the Genome

Journey Through the Genome is a two-player, text-based board game where players compete to become the next Lead Genomicist in a lion conservation genomics lab. Players move across a two-lane board, complete DNA-based challenges, face random lab events, and earn Discovery Points based on their performance.

---

## How the Game Works

- This is a 2-player game.
- Each player chooses:
  - A scientist character with starting stats.
  - A path type:
    - Training Fellowship – slower start but stronger long-term abilities.
    - Direct Lab Assignment – faster start with higher risk.
- Players take turns spinning a virtual spinner to move across the board.
- The game ends when both players reach the final tile (Genome Conference).
- The player with the highest Discovery Points (DP) at the end wins.

---

## Board and Tile Types

Each player has their own lane on a 52-tile board. Tiles trigger different events:

- Green (G) – Random lab events that can add or remove DP.
- Purple (U) – Riddle challenges.
- Blue (B) – DNA similarity task (equal-length comparison).
- Pink (P) – DNA similarity task (unequal-length best match).
- Red (R) – DNA mutation identification with alignment.
- Brown (T) – DNA to RNA transcription task.
- Grey – Starting tile.
- Orange – Final tile where scoring is completed.

---

## DNA Challenges

Players will complete four different DNA-based tasks:

1. Blue Tile – Compare two equal-length DNA strands.
2. Pink Tile – Find the best alignment of a shorter strand inside a longer one.
3. Red Tile – Identify substitutions, deletions, and insertions after alignment.
4. Brown Tile – Transcribe a DNA strand into RNA by replacing T with U.

These tasks affect player stats such as Accuracy, Insight, Efficiency, and Discovery Points.

---

## Advisors

Players who choose the Training Fellowship path select an advisor. Advisors can protect players from certain negative random events.

---

## End of Game Scoring

When both players reach the final tile:

- Every 100 points of Accuracy, Efficiency, and Insight are converted into 1,000 Discovery Points.
- Final stats are displayed.
- The winner is declared based on total Discovery Points.
- Final game results are saved to `game_stats.txt`.

---

## Files Used

- main.cpp – Main game logic
- Board.h / Board.cpp – Game board structure
- Player.h / Player.cpp – Player class
- Tile.h – Tile structure
- characters.txt – Playable characters
- advisor.txt – Advisor list
- random_events.txt – Green tile events
- riddles.txt – Purple tile riddles

---

## How to Run

1. Compile the project using a C++ compiler: `g++ main.cpp Board.cpp Player.cpp -o genomeGame`
2. Run the program: `./genomeGame`

## Goal

Make smart decisions, complete DNA challenges correctly, manage your traits wisely, and finish with the most Discover Points to become the next Lead Genomicist.

