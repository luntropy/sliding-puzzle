#include <iostream>
#include "Node.h"

int main() {
    // Get the input
    int N, I;

    std::cin >> N >> I;

    Board* goal = new Board(N, I);
    goal->generate_goal();

    // Create Start state to pass it to the Node as root
    Board* start_board = new Board(N, I);
    start_board->arrange_board();
    start_board->set_goal(goal);

    // Create the root node
    Node* start = new Node(start_board);
    start->set_goal(goal);

    std::pair<std::stack<Node*>, int> result = start->ida_star(goal);
    if (result.second != -1) {
        std::cout << std::endl;
        std::cout << result.second << std::endl;
        std::cout << std::endl;

        while (!result.first.empty()) {
            Node* node = result.first.top();
            node->print_dir_shift();
            std::cout << std::endl;
            result.first.pop();
        }
    }
    else {
        std::cout << "No solution found." << std::endl;
    }

    delete goal;
    delete start_board;
    delete start;

    return 0;
}
