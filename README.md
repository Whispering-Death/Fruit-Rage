# Fruit-Rage
An automated game playing agent designed to maximize the chances of winning a time constrained game similar to Candy Crush.

## Algorithm
- Creating a class to store the state of a particular game.
- To explore all game states in a depth first fashion.
- Reducing the search space using alpha-beta pruning.
- Running an iterative DFS till a particular maximum branching depth in accordance with the time constraints.

## Files
- calibration.cpp : Experimenting with different grid sizes to estimate the time taken in various scenarios.
- fruit_rage.cpp : Code for the automated agent.
- calibration.csv : Information compiled from a number of test runs.

## Implementation
- Branching depth vs Time tradeoff.
- Analyzed the information from the generated csv file.
- Set a maximum branching depth
- Used exactly half the time available to make a single move.



