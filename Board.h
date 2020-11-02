#include <iostream>

#include <utility>
#include <vector>

#include <cmath>

#ifndef BOARD_H
#define BOARD_H

enum direction {NONE, UP, DOWN, RIGHT, LEFT};

class Board {
private:
    // Translate I to pair
    // Input validation
    int I;
    int square_side;
    int** board;
    int manhattan_cost;

    Board* parent;
    direction dir_shift;
    std::vector<Board*> children;

    void allocate_memory_board();
    void assign_zero_state();
    void copy_board_arrangement(const Board&);
    void copy_board_obj(const Board&);

    std::pair<int, int> get_position_by_value(int, Board);
    int manhattan_cost_tile(int, int, Board);

    // To check if the puzzle is solvable:
    // void calculate_inversions();

    // To check if we are in a loop:
    // void detect_loop();

    void clear_board();

public:
    Board();
    Board(int, int);
    Board(const Board&);
    Board& operator=(const Board&);
    // May need change
    ~Board();

    // TO DO AFTER RESEARCH
    void generate_desired_solution();
    void arrange_board();
    void set_goal(Board);
    bool is_goal(Board);

    int calc_manhattan_cost(Board);

    int get_tile_value(int, int);
    int get_tile_count();
    int get_zero_position();
    int get_square_side();
    int get_manhattan_cost();

    void print_board();
    // void print_board_solution();
};

#endif
