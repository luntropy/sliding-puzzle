#include <iostream>

#include <utility>
#include <string>

// #include <chrono>
#include <cmath>

#ifndef BOARD_H
#define BOARD_H

enum direction { NONE, UP, DOWN, RIGHT, LEFT };

class Board {
private:
    int** tiles;
    direction dir_shift;
    int manhattan_cost;
    int side_size;
    std::pair<int, int> zero_goal_position;
    std::pair<int, int> zero_curr_position;

    void allocate_memory_board();
    void assign_zero_state();

    std::pair<int, int> get_position_by_value(int, Board*);
    int get_value_by_position(std::pair<int, int>);
    int manhattan_cost_tile(int, int, Board*);
    int calc_manhattan_cost(Board*);
    void switch_values(std::pair<int, int>, std::pair<int, int>);

    void set_manhattan_cost(Board*);
    void set_side_size(int);
    void set_zero_goal_position(int);
    void copy_board_arrangement(const Board&);
    void copy_board_obj(const Board&);

    void clear();

public:
    Board();
    Board(int, int);
    Board(const Board&);
    Board& operator=(const Board&);
    ~Board();

    void arrange_board();
    void generate_goal();

    void set_goal(Board*);

    direction get_dir_shift() const;
    int get_manhattan_cost() const;

    bool is_goal() const;

    void print_board() const;
    void print_board_data() const;

    Board* move_up(Board*);
    Board* move_down(Board*);
    Board* move_right(Board*);
    Board* move_left(Board*);
};

#endif
