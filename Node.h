#include <bits/stdc++.h>

#include <vector>
#include <stack>

#include <algorithm>

#include "Board.h"

#ifndef NODE_H
#define NODE_H

class Node {
private:
    Node* parent;
    Board* board;
    int depth;
    std::vector<Node*> children;

    std::pair<bool, int> search(std::stack<Node*>, int, int, std::vector<Node*>, std::stack<Node*>*, Board*);

    int calc_depth();
    void generate_children(Board*);

    void copy_node_obj(const Node&);
    void clear();
public:
    Node();
    Node(Board*);
    Node(Node*, Board*);
    Node(const Node&);
    Node& operator=(const Node&);
    ~Node();

    std::pair<std::stack<Node*>, int> ida_star(Board*);
    void set_goal(Board*);

    Board* get_board()const;
    int get_depth() const;
    direction get_dir_shift() const;
    int get_manhattan_cost() const;

    bool is_goal() const;
    int cost(Node*) const;

    void print_dir_shift() const;
    void print_board_data() const;
};

struct compare_nodes
{
    inline bool operator()(const Node* a, const Node* b) {
        return a->get_manhattan_cost() < b->get_manhattan_cost();
    }
};

#endif
