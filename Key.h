//
// Created by kosti on 10/20/2018.
//

#ifndef UNTITLED_KEY_H
#define UNTITLED_KEY_H
#include <iostream>
#include <vector>

using namespace std;

struct Key {
    vector<int> dim ;
    long int hash_val;

    bool operator==(const Key& lhs) const
    {
        if (lhs.dim.size() != dim.size()) return false;
        for (int i = 0 ; i < lhs.dim.size() ; i++) {
            if (lhs.dim[i]!=dim[i]){
                return false;
            }
        }
        return true;
    }
};

namespace std {
    template <>
    struct hash<Key>{
        size_t operator()(const Key &k) const {
            return k.hash_val;
        }
    };
}

#endif //UNTITLED_KEY_H
