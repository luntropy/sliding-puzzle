#include "Board.h"

void Board::allocate_memory_board() {
    this->tiles = new int*[this->side_size];

    for (int i = 0; i < this->side_size; ++i) {
        this->tiles[i] = new int[this->side_size];
    }
}

void Board::assign_zero_state() {
    for (int i = 0; i < this->side_size; ++i) {
        for (int j = 0; j < this->side_size; ++j) {
            this->tiles[i][j] = 0;
        }
    }
}

// Calculate Manhnattan distance
std::pair<int, int> Board::get_position_by_value(int value, Board* goal) {
    for (int i = 0; i < this->side_size; ++i) {
        for (int j = 0; j < this->side_size; ++j) {
            if (goal->tiles[i][j] == value) {
                return std::make_pair(i, j);
            }
        }
    }

    return std::make_pair(-1, -1);
}

int Board::get_value_by_position(std::pair<int, int> pos) {
    return this->tiles[pos.first][pos.second];
}

int Board::manhattan_cost_tile(int i, int j, Board* goal) {
    std::pair<int, int> position = this->get_position_by_value(this->tiles[i][j], goal);

    return std::abs(i - position.first) + std::abs(j - position.second);
}

int Board::calc_manhattan_cost(Board* goal) {
    int distance = 0;
    for (int i = 0; i < this->side_size; ++i) {
        for (int j = 0; j < this->side_size; ++j) {
            if (this->tiles[i][j] != 0) {
                distance += this->manhattan_cost_tile(i, j, goal);
            }
        }
    }

    return distance;
}

void Board::switch_values(std::pair<int, int> from, std::pair<int, int> to) {
    int num = this->get_value_by_position(from);
    this->tiles[from.first][from.second] = this->tiles[to.first][to.second];
    this->tiles[to.first][to.second] = num;
}

void Board::set_manhattan_cost(Board* goal) {
    this->manhattan_cost = this->calc_manhattan_cost(goal);
}

void Board::set_side_size(int N) {
    this->side_size = sqrt(N + 1);
}

void Board::set_zero_goal_position(int I) {
    if (I == -1) {
        this->zero_goal_position = std::make_pair(this->side_size - 1, this->side_size - 1);
    }
    else {
        this->zero_goal_position = std::make_pair(floor(I / this->side_size), I % this->side_size);
    }
}

void Board::copy_board_arrangement(const Board& board) {
    for (int i = 0; i < this->side_size; ++i) {
        for (int j = 0; j < this->side_size; ++j) {
            this->tiles[i][j] = board.tiles[i][j];
        }
    }
}

void Board::copy_board_obj(const Board& board) {
    this->dir_shift = board.dir_shift;
    this->manhattan_cost = board.manhattan_cost;
    this->side_size = board.side_size;
    this->allocate_memory_board();
    this->copy_board_arrangement(board);
    this->zero_goal_position = board.zero_goal_position;
    this->zero_curr_position = board.zero_curr_position;
}

void Board::clear() {
    for (int i = 0; i < this->side_size; ++i) {
            delete[] this->tiles[i];
    }

    delete[] this->tiles;
}

Board::Board() {
    this->tiles = nullptr;
    this->dir_shift = NONE;
    this->manhattan_cost = 0;
    this->side_size = 0;
    this->zero_goal_position = std::make_pair(0, 0);
    this->zero_curr_position = std::make_pair(0, 0);
}

Board::Board(int N, int I) {
    this->set_side_size(N);
    this->allocate_memory_board();
    this->assign_zero_state();
    this->dir_shift = NONE;
    this->manhattan_cost = 0;
    this->set_zero_goal_position(I);
    this->zero_curr_position = std::make_pair(0, 0);
}

Board::Board(const Board& board) {
    this->copy_board_obj(board);
}

Board& Board::operator=(const Board& board) {
    if (this != &board) {
        this->clear();
        this->copy_board_obj(board);
    }

    return *this;
}

Board::~Board() {
    this->clear();
}

void Board::arrange_board() {
    for (int i = 0; i < this->side_size; ++i) {
        for (int j = 0; j < this->side_size; ++j) {
            int number = 0;
            std::cin >> number;
            this->tiles[i][j] = number;

            if (number == 0) {
                this->zero_curr_position = std::make_pair(i, j);
            }
        }
    }
}


// Assigns the Goal state to a given board
void Board::generate_goal() {
    int current_plate = 1;
    for (int i = 0; i < this->side_size; ++i) {
        for (int j = 0; j < this->side_size; ++j) {
            if (this->zero_goal_position.first == i && this->zero_goal_position.second == j) {
                this->tiles[i][j] = 0;
            }
            else {
                this->tiles[i][j] = current_plate;
                ++current_plate;
            }
        }
    }

    this->zero_curr_position = this->zero_goal_position;
}

void Board::set_goal(Board* goal) {
    this->manhattan_cost = this->calc_manhattan_cost(goal);
}

direction Board::get_dir_shift() const {
    return this->dir_shift;
}

int Board::get_manhattan_cost() const {
    return this->manhattan_cost;
}

bool Board::is_goal() const {
    int max = this->tiles[0][0];

    // Position of the zero in the Goal state
    int k = this->zero_goal_position.first;
    int l = this->zero_goal_position.second;
    if (this->tiles[k][l] != 0) {
        return false;
    }

    for (int i = 0; i < this->side_size; ++i) {
        for (int j = 0; j < this->side_size; ++j) {
            if (i == k && j == l) {
                continue;
            }

            // Check only if it is bigger or if it is +1 than the previous tile?
            if (max <= this->tiles[i][j]) {
                max = this->tiles[i][j];
            }
            else {
                return false;
            }
        }
    }

    return true;
}

void Board::print_board() const {
    for (int i = 0; i < this->side_size; ++i) {
        for (int j = 0; j < this->side_size; ++j) {
            std::cout << this->tiles[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void Board::print_board_data() const {
    std::cout << "Board arrangement: " << std::endl;
    this->print_board();
    std::cout << "Manhattan cost: " << this->manhattan_cost << std::endl;
    std::cout << "Side size: " << this->side_size << std::endl;
    std::cout << "Position of the zero in Goal: " << '(' << this->zero_goal_position.first << ',' << this->zero_goal_position.second << ')' << std::endl;
    std::cout << "Position of the zero currently: " << '(' << this->zero_curr_position.first << ',' << this->zero_curr_position.second << ')' << std::endl;

    std::string movement;

    if (this->dir_shift == 1) {
        movement = "UP";
    }
    else if (this->dir_shift == 2) {
        movement = "DOWN";
    }
    else if (this->dir_shift == 3) {
        movement = "RIGHT";
    }
    else if (this->dir_shift == 4) {
        movement = "LEFT";
    }
    else {
        movement = "NONE";
    }
    std::cout << "Movement: " << movement << std::endl;
}

// Movement up moves the zero down
Board* Board::move_up(Board* goal) {
    int x = this->zero_curr_position.first;

    if ((x + 1) > (this->side_size - 1)) {
        return nullptr;
    }

    std::pair<int, int> new_pos = std::make_pair(this->zero_curr_position.first + 1, this->zero_curr_position.second);
    // Switch positions
    this->switch_values(this->zero_curr_position, new_pos);
    this->zero_curr_position = new_pos;
    this->set_manhattan_cost(goal);
    this->dir_shift = UP;

    return this;
}

// Movement down moves the zero up
Board* Board::move_down(Board* goal) {
    int x = this->zero_curr_position.first;

    if ((x - 1) < 0) {
        return nullptr;
    }

    std::pair<int, int> new_pos = std::make_pair(this->zero_curr_position.first - 1, this->zero_curr_position.second);
    // Switch positions
    this->switch_values(this->zero_curr_position, new_pos);
    this->zero_curr_position = new_pos;
    this->set_manhattan_cost(goal);
    this->dir_shift = DOWN;

    return this;
}

// Movement to the right moves the zero to the left
Board* Board::move_right(Board* goal) {
    int y = this->zero_curr_position.second;

    if ((y - 1) < 0) {
        return nullptr;
    }

    std::pair<int, int> new_pos = std::make_pair(this->zero_curr_position.first, this->zero_curr_position.second - 1);
    // Switch positions
    this->switch_values(this->zero_curr_position, new_pos);
    this->zero_curr_position = new_pos;
    this->set_manhattan_cost(goal);
    this->dir_shift = RIGHT;

    return this;
}

// Movement to the left moves the zero to the right
Board* Board::move_left(Board* goal) {
    int y = this->zero_curr_position.second;

    if ((y + 1) > (this->side_size - 1)) {
        return nullptr;
    }

    std::pair<int, int> new_pos = std::make_pair(this->zero_curr_position.first, this->zero_curr_position.second + 1);
    // Switch positions
    this->switch_values(this->zero_curr_position, new_pos);
    this->zero_curr_position = new_pos;
    this->set_manhattan_cost(goal);
    this->dir_shift = LEFT;

    return this;
}
