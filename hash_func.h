//
// Created by kosti on 10/21/2018.
//

#ifndef UNTITLED_HASH_FUNC_H
#define UNTITLED_HASH_FUNC_H
#include<iostream>
#include <vector>
#include "Key.h"

using namespace std;


class hash_func {
private:
    vector<float> t;
    vector<int> r;
    vector<vector<float>> v;
public:
    hash_func();
    ~hash_func();
    int hash_value(Key);
};


#endif //UNTITLED_HASH_FUNC_H
