# AYED2-P4-Graphs (Bandit vs. Police)

## Project Overview
"Bandit vs. Police" is a (Rogue Like) C-based simulation game that depicts a chase between a bandit and a police officer on a two-dimensional grid. The objective is for the police officer to catch the bandit, while the bandit attempts to evade capture. Both characters move across the grid following distinct algorithms: the police officer moves towards the bandit's position, and the bandit moves away from the police officer.

## Compilation
To compile the project, use the gcc compiler with the following command executed in the project's root directory:
```bash
gcc -o game src/*.c
```
This command will generate an executable named `game`.

## Usage
After compilation move to src directory, run the game using:
```bash
./game <scenario>.txt
```
The game will display the grid in the console, updating the positions of the police officer and the bandit each turn until the police officer catches the bandit or another termination condition is met.

## Note on the Bandit's Algorithm
It's important to note that the bandit's movement algorithm is (currently) a direct inversion of the police officer's algorithm. While the police officer moves toward the bandit's current position, the bandit moves away from the police officer's position. This simplistic strategy may appear naive or predictable, as it doesn't incorporate more sophisticated evasion tactics. Consequently, the bandit's behavior might seem less intelligent or straightforward in its attempt to escape the police officer.
