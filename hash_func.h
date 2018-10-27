//
// Created by kosti on 10/21/2018.
//

#ifndef UNTITLED_HASH_FUNC_H
#define UNTITLED_HASH_FUNC_H
#include<iostream>
#include <vector>
#include "Key.h"
#include "data_point.h"
#include "Value.h"

class hash_func {
private:
    std::vector<int> r;
    std::vector<std::vector<float>> v;
    std::vector<float> t;
public:
    hash_func(int,int);
    ~hash_func();
    value_point<int> hash_value(data_point<int>&,int&,int,int);
};


#endif //UNTITLED_HASH_FUNC_H
