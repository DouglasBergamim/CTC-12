#include <IndexPointsAluno.h>

/// returns the number of elements in the index

long IndexPointsAluno::size()
{
    return size_tree;
}

/// adds new element to the index.
void IndexPointsAluno::add (double key, long idx){
    Node* node = helper_add_node(key, idx);
    fixup_insert(node);
    ++size_tree;
}

IndexPointsAluno::Node* IndexPointsAluno::helper_add_node(double key, long idx)
{
    Node* node = new Node(idx, key, RED, nil);
    Node* x = root;
    Node* y = nil;
    while (x != nil)
    {
        y = x;
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    node->p = y;
    if (y == nil)
    {
        root = node;
        root -> color = BLACK;
        return root;
    }
    if (key < y->key)
        y-> left = node;
    else y->right = node;
    return node;
}

void IndexPointsAluno::fixup_insert(Node* z)
{
    while (z -> p -> color == RED)
    {
        bool isLeft = (z -> p == z -> p -> p -> left);
        Node* y = isLeft ? z -> p -> p -> right : z -> p -> p -> left;
        if (y -> color == RED) // if the uncle is RED, we have to change the colors
        {
            y -> color= BLACK;
            z -> p -> p -> color = RED;
            z -> p -> color = BLACK;
            z = z -> p -> p;
        }
        else // if the uncle is BLACK, we have to change the colors and rotate
        {
            if (z == (isLeft ? z -> p -> right: z-> p -> left))
            {
                z = z-> p;
                isLeft ? left_rotate(z) : right_rotate(z);
            }
            z -> p -> p -> color = RED;
            z -> p -> color = BLACK;
            isLeft ? right_rotate(z -> p -> p) : left_rotate(z -> p -> p);
        }
    }
    root -> color = BLACK;
}

void IndexPointsAluno::left_rotate(Node* node)
{
    Node* y = node -> right;
    node -> right = y -> left;

    if (y -> left != nil)
        y -> left -> p = node;

    y -> p = node -> p;
    if (node -> p == nil)
        root = y;
    else if (node == node -> p -> left)
        node -> p -> left = y;
    else node -> p -> right = y;
    y -> left = node;
    node -> p = y;
}

void IndexPointsAluno::right_rotate(Node* node)
{
    Node* y = node -> left;
    node -> left = y -> right;

    if (y -> right != nil)
        y -> right -> p = node;

    y -> p = node -> p;
    if (node -> p == nil)
        root = y;
    else if (node == node -> p -> left)
        node -> p -> left = y;
    else node -> p -> right = y;
    y -> right = node;
    node -> p = y;
}

// in this function, we have to create the basic structure to the tree
void IndexPointsAluno::find(std::vector<long> &res, double first, double last ) {
    // it is float, so it is not possible to compare with ==
    // the only thing that makes sense is to look for a range from
    // a min value to a max value.
    // stl::multimap implements this using iterators
    // you do not need to use iterators, but you need to fill the answer in O(k + logn)
    // where k is the number of elements in the range from first to last
    // in other words: NAO VALE FAZER INORDER COMPLETO E SELECIONAR O RANGE
    // PRECISA UM INORDER ESPERTO QUE ACHA O FIRST em O(log n) E CONTINUA ATE O LAST
    res.clear();
    iterator it = lower_bound(first);
    while (it  != end() && it -> key < last)
    {
        res.push_back(it -> idx);
        ++it;
    }
}

IndexPointsAluno::Node& IndexPointsAluno::iterator::operator++()
{
    if (myit == nil)
        return *nil;

    if (myit -> right != nil)
    {
        myit = myit -> right;
        while (myit -> left != nil)
        {
            myit = myit -> left;
        }
    }
    else
    {
        Node* parent = myit -> p;
        while (parent != nil &&  myit == parent -> right){
            myit = parent;
            parent = parent -> p;
        }
        myit = parent;
    }
    return *myit;
 }

bool IndexPointsAluno::iterator::operator==(iterator another_it)
{
    return myit == another_it.myit;
}

bool IndexPointsAluno::iterator::operator!=(iterator another_it)
{
    return myit != another_it.myit;
}

IndexPointsAluno::Node* IndexPointsAluno::iterator::operator->()
{
    return myit;
}

IndexPointsAluno::iterator IndexPointsAluno::lower_bound(double value)
{
    Node* current = root;
    Node* best = nil;

    while (current != nil)
    {
        if (current -> key >= value)
        {
            best = current;
            current = current -> left;
        } else
        {
            current = current -> right;
        }
    }
    return iterator(best, nil);
}

IndexPointsAluno::iterator IndexPointsAluno::end()
{
    iterator it = iterator(nil,nil);
    return it;
}



