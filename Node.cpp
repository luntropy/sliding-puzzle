#include "Node.h"

// Algorithm
std::pair<std::stack<Node*>, int> Node::ida_star(Board* goal) {
    int threshold = this->get_manhattan_cost();
    std::stack<Node*> result;
    std::stack<Node*> path;
    path.push(this);

    // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    while (true) {
        std::vector<Node*> visited;
        // std::cout << "Iteration with threshold: " << threshold << std::endl;
        std::pair<bool, int> res = search(path, 0, threshold, visited, &result, goal);

        if (res.first) {
            // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            // std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;

            return std::make_pair(result, threshold);
        }

        if (res.second == INT_MAX) {
            return std::make_pair(result, -1);
        }

        threshold = res.second;
    }
}

std::pair<bool, int> Node::search(std::stack<Node*> path, int g, int threshold, std::vector<Node*> visited, std::stack<Node*>* result, Board* goal) {
    Node* current = path.top();
    visited.push_back(current);
    int f = g + current->get_manhattan_cost();

    if (f > threshold) {
        return std::make_pair(false, f);
    }

    if (current->is_goal()) {
        return std::make_pair(true, threshold);
    }

    int min = INT_MAX;

    if (current->children.empty()) {
        current->generate_children(goal); // Children are ordered by
    }

    std::vector<Node*>::iterator it;
    for (it = current->children.begin(); it != current->children.end(); ++it) {
        std::vector<Node*>::iterator in_path = std::find(visited.begin(), visited.end(), *it); // Check if the node is already in the path

        if (in_path == visited.end()) {
            path.push(*it);
            std::pair<bool, int> res = search(path, g + 1, threshold, visited, result, goal);

            if (res.first) {
                (*result).push(*it); // Construct the result path
                return std::make_pair(true, f);
            }

            if (res.second < min) {
                min = res.second;
            }

            path.pop();
        }
    }

    return std::make_pair(false, min);
}

int Node::calc_depth() {
    if (this->parent) {
        return (this->parent)->get_depth() + 1;
    }

    return 0;
}

void Node::generate_children(Board* goal) {
    int prev_dir_shift = this->get_dir_shift();
    Node* new_node = nullptr;

    if (prev_dir_shift != UP) {
        Board* move_down_state = new Board(*this->board);
        move_down_state = move_down_state->move_down(goal);

        if (move_down_state) {
            new_node = new Node(this, move_down_state);
            this->children.push_back(new_node);
        }
    }

    if (prev_dir_shift != DOWN) {
        Board* move_up_state = new Board(*this->board);
        move_up_state = move_up_state->move_up(goal);

        if (move_up_state) {
            new_node = new Node(this, move_up_state);
            this->children.push_back(new_node);
        }
    }

    if (prev_dir_shift != RIGHT) {
        Board* move_left_state = new Board(*this->board);
        move_left_state = move_left_state->move_left(goal);

        if (move_left_state) {
            new_node = new Node(this, move_left_state);
            this->children.push_back(new_node);
        }
    }

    if (prev_dir_shift != LEFT) {
        Board* move_right_state = new Board(*this->board);
        move_right_state = move_right_state->move_right(goal);

        if (move_right_state) {
            new_node = new Node(this, move_right_state);
            this->children.push_back(new_node);
        }
    }

    std::sort(this->children.begin(), this->children.end(), compare_nodes());
}

void Node::copy_node_obj(const Node& node) {
    this->parent = node.parent;
    this->board = node.board;
    this->depth = node.depth;
    this->children = node.children;
}

void Node::clear() {
    delete this->board;

    std::vector<Node*>::iterator it;
    for (it = this->children.begin(); it != this->children.end(); ++it) {
        delete *it;
    }
}

Node::Node() {
    this->parent = nullptr;
    this->board = nullptr;
    this->depth = 0;
}

// For root creation
Node::Node(Board* board) {
    this->parent = nullptr;
    this->board = board;
    this->depth = this->calc_depth();
}

// For child creation
Node::Node(Node* parent, Board* board) {
    this->parent = parent;
    this->board = board;
    this->depth = this->calc_depth();
}

Node::Node(const Node& node) {
    this->copy_node_obj(node);
}

Node& Node::operator=(const Node& node) {
    if (this != &node) {
        this->clear();
        this->copy_node_obj(node);
    }

    return *this;
}

Node::~Node() {
    this->clear();
}

void Node::set_goal(Board* goal) {
    (this->board)->set_goal(goal);
}

Board* Node::get_board() const {
    return this->board;
}

int Node::get_depth() const {
    return this->depth;
}

direction Node::get_dir_shift() const {
    return (this->board)->get_dir_shift();
}

int Node::get_manhattan_cost() const {
    return (this->board)->get_manhattan_cost();
}

bool Node::is_goal() const {
    return (this->board)->is_goal();
}

int Node::cost(Node* to) const {
    return to->depth - this->depth;
}

void Node::print_dir_shift() const {
    std::string movement;

    if (this->get_dir_shift() == 1) {
        movement = "up";
    }
    else if (this->get_dir_shift() == 2) {
        movement = "down";
    }
    else if (this->get_dir_shift() == 3) {
        movement = "right";
    }
    else if (this->get_dir_shift() == 4) {
        movement = "left";
    }
    else {
        movement = "none";
    }
    std::cout << movement << std::endl;
}

void Node::print_board_data() const {
    (this->board)->print_board_data();
}
