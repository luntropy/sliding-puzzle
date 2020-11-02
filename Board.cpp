#include "Board.h"

void Board::allocate_memory_board() {
    board = new int*[this->square_side];

    for (int i = 0; i < this->square_side; ++i) {
        board[i] = new int[this->square_side];
    }
}

void Board::assign_zero_state() {
    for (int i = 0; i < this->square_side; ++i) {
        for (int j = 0; j < this->square_side; ++j) {
            this->board[i][j] = 0;
        }
    }
}

void Board::copy_board_arrangement(const Board& board) {
    for (int i = 0; i < this->square_side; ++i) {
        for (int j = 0; j < this->square_side; ++j) {
            this->board[i][j] = board.board[i][j];
        }
    }
}

void Board::copy_board_obj(const Board& board) {
    this->I = board.I;
    this->square_side = board.square_side;
    this->allocate_memory_board();
    this->copy_board_arrangement(board);
    this->manhattan_cost = board.manhattan_cost;
    this->parent = board.parent;
    this->dir_shift = board.dir_shift;
    this->children = board.children;
}

std::pair<int, int> Board::get_position_by_value(int value, Board goal_board) {
    for (int i = 0; i < this->square_side; ++i) {
        for (int j = 0; j < this->square_side; ++j) {
            if (goal_board.board[i][j] == value) {
                return std::make_pair(i, j);
            }
        }
    }

    return std::make_pair(-1, -1);
}

int Board::manhattan_cost_tile(int i, int j, Board goal_board) {
    std::pair<int, int> goal = this->get_position_by_value(this->board[i][j], goal_board);

    return std::abs(i - goal.first) + std::abs(j - goal.second);
}

// EXTRA
// void Board::calculate_inversions() {
//
// }

void Board::clear_board() {
    for (int i = 0; i < this->square_side; ++i) {
            delete[] this->board[i];
    }

    delete[] this->board;

    std::vector<Board*>::iterator it;
    for (it = this->children.begin(); it != this->children.end(); ++it) {
        delete *it;
    }
}

Board::Board() {
    this->square_side = 0;
    this->I = -1;
    this->board = nullptr;
    this->manhattan_cost = 0;

    this->parent = nullptr;
    this->dir_shift = NONE;
}

Board::Board(int N, int I) {
    this->square_side = sqrt(N + 1);

    if (I == -1) {
        this->I = N;
    }
    else {
        this->I = I;
    }

    this->allocate_memory_board();
    this->assign_zero_state();
    this->manhattan_cost = 0;

    this->parent = nullptr;
    this->dir_shift = NONE;
}

Board::Board(const Board& board) {
    this->copy_board_obj(board);
}

Board& Board::operator=(const Board& board) {
    if (this != &board) {
        this->clear_board();
        this->copy_board_obj(board);
    }

    return *this;
}

Board::~Board() {
    this->clear_board();
}

void Board::generate_desired_solution() {
    int index_count = 0;
    int current_plate = 1;
    for (int i = 0; i < this->square_side; ++i) {
        for (int j = 0; j < this->square_side; ++j) {
            if (index_count == this->I) {
                this->board[i][j] = 0;
            }
            else {
                this->board[i][j] = current_plate;
                ++current_plate;
            }
            ++index_count;
        }
    }
}

// Get the board state from the input
void Board::arrange_board() {
    for (int i = 0; i < this->square_side; ++i) {
        for (int j = 0; j < this->square_side; ++j) {
            std::cin >> this->board[i][j];
        }
    }
}

void Board::set_goal(Board goal_board) {
    this->manhattan_cost = this->calc_manhattan_cost(goal_board);
}

bool Board::is_goal(Board goal_board) {
    for (int i = 0; i < this->square_side; ++i) {
        for (int j = 0; j < this->square_side; ++j) {
            if (this->board[i][j] != goal_board.get_tile_value(i, j)) {
                return 0;
            }
        }
    }

    return 1;
}

int Board::calc_manhattan_cost(Board goal_board) {
    int distance = 0;
    for (int i = 0; i < this->square_side; ++i) {
        for (int j = 0; j < this->square_side; ++j) {
            if (this->board[i][j] != 0) {
                distance += this->manhattan_cost_tile(i, j, goal_board);
            }
        }
    }

    return distance;
}

int Board::get_tile_count() {
    return this->square_side * 2 - 1;
}

int Board::get_tile_value(int i, int j) {
    return this->board[i][j];
}

int Board::get_zero_position() {
    return this->I;
}

int Board::get_square_side() {
    return this->square_side;
}

int Board::get_manhattan_cost() {
    return this->manhattan_cost;
}

void Board::print_board() {
    for (int i = 0; i < this->square_side; ++i) {
        for (int j = 0; j < this->square_side; ++j) {
            std::cout << this->board[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

// void Board::print_board_solution();
