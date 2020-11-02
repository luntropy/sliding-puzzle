#include <iostream>

#include "Board.h"

/* Algorithm

0. Check if the puzzle is solvable
1. Get current state and generate possible moves from that state
    1.1. Evaluate the heruistic - Manhattan
2. Move to the next node that is with the best heruistic result
3. Avoid nodes that cause loops
4. Find the result and return it

*/

int main() {
    int N;
    int I;

    std::cout << "Count of plates with numbers: ";
    std::cin >> N;

    std::cout << "Position of the 0 in the solution: ";
    std::cin >> I;

    Board goal = Board(N, I);
    goal.generate_desired_solution();
    Board start = Board(N, I);

    std::cout << "Arrangement of the board: " << std::endl;
    start.arrange_board();
    std::cout << std::endl;
    start.print_board();

    std::cout << std::endl;
    std::cout << "Goal: " << std::endl;
    goal.print_board();
    std::cout << std::endl;

    // Board test = Board(goal);
    // std::cout << "Test board: " << std::endl;
    // test.print_board();

    std::cout << "Copy new board to goal: " << std::endl;
    goal = start;
    goal.print_board();

    std::cout << "Goal or not: " << start.is_goal(goal) << std::endl;

    // std::cout << "Distance: " << std::endl;
    start.set_goal(goal);
    std::cout << start.get_manhattan_cost() << std::endl;

    return 0;
}
