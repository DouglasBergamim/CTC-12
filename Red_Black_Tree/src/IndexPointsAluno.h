#ifndef CES12_ALUNOINDEXPOINTS_H
#define CES12_ALUNOINDEXPOINTS_H

#include <vector>
#include <map>
#include <IndexPointsAbstract.h>


#endif
class IndexPointsAluno : public IndexPointsAbstract {

public:
    IndexPointsAluno()
    {
        nil = new Node(0, 0, BLACK, nullptr);
        root = nil;
        size_tree = 0;
    };

    long size();

    void add (double key, long idx);

    //look for a range of values
    void find(std::vector<long> &res, double first, double last );

private:

    long size_tree;

    enum Color
    {
        BLACK,
        RED
    };

    struct Node
    {
        long idx;
        double key;
        Color color;
        Node* left;
        Node* right;
        Node* p;

        Node(long idx, double key, Color c, Node* nil): idx(idx), key(key), color(c), left(nil), right(nil), p(nil) {}
    };

    struct iterator
    {
        //Shorthand
        using value_type = Node;
        using pointer = Node*;
        using reference = Node&;

        pointer myit;
        pointer nil;

        explicit iterator(Node* ptr, Node* nil): myit(ptr), nil(nil) {};

        Node& operator++();

        Node* operator->();

        bool operator==(iterator another_it);

        bool operator!=(iterator another_it);
    };

    Node* root;
    Node* nil;

    //Returns an iterator to the first node with key = value.
    iterator lower_bound(double value);

    //Return an iterator to nil
    iterator end();

    void left_rotate(Node* node);

    void right_rotate(Node* node);

    //Fixes the tree balance after adding a red node.
    void fixup_insert(Node* node);

    //Adds a red node to the tree.
    Node* helper_add_node(double key, long idx);

    long helper_size(Node* node);

    std::multimap<double, long> _map;

    friend class iterator;
};//class
