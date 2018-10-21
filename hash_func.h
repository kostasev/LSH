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
    vector<int> r;
    vector<vector<float>> v;
public:
    hash_func(int,int);
    ~hash_func();
    long int hash_value(Key&,int);
};


#endif //UNTITLED_HASH_FUNC_H
