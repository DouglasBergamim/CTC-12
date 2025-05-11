#include "hash.h"

// LOOK FOR THE COMMENTS IN THE .H 
// TO UNDERSTAND WHAT EACH FUNCTION MUST DO

Hash::Hash(int tablesize, int (*hf) (std::string) ) {
    _hash_func = hf;
    _table.resize(tablesize);
}

int Hash::add(std::string str, int &collisions) {
    int hash = _hash_func(str);
    if (contains(str, collisions))
    {
        return 0;
    } else {
        _table[hash].push_front(str);
        return 1;
    }
}//add

int Hash::remove(std::string str, int &collisions)
{
    int hash = _hash_func(str);
    if (contains(str, collisions))
    {
        _table[hash].remove(str);
        return 1;
    }
    else return 0;
}//remove


int Hash::hash(std::string str) {
    int hash = _hash_func(str) % _table.size();
    return hash;
}//hash


int Hash::contains(std::string str, int &collisions) { 
    int key = hash(str);
    collisions = 0;
    if (_table[key].empty())
        return 0;
    for (auto & it : _table[key])
    {
        collisions++;
        if (it == str)
            return 1;
    }
    return 0;
}//contains


int Hash::worst_case() {
    int worst_case = 0;
    for (auto & i : _table)
    {
        if (!i.empty())
        {
            int count = 0;
            for (auto it = i.begin(); it != i.end(); ++it){
                count++;
            }
            if (count > worst_case)
                worst_case = count;
        }
    }
    return worst_case;
}//worst_case

int Hash::size() {
    int size = 0;
    for (auto & i : _table)
    {
        if (!i.empty())
        {
            for (auto it = i.begin(); it != i.end(); ++it)
            {
                size++;
            }
        }
    }
    return size;
}//size

