# Sliding Puzzle
## Purpose
The objective of the program is to find a solution to a given sliding puzzle. A solution in this case is the minimum movements left, right, up or down, needed to order the plates in increasing order.

[Sliding puzzle Wikipedia](https://en.wikipedia.org/wiki/Sliding_puzzle)

## Rules
- The puzzle can have 8, 15, 24 or more plates.
- The empty place is displayed by the number 0.
- The ordering of the plates can happen by sliding them, if possible, in the position of the empty place.
- The sliding can be to left, right, up or down.
- Loops should be avoided, e.g. sliding up and then immediately down is not allowed.
- The user can input the number of plates, the index of the empty place in the final solution and the current positions of the plates.
- The index '-1' is the default position of the empty place - bottom right.

## About the program
The program uses the algorithm **IDA\*** and **Manhattan distance** to find the optimal solution to the given puzzle.

- There is no solution to some of the puzzle's configurations.
- More information about the unsolvable puzzles - [Here](https://www.cs.princeton.edu/courses/archive/spring18/cos226/assignments/8puzzle/index.html)

### To run the program
- Build it using `make`
- Run `./main`
- Input the number of plates.
- Input the position of the empty place in the final solution.
- Input the current order of the plates.

### Output
- Outputs the count of the needed steps to order the puzzle.
- Outputs the movements needed to reach the goal state.

### Example
![Example](https://github.com/luntropy/sliding-puzzle/blob/main/images/example-puzzle-3x3.png)

### Visualization of the final result - no movements needed
![Example-solution-visualization](https://github.com/luntropy/sliding-puzzle/blob/main/images/example-puzzle-3x3-no-movements.png)
